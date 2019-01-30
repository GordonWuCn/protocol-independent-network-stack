from rubik import *

class pptp_general(header_t):
    length = byte(2)
    pptp_message_type = byte(2)
    magic_cookie = bit(32)

class start_control_connection_request(header_t):
    SCCRQ_type = bit(16, 256)
    SCCRQ_reserved0 = bit(16)
    SCCRQ_protocol_version = bit(16)
    SCCRQ_reserved1 = bit(16)
    SCCRQ_framing_capabilities = bit(32)
    SCCRQ_bearer_capabilities = bit(32)
    SCCRQ_maximum_channels = bit(16)
    SCCRQ_firmware_revision = bit(16)
    SCCRQ_host_name = ptr(64)
    SCCRQ_vandor_name = ptr(64)

class start_control_connection_reply(header_t):
    SCCRP_type = bit(16, 512)
    SCCRP_reserved0 = bit(16)
    SCCRP_protocol_version = bit(16)
    SCCRP_result_code = bit(8)
    SCCRP_error_code = bit(8)
    SCCRP_framing_capabilities = bit(32)
    SCCRP_bearer_capabilities = bit(32)
    SCCRP_maximum_channels = bit(16)
    SCCRP_firmware_revision = bit(16)
    SCCRP_host_name = ptr(64)
    SCCRP_vandor_name = ptr(64)

class outgoing_call_request(header_t):
    OCRQ_type = bit(16, 1792)
    OCRQ_reserved0 = bit(16)
    OCRQ_call_ID = bit(16)
    OCRQ_call_serial_number = bit(16)
    OCRQ_minimum_BPS = bit(32)
    OCRQ_maximum_BPS = bit(32)
    OCRQ_bearer_type = bit(32)
    OCRQ_framing_type = bit(32)
    OCRQ_packet_recv_ws = bit(16)
    OCRQ_packet_processing_delay = bit(16)
    OCRQ_phone_number_length = bit(16)
    OCRQ_reserved = bit(16)
    OCRQ_phone_number = ptr(64)
    OCRQ_subaddress = ptr(64)

class outgoing_call_reply(header_t):
    OCRP_type = bit(16, 2048)
    OCRP_reserved0 = bit(16)
    OCRP_call_ID = bit(16)
    OCRP_peer_call_ID = bit(16)
    OCRP_result_code = bit(8)
    OCRP_error_code = bit(8)
    OCRP_cause_code = bit(16)
    OCRP_connect_speed = bit(32)
    OCRP_packet_recv_ws = bit(16)
    OCRP_packet_processing_delay = bit(16)
    OCRP_physical_channel_ID = bit(32)

class set_link_info(header_t):
    SLI_type = bit(16, 3840)
    SLI_reserved0 = bit(16)
    SLI_peer_call_ID = bit(16)
    SLI_reserved = bit(16)
    SLI_send_ACCM = bit(32)
    SLI_recv_ACCM = bit(32)

class echo_request(header_t):
    ERQ_type = bit(16, 1280)
    ERQ_reserved0 = bit(16)
    ERQ_identifier = bit(32)

class echo_reply(header_t):
    ERP_type = bit(16, 1536)
    ERP_reserved0 = bit(16)
    ERP_identifier = bit(32)
    ERP_result_code = bit(8)
    ERP_error_code = bit(8)
    ERP_reserved1 = bit(16)

def pptp_layer(ip):
    pptp = connection_oriented()
    pptp.header = seq_parse([pptp_general]) + \
                  any_parse([ \
                            start_control_connection_request, \
                            start_control_connection_reply, \
                            outgoing_call_request, \
                            outgoing_call_reply, \
                            set_link_info, \
                            echo_request, \
                            echo_reply\
                            ])
    pptp.src_meta = [ip.header['src_addr']]
    pptp.dst_meta = [ip.header['dst_addr']]
    pptp.timeout = 120

    states = ["CLOSED", "REQUEST_CONNECT", "CONNECTION_ESTABLISHED", \
             "REQUEST_SESSION", "SESSION_ESTABLISHED", "ECHO_SENT"]
    pptp.psm = psm(states, start_state = "CLOSED")

    pptp.psm["SCCRQ_sent"] = from_("CLOSED") + \
                             to_("REQUEST_CONNECT") + \
                             predict_(pptp.to_passive and \
                                      start_control_connection_request)

    pptp.psm["SCCRP_sent"] = from_("REQUEST_CONNECT") + \
                             to_("CONNECTION_ESTABLISHED") + \
                             predict_(pptp.to_active and \
                                      start_control_connection_reply)
    
    pptp.psm["OCRQ_sent"] = from_("CONNECTION_ESTABLISHED") + \
                            to_("REQUEST_SESSION") + \
                            predict_(pptp.to_passive and \
                                     outgoing_call_request)

    pptp.psm["OCRP_sent"] = from_("REQUEST_SESSION") + \
                            to_("SESSION_ESTABLISHED") + \
                            predict_(pptp.to_active and \
                                     outgoing_call_reply)

    pptp.psm["session_config_passive"] = from_("SESSION_ESTABLISHED") + \
                                         to_("SESSION_ESTABLISHED") + \
                                         predict_(pptp.to_active and \
                                                  set_link_info)

    pptp.psm["session_config_active"] = from_("SESSION_ESTABLISHED") + \
                                        to_("SESSION_ESTABLISHED") + \
                                        predict_(pptp.to_active and \
                                                 set_link_info)

    pptp.psm["keep_alive"] = from_("SESSION_ESTABLISHED") + \
                             to_("ECHO_SENT")  + \
                             predict_(pptp.to_passive and \
                                      echo_request)

    pptp.psm["maintain_connection"] = from_("ECHO_SENT") + \
                                      to_("SESSION_ESTABLISHED") + \
                                      predict_(pptp.to_active and \
                                              echo_reply)

    return pptp