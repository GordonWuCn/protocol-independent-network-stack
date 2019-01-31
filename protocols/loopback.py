from rubik import *

class loopback_header(header_t):
    family = bit(32)

def loopback_layer():
    loopback = connectionless()
    loopback.header = seq_parse([loopback_header])
    loopback.src_meta = [loopback.header["family"]]
    loopback.dst_meta = [loopback.header["family"]]

    loopback.selector = if_(0) >> selector(loopback.src_meta, loopback.dst_meta)

    state = ["dump"]

    loopback.psm = psm(state, start_state = "dump")
    loopback.psm["incoming"] = from_("dump") + to_("dump") + predict_(1) +\
        set_(loopback.SDU, loopback.payload) + \
        set_(loopback.SDU_length, loopback.payload_length)
    return loopback