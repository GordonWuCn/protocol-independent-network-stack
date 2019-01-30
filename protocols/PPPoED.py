from rubik import *

class PPPoED_header(header_t):
    version = bit(4)
    type = bit(4)
    PPPoED_code = bit(8)
    session_ID = bit(16)
    length = byte(2)

class PPPoED_EOL(header_t):
    EOL_type = bit(16, 0x0000)
    EOL_value = bit(16)

class PPPoED_service_name(header_t):
    service_name_type = bit(16, 0x0101)
    service_name_length = byte(2)
    service_name_value = ptr(service_name_length)

class PPPoED_AC_name(header_t):
    AC_name_type = bit(16, 0x0201)
    AC_name_length = byte(2)
    AC_name_value = ptr(AC_name_length)

class PPPoED_AC_cookie(header_t):
    AC_cookie_type = bit(16, 0x0401)
    AC_cookie_length = byte(2)
    AC_cookie_value = ptr(AC_cookie_length)

def PPPoED_layer(eth):
    PPPoED = connection_oriented()
    PPPoED.header = seq_parse([PPPoED_header]) + (if_(PPPoED_header.length > 0) >> \
        (while_(PPPoED.cur_pos < 6 + PPPoED_header.length) >> any_parse([PPPoED_EOL, \
        PPPoED_service_name, PPPoED_AC_name, PPPoED_AC_cookie])))
    PPPoED.timeout = 10

    PPPoED.src_meta = [eth.header["eth_src_upper"], eth.header["eth_src_middle"], eth.header["eth_src_lower"]]
    PPPoED.dst_meta = [eth.header["eth_dst_upper"], eth.header["eth_dst_middle"], eth.header["eth_dst_lower"]]

    PPPoED.selector = if_(not (eth.header["eth_dst_upper"] == 0xFFFF and \
        eth.header["eth_dst_lower"] == 0xFFFF and eth.header["eth_dst_middle"] == 0xFFFF)) >> selector(PPPoED.src_meta, \
        PPPoED.dst_meta)

    state = ["initiation", "offered", "request", "confirmed"]

    PPPoED.psm = psm(state, start_state = "initiation", terminate_states = [])

    PPPoED.psm["PADI"] = from_("initiation") + to_("initiation") + \
        predict_(PPPoED.to_passive and eth.header["eth_dst_upper"] == 0xFFFF and \
            eth.header["eth_dst_lower"] == 0xFFFF and \
            eth.header["eth_dst_middle"] == 0xFFFF and PPPoED.header["PPPoED_code"] == 0x09) 
    PPPoED.psm["PADO"] = from_("initiation") + to_("offered") + \
        predict_(PPPoED.to_passive and PPPoED.header["PPPoED_code"] == 0x07)

    PPPoED.psm["PADR"] = from_("offered") + to_("request") + \
        predict_(PPPoED.to_active and PPPoED.header["PPPoED_code"] == 0x19)

    PPPoED.psm["PADS"] = from_("request") + to_("confirmed") + \
        predict_(PPPoED.to_passive and PPPoED.header["PPPoED_code"] == 0x65)

    PPPoED.psm["others"] = from_("confirmed") + to_("confirmed") + \
        predict_(PPPoED.to_active)
    PPPoED.psm["others"] = from_("confirmed") + to_("confirmed") + \
        predict_(PPPoED.to_passive)

    return PPPoED