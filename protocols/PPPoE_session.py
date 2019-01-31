from rubik import *

class PPPoE_session_header(header_t):
    PPPoE_session_ver = bit(4)
    PPPoE_session_type = bit(4)
    PPPoE_session_code = bit(8)
    PPPoE_session_ID = bit(16)
    PPPoE_session_length = byte(2)

def PPPoE_session_layer(eth):
    PPPoE_session = connectionless()
    PPPoE_session.header = seq_parse([PPPoE_session_header])
    PPPoE_session.src_meta = [eth.header["eth_src_upper"], eth.header["eth_src_middle"], eth.header["eth_src_lower"], PPPoE_session.header["PPPoE_session_ID"]]

    PPPoE_session.dst_meta = [eth.header["eth_dst_upper"], eth.header["eth_dst_middle"], eth.header["eth_dst_lower"], PPPoE_session.header["PPPoE_session_ID"]]

    PPPoE_session.selector = if_(0) >> selector(PPPoE_session.src_meta, \
                                                PPPoE_session.dst_meta)

    state = ["dump"]

    PPPoE_session.psm = psm(state, start_state = "dump")
    PPPoE_session.psm["incoming"] = from_("dump") + to_("dump") + \
        predict_(1) + set_(PPPoE_session.SDU, PPPoE_session.payload) + \
        set_(PPPoE_session.SDU_length, PPPoE_session.payload_length)

    return PPPoE_session
