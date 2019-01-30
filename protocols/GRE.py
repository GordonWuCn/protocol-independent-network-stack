from rubik import *

class GRE_header(header_t):
        C = bit(1)
        R = bit(1)
        K = bit(1)
        S = bit(1)
        strict_source_route = bit(1)
        recursion_control = bit(3)
        A = bit(1)
        reserved = bit(4)
        version = bit(3)
        protocol = byte(2)
        payload_length = byte(2)
        call_ID = bit(16)

class GRE_sequence_number(header_t):
        sequence_number = bit(32)

class GRE_ack_number(header_t):
        ack_number = bit(32)

class GRE_perm(header_t):
        short_PPP = bit(8)

def gre_layer(ip):
        gre = connection_oriented()
        gre.header = seq_parse([GRE_header]) + \
                     (if_(GRE_header.S) >> seq_parse([GRE_sequence_number])) + \
                     (if_(GRE_header.A) >> seq_parse([GRE_ack_number]))
        gre.src_meta = [ip.header["src_addr"]]
        gre.dst_meta = [ip.header["dst_addr"]]

        gre.perm = auxiliary_data(GRE_perm)

        gre.initializing = set_(gre.perm["short_PPP"], 0)

        state = ["dump"]

        gre.psm = psm(state, start_state = "dump")
        gre.psm["tunneling_p"] = from_("dump") + to_("dump") + \
                                 predict_(gre.to_active and \
                                         gre.header["payload_length"] > 0) + \
                                 set_(gre.SDU, gre.payload) + \
                                 set_(gre.SDU_length, gre.payload_length)

        gre.psm["tunneling_a"] = from_("dump") + to_("dump") + \
                                 predict_(gre.to_passive and \
                                         gre.header["payload_length"] > 0) + \
                                 set_(gre.SDU, gre.payload) + \
                                 set_(gre.SDU_length, gre.payload_length)

        gre.psm["only_ack_p"] = from_("dump") + to_("dump") + \
                                predict_(gre.to_active and \
                                                 gre.header["payload_length"] == 0)

        gre.psm["only_ack_a"] = from_("dump") + to_("dump") + \
                                predict_(gre.to_passive and \
                                                 gre.header["payload_length"] == 0)
        return gre