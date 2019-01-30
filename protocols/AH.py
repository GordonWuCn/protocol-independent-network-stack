from rubik import *
class AH_header(header_t):
    NH = bit(8)
    payload_length = bit(8)
    reserved = bit(16)
    SPI = bit(32)
    seq_num = byte(4)
    ICV_upper = bit(64)
    ICV_lower = bit(32)

class AH_perm(header_t):
    seq_num = bit(32)

def AH_layer(ip):
    AH = connectionless()
    AH.header = seq_parse([AH_header])
    AH.timeout = 10
    AH.perm = auxiliary_data(AH_perm)

    AH.initializing = set_(AH.perm["seq_num"], 0)

    AH.src_meta = [ip.header["src_addr"]]
    AH.dst_meta = [ip.header["dst_addr"]]

    state = ["check_seq"]

    AH.psm = psm(state, start_state = "check_seq")
    AH.psm["safe"] = from_("check_seq") + to_("check_seq") + \
        predict_(AH.header["seq_num"] == AH.perm["seq_num"] + 1) + \
        set_(AH.perm["seq_num"], AH.header["seq_num"])
    return AH