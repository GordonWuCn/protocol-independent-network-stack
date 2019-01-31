from rubik import *
class tcp_hdr(header_t):
    srcport = bit(16)
    dstport = bit(16)
    seq_num = byte(4)
    ack_num = byte(4)
    hdr_len = bit(4)
    blank = bit(4)
    cwr = bit(1)
    ece = bit(1)
    urg = bit(1)
    ack = bit(1)
    psh = bit(1)
    rst = bit(1)
    syn = bit(1)
    fin = bit(1)
    window_size = bit(16)
    checksum = bit(16)
    urgent_pointer = bit(16)

class tcp_eol(header_t):
    eol_type = bit(8, 0)

class tcp_nop(header_t):
    nop_type = bit(8, 1)

class tcp_mss(header_t):
    mss_type = bit(8, 2)
    mss_len = bit(8)
    mss_value = bit(16)

class tcp_ws(header_t):
    ws_type = bit(8, 3)
    ws_len = bit(8)
    ws_value = bit(8)

class tcp_SACK_permitted(header_t):
    SCAK_permitted_type = bit(8, 4)
    SCAK_permitted_len = bit(8)

class tcp_SACK(header_t):
    SACK_type = bit(8, 5)
    SACK_len = bit(8)
    SACK_value = ptr(SACK_len - 2)

class tcp_TS(header_t):
    TS_type = bit(8, 8)
    TS_len = bit(8)
    TS_value = bit(32)
    TS_echo_reply = bit(32)

class tcp_cc_new(header_t):
    cc_new_type = bit(8, 12)
    cc_new_len = bit(8)
    cc_new_value = bit(32)

class tcp_mptcp(header_t):
    mptcp_type = bit(8, 30)
    mptcp_len = bit(8)
    mptcp_value = ptr(mptcp_len - 2)

class tcp_unknown(header_t):
    unknown_type = bit(8, 251)
    unknown_len = bit(8)
    unknown_value = ptr(unknown_len - 2)

class data(header_t):
    cur_seq_num = bit(32)
    active_buf_len = bit(32, 0)
    passive_buf_len = bit(32, 0)
    active_seq = bit(32)
    passive_seq = bit(32)
    active_window = bit(64)
    passive_window = bit(64)
    active_ws = bit(32, 1)
    passive_ws = bit(32, 1)
    active_ack = bit(32, 0)
    passive_ack = bit(32, 0)

class temp(header_t):
    tcp_hdr_len = bit(8)
    buf_len = bit(32)
    cur_seq = bit(32)
    window = bit(32)

class tcp_blank(header_t):
    blank = bit(32)


