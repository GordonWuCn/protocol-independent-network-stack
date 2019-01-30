from rubik import *
class gtp_hdr(header_t):
    version = bit(3)
    PT = bit(1)
    Reserved = bit(1)
    E = bit(1)
    S = bit(1)
    PN = bit(1)
    MT = bit(8)
    Total_length = bit(16)
    TEID = bit(32)
    # TEID = byte(4)

class var_header(header_t):
    seq_no_upper = bit(16)
    NPDU_no = bit(8)
    Next_header_type = bit(8)

class gtp_extension_header(header_t):
    extension_length = bit(8)
    extension_data = ptr(extension_length * 4 - 2)
    next_type = bit(8)



def gtp_layer():
    gtp = connectionless()
    gtp.header = seq_parse([gtp_hdr]) + \
                 (if_(gtp_hdr.E or gtp_hdr.S or gtp_hdr.PN) >> \
                    (seq_parse([var_header]) + \
                    ((if_(gtp_hdr.E) >> (seq_parse([gtp_extension_header]) + \
                       (while_(gtp_extension_header.next_type) >> \
                               seq_parse([gtp_extension_header])))))))
    gtp.timeout = 10
    gtp.src_meta = [gtp.header["TEID"]]
    gtp.dst_meta = [gtp.header["TEID"]]
    gtp.selector = if_(0) >> selector(gtp.src_meta, gtp.dst_meta)

    state = ["start"]
    gtp.psm = psm(state, start_state = "start")
    gtp.psm["direct_dump"] = from_("start") + \
                                       to_("start") + \
                                       predict_(1) + \
                                       set_(gtp.SDU_length, gtp.payload_length) + \
                                       set_(gtp.SDU, gtp.payload)
    return gtp