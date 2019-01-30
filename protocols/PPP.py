from rubik import *

class PPP_short_header(header_t):
    short_protocol = byte(1)

class PPP_header(header_t):
    address = bit(8)
    control = bit(8)
    protocol = byte(2)

class PPP_LCP_header(header_t):
    LCP_code = bit(8)
    LCP_ID = bit(8)
    LCP_length = byte(2)

class PPP_IPCP_header(header_t):
    PPP_IPCP_code = bit(8)
    PPP_IPCP_ID = bit(8)
    PPP_IPCP_length = byte(2)
    PPP_IPCP_data = ptr(PPP_IPCP_length - 4)

class PPP_CHAP_header(header_t):
    CHAP_code = bit(8)
    CHAP_ID = bit(8)
    CHAP_length = byte(2)
    CHAP_data = ptr(CHAP_length - 4)

class PPP_CCP_header(header_t):
    CCP_code = bit(8)
    CCP_ID = bit(8)
    CCP_length = byte(2)
    CCP_data = ptr(CCP_length - 4)

class PPP_IPV6CP_header(header_t):
    IPV6CP_code = bit(8)
    IPV6CP_ID = bit(8)
    IPV6CP_length = byte(2)
    IPV6CP_data = ptr(IPV6CP_length - 4)

class PPP_LCP_ACCM_option(header_t):
    ACCM_type = bit(8, 2)
    ACCM_length = bit(8)
    ACCM_value = ptr(ACCM_length - 2)

class PPP_LCP_AP_option(header_t):
    AP_type = bit(8, 3)
    AP_length = bit(8)
    AP_value = ptr(AP_length - 2)

class PPP_LCP_MN_option(header_t):
    MN_type = bit(8, 5)
    MN_length = bit(8)
    MN_value = ptr(MN_length - 2)

class PPP_LCP_PFC_option(header_t):
    PFC_type = bit(8, 7)
    PFC_length = bit(8)

class PPP_LCP_ACFC_option(header_t):
    ACFC_type = bit(8, 8)
    ACFC_length = bit(8)

class PPP_LCP_MRU_option(header_t):
    MRU_type = bit(8, 1)
    MRU_length = bit(8)
    MRU_value = ptr(MRU_length - 2)

class PPP_temp_data(header_t):
    protocol = bit(32)

def ppp_layer(ip, gre):
    PPP = connection_oriented()
    PPP.header = (if_(not gre.perm["short_PPP"]) >> seq_parse([PPP_header]) + \
                (if_(PPP_header.protocol == 0xC223) \
                    >> (seq_parse([PPP_CHAP_header]))) + \
                (if_(PPP_header.protocol == 0x80FD) \
                    >> (seq_parse([PPP_CCP_header]))) + \
                (if_(PPP_header.protocol == 0x8021) \
                    >> (seq_parse([PPP_IPCP_header]))) + \
                (if_(PPP_header.protocol == 0x8057) \
                    >> (seq_parse([PPP_IPV6CP_header]))) + \
                (if_(PPP_header.protocol == 0xC021) \
                    >> ((seq_parse([PPP_LCP_header])) + \
                        (while_(PPP.cur_pos < PPP_LCP_header.LCP_length + 4) >> \
                            any_parse([PPP_LCP_ACCM_option, \
                                       PPP_LCP_AP_option, \
                                       PPP_LCP_MN_option, \
                                       PPP_LCP_PFC_option, \
                                       PPP_LCP_ACFC_option, \
                                       PPP_LCP_MRU_option]))))) + \
                (if_(gre.perm["short_PPP"]) >> seq_parse([PPP_short_header]) + \
                            (if_(PPP_short_header.short_protocol == 0xC223) \
                                >> (seq_parse([PPP_CHAP_header]))) + \
                            (if_(PPP_short_header.short_protocol == 0x80FD) \
                                >> (seq_parse([PPP_CCP_header]))) + \
                            (if_(PPP_short_header.short_protocol == 0x8021) \
                                >> (seq_parse([PPP_IPCP_header]))) + \
                            (if_(PPP_short_header.short_protocol == 0x8057) \
                                >> (seq_parse([PPP_IPV6CP_header]))) + \
                            (if_(PPP_short_header.short_protocol == 0xC021) \
                                >> (seq_parse([PPP_LCP_header]))))

    PPP.temp = auxiliary_data(PPP_temp_data)

    PPP.preprocess = (if_(gre.perm["short_PPP"]) >> \
                         set_(PPP.temp["protocol"], \
                              PPP.header["short_protocol"])) + \
                     (if_(not gre.perm["short_PPP"]) >> \
                         set_(PPP.temp["protocol"], \
                              PPP.header["protocol"]))

    PPP.src_meta = [ip.header["src_addr"]]
    PPP.dst_meta = [ip.header["dst_addr"]]

    state = ["SESSION", "active_pasive_sent_ACFC", \
                "passive_sent_ACFC_active_no", "active_ACFC_acked_passive_no"]

    PPP.psm = psm(state, start_state = "SESSION")

    PPP.psm["config_a"] = from_("SESSION") + \
        to_("SESSION") + predict_(PPP.to_passive and \
                                  PPP.temp["protocol"] != 0x0021 and \
                                  not PPP_LCP_ACFC_option)

    PPP.psm["config_p"] = from_("SESSION") + \
        to_("SESSION") + predict_(PPP.to_active and \
                                  PPP.temp["protocol"] != 0x0021 and \
                                  not PPP_LCP_ACFC_option)

    PPP.psm["p_sent_AFCF"] = from_("SESSION") + \
        to_("passive_sent_ACFC_active_no") + predict_(PPP.to_passive and \
                                                      PPP_LCP_ACFC_option)
    PPP.psm["a_after_p_sent_AFCF"] = \
        from_("passive_sent_ACFC_active_no") + to_("active_pasive_sent_ACFC") +\
        predict_(PPP.to_active and PPP_LCP_ACFC_option)

    PPP.psm["a_AFCF_acked"] = from_("active_pasive_sent_ACFC") + \
        to_("active_ACFC_acked_passive_no") + predict_(PPP.to_passive)

    PPP.psm["a_p_AFCF_acked"] = from_("active_ACFC_acked_passive_no") + \
        to_("SESSION") + predict_(PPP.to_active) + set_(gre.perm["short_PPP"], 1)

    PPP.psm["tunneling_a"] = from_("SESSION") + \
        to_("SESSION") + predict_(PPP.to_passive and \
                                    PPP.temp["protocol"] == 0x0021) + \
                         set_(PPP.SDU, PPP.payload) + \
                         set_(PPP.SDU_length, PPP.payload_length)

    PPP.psm["tunneling_p"] = from_("SESSION") + \
        to_("SESSION") + predict_(PPP.to_active and \
                                    PPP.temp["protocol"] == 0x0021) + \
                         set_(PPP.SDU, PPP.payload) + \
                         set_(PPP.SDU_length, PPP.payload_length)

    return PPP, PPP.temp