def tcp_layer(ip):
    tcp = connection_oriented()

    tcp.header = seq_parse([tcp_hdr]) + \
                 (while_(tcp.cur_pos < tcp_hdr.hdr_len * 4 and \
                      tcp.payload_length > 0) >> \
                      any_parse([tcp_eol, \
                                 tcp_nop, \
                                 tcp_mss, \
                                 tcp_ws, \
                                 tcp_SACK_permitted, \
                                 tcp_SACK, \
                                 tcp_TS, \
                                 tcp_cc_new, \
                                 tcp_mptcp, \
                                 tcp_unknown])) + \
                 (while_(tcp.cur_pos < tcp_hdr.hdr_len * 4 and \
                      tcp.payload_length > 0) >> seq_parse([tcp_blank]))
    tcp.timeout = 10
    tcp.src_meta = [ip.header["src_addr"], tcp.header['srcport']]
    tcp.dst_meta = [ip.header["dst_addr"], tcp.header['dstport']]

    tcp.perm = auxiliary_data(data)
    tcp.temp = auxiliary_data(temp)

    tcp.preprocess = set_(tcp.temp['buf_len'], 0) + \
                     (if_(tcp_ws and tcp.to_active) >> \
                         set_(tcp.perm["passive_ws"], tcp.header["ws_value"])) + \
                     (if_(tcp_ws and tcp.to_passive) >> \
                         set_(tcp.perm["active_ws"], tcp.header["ws_value"])) + \
                     (if_(tcp.to_active) >> \
                         set_(tcp.perm["passive_window"], tcp.header["window_size"])) + \
                     (if_(tcp.to_passive) >> \
                         set_(tcp.perm["active_window"], tcp.header["window_size"])) + \
                     (if_(tcp.to_active and tcp.header["ack"] and \
                         tcp.header["ack_num"] > tcp.perm["passive_ack"]) >> \
                         set_(tcp.perm["passive_ack"], tcp.header["ack_num"])) + \
                     (if_(tcp.to_passive and tcp.header["ack"] and \
                         tcp.header["ack_num"] > tcp.perm["active_ack"]) >> \
                         set_(tcp.perm["active_ack"], tcp.header["ack_num"]))

    states = ['CLOSED', 'SYN_SENT', 'SYN_RECEIVED', 'ESTABLISHED', \
                 'FIN_WAIT_1','CLOSE_WAIT','LAST_ACK', 'TERMINATE']
    tcp.psm = psm(states, 
                  start_state = "CLOSED", 
                  terminate_states = ["TERMINATE"])

    tcp.psm['first_hs'] = from_('CLOSED') + \
                          to_('SYN_SENT') + \
                          predict_(tcp.to_passive and tcp.header['syn']) + \
                          set_(tcp.perm['active_seq'], tcp.header['seq_num'] + 1)

    tcp.psm['second_hs'] = from_('SYN_SENT') + \
                           to_('SYN_RECEIVED') + \
                           predict_(tcp.to_active and tcp.header['syn'] and \
                                tcp.header['ack'] and tcp.header['ack_num'] == \
                                    tcp.perm['active_seq'])  + \
                           set_(tcp.perm["passive_seq"], tcp.header["seq_num"] + 1)
    tcp.psm['third_hs'] = from_('SYN_RECEIVED') + \
                          to_('ESTABLISHED') + \
                          predict_(tcp.to_passive and tcp.header['ack'] and \
                              tcp.header["ack_num"] == tcp.perm["passive_seq"])
                                
    tcp.psm["buffering_passive"] = \
                        from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_passive and tcp.payload_length > 0 and \
                            tcp.perm["active_seq"] < tcp.header["seq_num"] and \
                            tcp.header["seq_num"] >= tcp.perm["passive_ack"] and \
                            tcp.header["seq_num"] < tcp.perm["passive_ack"] + \
                                tcp.perm["passive_window"] << tcp.perm["passive_ws"]) + \
                        set_(tcp.temp["cur_seq"], tcp.perm["active_seq"]) + \
                        set_(tcp.temp["window"], tcp.perm["passive_ack"]) + \
                        manage_buf(["inserter", "ejector", "out_of_window"]) +\
                        set_(tcp.perm["active_seq"], tcp.temp["cur_seq"])

    tcp.psm["ff_passive"] = \
                        from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_passive and tcp.payload_length > 0 and \
                            tcp.perm["active_seq"] == tcp.header["seq_num"] and \
                            tcp.header["seq_num"] >= tcp.perm["passive_ack"] and \
                            tcp.header["seq_num"] < tcp.perm["passive_ack"] + \
                                tcp.perm["passive_window"] << tcp.perm["passive_ws"] ) + \
                        set_(tcp.perm["active_seq"], \
                            tcp.perm["active_seq"] + tcp.payload_length) + \
                        set_(tcp.SDU, tcp.payload) + \
                        set_(tcp.SDU_length, tcp.payload_length)

    tcp.psm["retrx_passive"] = \
                        from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_passive and tcp.payload_length > 0 and \
                            tcp.perm["active_seq"] > tcp.header["seq_num"] and \
                            tcp.header["seq_num"] >= tcp.perm["passive_ack"] and \
                            tcp.header["seq_num"] < tcp.perm["passive_ack"] + \
                                tcp.perm["passive_window"] << tcp.perm["passive_ws"])

    tcp.psm["out_of_window_passive"] = \
                        from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_passive and tcp.payload_length > 0 and \
                            (tcp.perm["active_seq"] > tcp.header["seq_num"] and \
                                tcp.header["seq_num"] < tcp.perm["passive_ack"] or \
                                tcp.perm["active_seq"] < tcp.header["seq_num"] and \
                                tcp.header["seq_num"] < tcp.perm["passive_ack"] + \
                                tcp.perm["passive_window"] << tcp.perm["passive_ws"]))

    tcp.psm["buffering_active"] = from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_active and tcp.payload_length > 0 and \
                            tcp.perm["passive_seq"] < tcp.header["seq_num"] and \
                            tcp.header["seq_num"] >= tcp.perm["active_ack"] and \
                            tcp.header["seq_num"] < tcp.perm["active_ack"] + \
                                tcp.perm["active_window"] << tcp.perm["active_ws"]) + \
                        set_(tcp.temp["cur_seq"], tcp.perm["passive_seq"]) + \
                        set_(tcp.temp["window"], tcp.perm["active_ack"]) + \
                        manage_buf(["inserter", "ejector", "out_of_window"]) + \
                        set_(tcp.perm["passive_seq"], tcp.temp["cur_seq"])

    tcp.psm["ff_active"] = from_("ESTABLISHED") + to_("ESTABLISHED") + \
                        predict_(tcp.to_active and tcp.payload_length > 0 and \
                            tcp.perm["passive_seq"] == tcp.header["seq_num"] and \
                            tcp.header["seq_num"] >= tcp.perm["active_ack"] and \
                            tcp.header["seq_num"] < tcp.perm["active_ack"] + \
                                tcp.perm["active_window"] << tcp.perm["active_ws"]) + \
                        set_(tcp.perm["passive_seq"], tcp.perm["passive_seq"] + tcp.payload_length) + \
                        set_(tcp.SDU, tcp.payload) + set_(tcp.SDU_length, tcp.payload_length)

    tcp.psm["retrx_active"] = from_("ESTABLISHED") + \
                              to_("ESTABLISHED") + \
                              predict_(tcp.to_active and tcp.payload_length > 0 and \
                                  tcp.perm["passive_seq"] > tcp.header["seq_num"] and \
                                  tcp.header["seq_num"] >= tcp.perm["active_ack"] and \
                                  tcp.header["seq_num"] < tcp.perm["active_ack"] + \
                                  tcp.perm["active_window"] << tcp.perm["active_ws"])

    tcp.psm["out_of_window_active"] = \
                        from_("ESTABLISHED") + \
                        to_("ESTABLISHED") + \
                        predict_(tcp.to_active and tcp.payload_length > 0 and \
                            (tcp.perm["passive_seq"] > tcp.header["seq_num"] and \
                                tcp.header["seq_num"] < tcp.perm["active_ack"] or \
                                tcp.perm["passive_seq"] < tcp.header["seq_num"] and \
                                tcp.header["seq_num"] < tcp.perm["active_ack"] + \
                                tcp.perm["active_window"] << tcp.perm["active_ws"]))


    tcp.psm['disconnected_1st_hs'] = from_('ESTABLISHED') + to_('FIN_WAIT_1') + \
                                predict_(tcp.to_passive and tcp.header['fin']) + \
                                set_(tcp.perm['active_seq'], tcp.header['seq_num'] + 1) 
    tcp.psm['disconnected_1st_hs'] = from_('ESTABLISHED') + to_('FIN_WAIT_1') + \
                                predict_(tcp.to_active and tcp.header['fin']) + \
                                set_(tcp.perm['active_seq'], tcp.header['seq_num'] + 1) + \
                                set_(tcp.to_passive, 1)
                                
    tcp.psm['disconnected_2nd_hs'] = from_('FIN_WAIT_1') + to_('CLOSE_WAIT') + \
                                predict_(tcp.to_active and tcp.header['ack'] and \
                                    not tcp.header['fin'] and \
                                    tcp.header['ack_num'] == tcp.perm['active_seq']) 
                                
    tcp.psm['disconnected_2nd_hs_fast'] = from_('FIN_WAIT_1') + to_('LAST_ACK') + \
                                predict_(tcp.to_active and tcp.header['ack'] and \
                                    tcp.header['fin'] and \
                                    tcp.header['ack_num'] == tcp.perm['active_seq']) + \
                                set_(tcp.perm['passive_seq'], tcp.header['seq_num'] + 1)
                                
    tcp.psm['disconnected_3rd_hs'] = from_('CLOSE_WAIT') + to_('LAST_ACK') + \
                                predict_(tcp.to_active and tcp.header['fin'] and \
                                    not tcp.header["ack"]) + \
                                set_(tcp.perm['passive_seq'], tcp.header['seq_num'] + 1)
                                
    tcp.psm['disconnected_4th_hs'] = from_('LAST_ACK') + to_('TERMINATE') + \
                                predict_(tcp.to_passive and tcp.header['ack'] and \
                                    tcp.header['ack_num'] == tcp.perm['passive_seq'])

    tcp.psm["rst"] = from_("*") + to_("TERMINATE") + predict_(tcp.header["rst"])
    

    tcp.buf = buffer(tcp.header['seq_num'])
    tcp.buf.op["inserter"] = insert()
    tcp.buf.op['ejector']  = while_(tcp.temp["cur_seq"] == tcp.buf.first_meta() or \
                                 tcp.header["psh"]) >> eject() + \
                             set_(tcp.temp["cur_seq"], \
                                 tcp.buf.first_meta() + tcp.payload_length)
    tcp.buf.op['out_of_window'] = while_(tcp.temp["window"] > \
                                      tcp.buf.first_meta()) >> eject() + \
                                  set_(tcp.temp["cur_seq"], \
                                      tcp.buf.first_meta() + tcp.payload_length)
    return tcp, tcp.temp

