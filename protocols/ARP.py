from rubik import *

class ARP_header(header_t):
    hardware_type = bit(16)
    protocol_type = bit(16)
    hardware_size = bit(8)
    protocol_size = bit(8)
    opcode = bit(16)
    sender_hw_addr = byte(hardware_size)
    sender_proto_addr = byte(protocol_size)
    target_hw_addr = byte(hardware_size)
    target_proto_addr = byte(protocol_size)

def ARP_layer(eth):
    ARP = connectionless()
    ARP.header = seq_parse([ARP_header])
    ARP.src_meta = [eth.header["eth_src_upper"], eth.header["eth_src_middle"], eth.header["eth_src_lower"]]
    ARP.dst_meta = [eth.header["eth_src_upper"], eth.header["eth_src_middle"], eth.header["eth_src_lower"]]

    ARP.selector = if_(0) >> selector(ARP.src_meta, ARP.dst_meta)

    state = ["dump"]

    ARP.psm = psm(state, start_state = "dump")
    ARP.psm["incoming"] = from_("dump") + to_("dump") + predict_(1)

    return ARP
