from rubik import header_t, byte, connectionless, seq_parse, selector, \
    auxiliary_data, connection_oriented, if_, psm, from_, to_, \
    predict_, layer, code_generator, set_, ptr, buffer, insert, \
    eject, while_, manage_buf, bit
class QUICHeaderFormPacketType(header_t):
    header_form_packet_type = byte(1)


class QUICLongHeaderPart1(header_t):
    version = byte(4)
    dst_src_conn_id_len = byte(1)


class QUICLongHeaderOptionalDstConnID(header_t):
    dst_conn_id = byte(((QUICLongHeaderPart1.dst_src_conn_id_len & 0xF0) >> 4) + 3)


class QUICLongHeaderOptionalSrcConnID(header_t):
    src_conn_id = byte((QUICLongHeaderPart1.dst_src_conn_id_len & 0x0F) + 3)


class QUICLongHeaderPart2(header_t):
    payload_length_first_byte = byte(1)


class QUICLongHeaderOptionalPayloadLengthTail(header_t):
    payload_length_tail = \
        byte((1 << ((QUICLongHeaderPart2.payload_length_first_byte & 0xC0) >> 6)) - 1)


class QUICLongHeaderPart3(header_t):
    packet_number = byte(4)

class udp_perm(header_t):
  dst_conn_id_len = bit(8)

def quic_header_layer(ip, udp):
    udp.perm = auxiliary_data(udp_perm)
    class QUICShortHeader(header_t):
        global udp
        dst_conn_id = byte(udp.perm['dst_conn_id_len'])
        packet_number = byte(1)

    udp.selector = if_(1) >> selector(udp.src_meta, udp.dst_meta)


    quic_header_protocol = connection_oriented()
    quic_header_protocol.header = \
        seq_parse([QUICHeaderFormPacketType]) + \
        (if_(QUICHeaderFormPacketType.header_form_packet_type & 0x80 != 0) >> \
            seq_parse([QUICLongHeaderPart1]) + \
            (if_(QUICLongHeaderPart1.dst_src_conn_id_len & 0xF0 != 0) >> \
                seq_parse([QUICLongHeaderOptionalDstConnID])) + \
            (if_(QUICLongHeaderPart1.dst_src_conn_id_len & 0x0F != 0) >> \
                seq_parse([QUICLongHeaderOptionalSrcConnID])) + \
            seq_parse([QUICLongHeaderPart2]) + \
            (if_(QUICLongHeaderPart2.payload_length_first_byte & 0xC0 != 0) >> \
                seq_parse([QUICLongHeaderOptionalPayloadLengthTail])) + \
            seq_parse([QUICLongHeaderPart3])) + \
        (if_(QUICHeaderFormPacketType.header_form_packet_type & 0x80 == 0) >> \
            seq_parse([QUICShortHeader]))
    quic_header_protocol.preprocess = \
        if_(QUICLongHeaderPart1) >> \
            set_(udp.perm['dst_conn_id_len'], \
                ((quic_header_protocol.header['dst_src_conn_id_len'] & 0xF0) >> 4) + 3)
    quic_header_protocol.src_meta = \
        [ip.header['src_addr'], \
         udp.header['src_port']]
    quic_header_protocol.dst_meta = \
        [ip.header['dst_addr'], \
         udp.header['dst_port']]
    quic_header_protocol.selector = \
        if_(1) >> \
            selector(quic_header_protocol.src_meta, quic_header_protocol.dst_meta)
    quic_header_protocol.psm = \
        psm(['start'], start_state='start')
    quic_header_protocol.psm['loop'] = \
        from_('start') + to_('start') + predict_(1) + \
        set_(quic_header_protocol.SDU, quic_header_protocol.payload) + \
        set_(quic_header_protocol.SDU_length, quic_header_protocol.payload_length)

    return quic_header_protocol

