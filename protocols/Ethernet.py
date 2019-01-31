from rubik import *

class eth_header(header_t):
    eth_dst_upper = bit(16)
    eth_dst_middle = bit(16)
    eth_dst_lower = bit(16)
    eth_src_upper = bit(16)
    eth_src_middle = bit(16)
    eth_src_lower = bit(16)
    eth_type = byte(2)

def eth_layer():
    eth = connectionless()
    eth.header = seq_parse([eth_header])
    eth.src_meta = [eth.header["eth_src_upper"], eth.header["eth_src_middle"], eth.header["eth_src_lower"]]
    eth.dst_meta = [eth.header["eth_dst_upper"], eth.header["eth_dst_middle"], eth.header["eth_dst_lower"]]

    eth.selector = if_(0) >> selector(eth.src_meta, eth.dst_meta)

    state = ["dump"]

    eth.psm = psm(state, start_state = "dump")
    eth.psm["incoming"] = from_("dump") + to_("dump") + predict_(1) +\
        set_(eth.SDU, eth.payload) + \
        set_(eth.SDU_length, eth.payload_length)
    return eth
