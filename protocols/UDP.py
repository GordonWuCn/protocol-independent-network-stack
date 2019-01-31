from rubik import *
class udp_hdr(header_t):
    src_port = bit(16)
    dst_port = bit(16)
    pkt_length = bit(16)
    checksum = bit(16)

def udp_layer():
    udp = connectionless();
    udp.header = seq_parse([udp_hdr])
    udp.timeout = 10
    udp.src_meta = [udp.header["src_port"]]
    udp.dst_meta = [udp.header["dst_port"]]
    udp.selector = if_(0) >> selector(udp.src_meta, udp.dst_meta)

    state = ["start"]
    udp.psm = psm(state, start_state = "start")
    udp.psm["direct_dump"] = from_("start") + \
                             to_("start") + \
                             predict_(1) + \
                             set_(udp.SDU_length, udp.payload_length) + \
                             set_(udp.SDU, udp.payload)
    return udp
