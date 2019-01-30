from rubik import *

class ip_hdr(header_t):
    version = bit(4)
    hdr_len = bit(4)
    TOS = bit(8)
    total_len = bit(16)
    identifier = bit(16)
    blank = bit(1)
    dont_frag = bit(1)
    more_frag = bit(1)
    frag_offset_upper = bit(5)
    frag_offset_lower = bit(8)
    TTL = bit(8)
    protocol = bit(8)
    checksum = bit(16)
    src_addr = bit(32)
    dst_addr = bit(32)

class pure_ip_data(header_t):
    buf_len = bit(32)

class pure_ip_temp_data(header_t):
    frag_offset = bit(16)
    buf_len = bit(32, 0)

class ip_meta_data(header_t):
    offset = bit(16)
    length = bit(16)

def ip_layer():
    ip = connectionless()
    ip.header = seq_parse([ip_hdr])
    ip.timeout = 10
    ip.perm = auxiliary_data(pure_ip_data)
    # ip_temp = auxiliary_data(temp)

    ip.temp = auxiliary_data(pure_ip_temp_data)
    ip.preprocess = set_(ip.temp["frag_offset"], \
                        ((ip.header["frag_offset_upper"] << 8) + \
                            ip.header["frag_offset_lower"]) * 8) + \
                    set_(ip.temp["buf_len"], 0)
    ip.src_meta = [ip.header["src_addr"]]
    ip.dst_meta = [ip.header["dst_addr"]]
    ip.selector = if_(not (ip.header["dont_frag"])) >> selector(ip.src_meta, ip.dst_meta) 

    state = ["direct_dump", "buffering"]

    ip.psm = psm(state, start_state = "direct_dump")

    ip.psm['no_buffer'] = from_("direct_dump") + \
                          to_("direct_dump") + \
                          predict_(ip.header["dont_frag"] or \
                              (not ip.header["dont_frag"] and \
                                   not ip.header["more_frag"])) + \
                          set_(ip.SDU, ip.payload) + \
                          set_(ip.SDU_length, ip.payload_length)
    ip.psm["has_buffer"] = from_("direct_dump") + \
                           to_("buffering") + \
                           predict_(ip.header["more_frag"] and \
                               not ip.header["dont_frag"]) + \
                           manage_buf(["inserter"])

    ip.psm["still_has_buffer"] = from_("buffering") + \
                                 to_("buffering") + \
                                 predict_(ip.header["more_frag"] and \
                                 not ip.header["dont_frag"]) + \
                                 manage_buf(["inserter"])
    ip.psm["last_buffer"] = from_("buffering") + to_("direct_dump") + \
                            predict_(not ip.header["more_frag"] and \
                                not ip.header["dont_frag"]) + \
                            manage_buf(["inserter", "assemble"])

    ip.buf = buffer(ip.temp["frag_offset"])
    ip.buf.op["inserter"] = insert()
    ip.buf.op["assemble"] = if_(1) >> assemble()
    return ip, ip.temp