def tcp_layer_modify(tcp):
    tcp.psm["ff_passive"] = None
    tcp.psm["ff_active"] = None
        
    tcp.psm["buffering_passive"] = \
                    from_("ESTABLISHED") + \
                    to_("ESTABLISHED") + \
                    predict_(tcp.to_passive and tcp.payload_length > 0 and \
                        tcp.perm["active_seq"] < tcp.header["seq_num"] and \
                        tcp.header["seq_num"] >= tcp.perm["passive_ack"] and \
                        tcp.header["seq_num"] < tcp.perm["passive_ack"] + \
                        tcp.perm["passive_window"] << tcp.perm["passive_ws"]) + \
                    set_(tcp.temp["cur_seq"], tcp.perm["active_seq"]) + \
                    set_(tcp.temp["window"], tcp.perm["passive_ack"]) + \
                    manage_buf(["inserter", "ejector"]) +\
                    set_(tcp.perm["active_seq"], tcp.temp["cur_seq"])

    tcp.psm["buffering_active"] = \
                    from_("ESTABLISHED") + \
                    to_("ESTABLISHED") + \
                    predict_(tcp.to_active and tcp.payload_length > 0 and \
                        tcp.perm["passive_seq"] < tcp.header["seq_num"] and \
                        tcp.header["seq_num"] >= tcp.perm["active_ack"] and \
                        tcp.header["seq_num"] < tcp.perm["active_ack"] + \
                        tcp.perm["active_window"] << tcp.perm["active_ws"]) + \
                    set_(tcp.temp["cur_seq"], tcp.perm["passive_seq"]) + \
                    set_(tcp.temp["window"], tcp.perm["active_ack"]) + \
                    manage_buf(["inserter", "ejector"]) + \
                    set_(tcp.perm["passive_seq"], tcp.temp["cur_seq"])

    tcp.buf = buffer(tcp.header['seq_num'])
    tcp.buf.op["inserter"] = insert()
    tcp.buf.op['ejector']  = if_(tcp.header["psh"]) >> (assemble() + \
                                set_(tcp.temp["cur_seq"], tcp.header["seq_num"]))

    return tcp
