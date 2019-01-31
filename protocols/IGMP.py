from rubik import *

class IGMP_header(header_t):
    IGMP_type = bit(8)
    reserved = bit(8)
    checksum = bit(16)
    group_address = bit(32)

def IGMP_layer():
    IGMP = connectionless()
    IGMP.header = seq_parse([IGMP_header])
    IGMP.src_meta = [IGMP.header["group_address"]]
    IGMP.dst_meta = [IGMP.header["group_address"]]

    IGMP.selector = if_(0) >> selector(IGMP.src_meta, IGMP.dst_meta)

    state = ["dump"]

    IGMP.psm = psm(state, start_state = "dump")
    IGMP.psm["incoming"] = from_("dump") + to_("dump") + predict_(1)

    return IGMP

