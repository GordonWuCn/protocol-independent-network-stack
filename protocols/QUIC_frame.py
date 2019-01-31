from rubik import header_t, byte, connectionless, seq_parse, selector, \
    auxiliary_data, connection_oriented, if_, psm, from_, to_, \
    predict_, layer, code_generator, set_, ptr, buffer, insert, \
    eject, while_, manage_buf, bit

class QUICFrame(header_t):
    frame_type = byte(1)


class QUICStreamFrameStreamID(header_t):
    stream_id = byte(1)


class QUICStreamFrameStreamIDTail(header_t):
    stream_id_tail = \
        ptr((1 << ((QUICStreamFrameStreamID.stream_id & 0xC0) >> 6)) - 1)


class QUICStreamFrameOffset(header_t):
    frame_offset = byte(1)


class QUICStreamFrameOffsetTail(header_t):
    frame_offset_tail = \
        byte((1 << ((QUICStreamFrameOffset.frame_offset & 0xC0) >> 6)) - 1)


class QUICStreamFrameLength(header_t):
    frame_length = byte(1)


class QUICStreamFrameLengthTail(header_t):
    frame_length_tail = \
        byte((1 << ((QUICStreamFrameLength.frame_length & 0xC0) >> 6)) - 1)


class QUICConnectionClose(header_t):
    error_code = bit(16)
    reason_phrase_length = bit(8)
    reason_phrase = ptr(reason_phrase_length)

class QUICACK(header_t):
    last_ack_upper = bit(2)
    last_ack_lower = bit(6)
    last_ack_extra = ptr((1 << last_ack_upper + 0) - 1)
    ack_delay_upper = bit(2)
    ack_delay_lower = bit(6)
    ack_delay_extra = ptr((1 << ack_delay_upper + 0) - 1)
    ack_block_count_upper = bit(2)
    ack_block_count_lower = bit(6)
    ack_block_count_extra = ptr((1 << ack_block_count_upper + 0) - 1)
    ack_block_upper = bit(2)
    ack_block_lower = bit(6)
    ack_block_extra = ptr((1 << ack_block_upper + 0) - 1)

class QUICMaxStreamData(header_t):
    max_data_stream_id_upper = bit(2)
    max_data_stream_id_lower = bit(6)
    max_data_stream_id_extra = bit((1 << max_data_stream_id_upper + 0) - 1)
    max_stream_data_upper = bit(2)
    max_stream_data_lower = bit(6)
    max_stream_data_extra = ptr((1 << max_stream_data_upper + 0) - 1)

class QUICMaxData(header_t):
    maximum_data = bit(8)

class QUICFrameTempData(header_t):
    length = byte(4)
    offset = byte(8)
    payload_len = byte(4)

class QUICFramePermData(header_t):
    accept_length = byte(4, 0)
    expect_length = byte(4)

def quic_frame_layer(ip, udp):
    quic_frame_protocol = connectionless()
    quic_frame_protocol.header = \
        seq_parse([QUICFrame]) + \
        (if_(QUICFrame.frame_type & 0xF0 == 0 and QUICFrame.frame_type == 2) >> \
            seq_parse([QUICConnectionClose])) + \
        (if_(QUICFrame.frame_type & 0xF0 == 0 and QUICFrame.frame_type == 0x0D) >> \
            seq_parse([QUICACK])) + \
        (if_(QUICFrame.frame_type & 0xF0 == 0 and QUICFrame.frame_type == 0x04) >> \
            seq_parse([QUICMaxData])) + \
        (if_(QUICFrame.frame_type & 0xF0 == 0 and QUICFrame.frame_type == 0x05) >> \
            seq_parse([QUICMaxStreamData])) + \
        (if_(QUICFrame.frame_type & 0xF8 == 0x10) >> \
            seq_parse([QUICStreamFrameStreamID]) + \
            (if_(QUICStreamFrameStreamID.stream_id & 0xC0 != 0) >> \
                seq_parse([QUICStreamFrameStreamIDTail])) + \
            (if_(QUICFrame.frame_type & 0x04 != 0) >> \
                seq_parse([QUICStreamFrameOffset]) + \
                (if_(QUICStreamFrameOffset.frame_offset & 0xC0 != 0) >> \
                    seq_parse([QUICStreamFrameOffsetTail]))) + \
            (if_(QUICFrame.frame_type & 0x02 != 0) >> \
                seq_parse([QUICStreamFrameLength]) + \
                (if_(QUICStreamFrameLength.frame_length & 0xC0 != 0) >> \
                    seq_parse([QUICStreamFrameLengthTail]))))


    quic_frame_protocol.temp = auxiliary_data(QUICFrameTempData)
    quic_frame_protocol.preprocess = \
        (if_(quic_frame_protocol.header["frame_type"] & 0xF0 == 0) >> \
            (if_(quic_frame_protocol.header["frame_type"] == 0x0E) >> \
                set_(quic_frame_protocol.temp['length'], 9)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x0D) >> \
                (if_(quic_frame_protocol.header["ack_block_count_lower"] == 0) >> \
                    set_(quic_frame_protocol.temp['length'], \
                        (1 << quic_frame_protocol.header["last_ack_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_delay_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_count_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_upper"] + 0) + 1) \
                ) + \
                (if_(not quic_frame_protocol.header["ack_block_count_upper"] and \
                        quic_frame_protocol.header["ack_block_count_lower"] != 0) >> \
                    set_(quic_frame_protocol.temp['length'], \
                        (1 << quic_frame_protocol.header["last_ack_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_delay_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_count_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_upper"] + 0) + 1 + \
                        quic_frame_protocol.payload_length) \
                )  + \
                (if_(quic_frame_protocol.header["ack_block_count_upper"]) >> \
                    set_(quic_frame_protocol.temp['length'], \
                        (1 << quic_frame_protocol.header["last_ack_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_delay_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_count_upper"] + 0) + \
                        (1 << quic_frame_protocol.header["ack_block_upper"] + 0) + 1 + \
                        quic_frame_protocol.payload_length) \
                ) \
            ) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x04) >> \
                set_(quic_frame_protocol.temp['length'], 1 + (1 << ((quic_frame_protocol.header["maximum_data"] & 0xC0) >> 6)))) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x0F) >> \
                set_(quic_frame_protocol.temp['length'], 9)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x00) >> \
                set_(quic_frame_protocol.temp['length'], 1 + quic_frame_protocol.payload_length)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x07) >> \
                set_(quic_frame_protocol.temp['length'], 1)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x06) >> \
                set_(quic_frame_protocol.temp['length'], 3)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x0C) >> \
                set_(quic_frame_protocol.temp['length'], 4)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x05) >> \
                set_(quic_frame_protocol.temp['length'], \
                    (1 << quic_frame_protocol.header["max_stream_data_upper"] + 0) + \
                    (1 << quic_frame_protocol.header["max_data_stream_id_upper"] + 0) + 1)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x01) >> \
                set_(quic_frame_protocol.temp['length'], 5)) + \
            (if_(quic_frame_protocol.header["frame_type"] == 0x02) >> \
                set_(quic_frame_protocol.temp['length'], 4 + \
                    quic_frame_protocol.header["reason_phrase_length"]))) + \
        (if_(quic_frame_protocol.header["frame_type"] & 0xF0 != 0) >> \
            ((if_(quic_frame_protocol.header['frame_type'] & 0x04 == 0) >> \
                set_(quic_frame_protocol.temp['offset'], 0)) + \
            (if_(quic_frame_protocol.header['frame_type'] & 0x04 != 0) >> \
                (if_(quic_frame_protocol.header['frame_offset'] & 0xC0 == 0) >> \
                    set_(quic_frame_protocol.temp['offset'], \
                        quic_frame_protocol.header['frame_offset'])) + \
                (if_((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6 == 1) >> \
                    set_(quic_frame_protocol.temp['offset'], \
                        ((quic_frame_protocol.header['frame_offset'] & 0x3F) << 8) + \
                        quic_frame_protocol.header['frame_offset_tail'])) + \
                (if_((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6 == 2) >> \
                    set_(quic_frame_protocol.temp['offset'], \
                        ((quic_frame_protocol.header['frame_offset'] & 0x3F) << 16) + \
                        quic_frame_protocol.header['frame_offset_tail'])) + \
                (if_((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6 == 3) >> \
                    set_(quic_frame_protocol.temp['offset'], \
                        ((quic_frame_protocol.header['frame_offset'] & 0x3F) << 24) + \
                        quic_frame_protocol.header['frame_offset_tail']))) + \
            (if_(quic_frame_protocol.header['frame_type'] & 0x02 == 0) >> \
                set_(quic_frame_protocol.temp['length'], 0)) + \
            (if_(quic_frame_protocol.header['frame_type'] & 0x02 != 0) >> \
                (if_((quic_frame_protocol.header['frame_length'] & 0xC0) == 0) >> \
                    (set_(quic_frame_protocol.temp["payload_len"], \
                        quic_frame_protocol.header['frame_length']) + \
                    set_(quic_frame_protocol.temp['length'], \
                        quic_frame_protocol.header['frame_length'] + \
                        (1 << ((quic_frame_protocol.header["stream_id"] & 0xC0) >> 6)) + 2) + \
                    (if_(QUICStreamFrameOffset) >> \
                        set_(quic_frame_protocol.temp['length'], \
                            quic_frame_protocol.temp["length"] + \
                            1 << ((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6)) \
                        ))) + \
                (if_((quic_frame_protocol.header['frame_length'] & 0xC0) >> 6 == 1) >> \
                    (set_(quic_frame_protocol.temp["payload_len"], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 8) + \
                        quic_frame_protocol.header['frame_length_tail']) + \
                    set_(quic_frame_protocol.temp['length'], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 8) + \
                        quic_frame_protocol.header['frame_length_tail'] + \
                        (1 << ((quic_frame_protocol.header["stream_id"] & 0xC0) >> 6)) + 3) + \
                    (if_(QUICStreamFrameOffset) >> \
                        set_(quic_frame_protocol.temp['length'], \
                            quic_frame_protocol.temp["length"] + \
                            1 << ((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6)) \
                        ))) + \
                (if_((quic_frame_protocol.header['frame_length'] & 0xC0) >> 6 == 2) >> \
                    (set_(quic_frame_protocol.temp["payload_len"], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 16) + \
                        quic_frame_protocol.header['frame_length_tail']) + \
                    set_(quic_frame_protocol.temp['length'], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 16) + \
                        quic_frame_protocol.header['frame_length_tail'] + \
                        (1 << ((quic_frame_protocol.header["stream_id"] & 0xC0) >> 6)) + 5) + \
                    (if_(QUICStreamFrameOffset) >> \
                        set_(quic_frame_protocol.temp['length'], \
                            quic_frame_protocol.temp["length"] + \
                            1 << ((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6)) \
                        ))) + \
                (if_((quic_frame_protocol.header['frame_length'] & 0xC0) >> 6 == 3) >> \
                    (set_(quic_frame_protocol.temp["payload_len"], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 24) + \
                        quic_frame_protocol.header['frame_length_tail']) + \
                    set_(quic_frame_protocol.temp['length'], \
                        ((quic_frame_protocol.header['frame_length'] & 0x3F) << 24) + \
                        quic_frame_protocol.header['frame_length_tail'] + \
                        (1 << ((quic_frame_protocol.header["stream_id"] & 0xC0) >> 6)) + 9))+ \
                    (if_(QUICStreamFrameOffset) >> \
                        set_(quic_frame_protocol.temp['length'], \
                            quic_frame_protocol.temp["length"] + \
                            1 << ((quic_frame_protocol.header['frame_offset'] & 0xC0) >> 6)) \
                        )))))

    quic_frame_protocol.src_meta = [ \
        ip.header['src_addr'], \
        udp.header['src_port'], \
        quic_frame_protocol.header['stream_id'], \
        quic_frame_protocol.header['stream_id_tail'], \
    ]
    quic_frame_protocol.dst_meta = [ \
        ip.header['dst_addr'], \
        udp.header['dst_port'], \
        quic_frame_protocol.header['stream_id'], \
        quic_frame_protocol.header['stream_id_tail'], \
    ]

    quic_frame_protocol.selector = \
        if_(quic_frame_protocol.header["frame_type"] & 0xF0 != 0) >> \
        selector(quic_frame_protocol.src_meta, quic_frame_protocol.dst_meta)



    quic_frame_protocol.perm = auxiliary_data(QUICFramePermData)


    quic_frame_protocol.buf = buffer( \
        quic_frame_protocol.temp['offset'], None, quic_frame_protocol.temp['payload_len'])

    # TODO: states for all data has passed middlebox
    quic_frame_protocol.psm = psm(['dump', 'frag'], start_state="dump")

    quic_frame_protocol.psm['other_frame'] = \
        from_("dump") + to_("dump") + \
        predict_(not QUICStreamFrameStreamID)

    quic_frame_protocol.psm['more_frag'] = \
        from_('dump') + to_('frag') + \
        predict_(QUICStreamFrameStreamID and quic_frame_protocol.header['frame_type'] & 0x01 == 0) + \
        set_(quic_frame_protocol.perm['expect_length'], 0) + \
        manage_buf(['insertor', 'ejector'])

    quic_frame_protocol.psm['receiving_fin'] = \
        from_('frag') + to_('frag') + \
        predict_(QUICStreamFrameStreamID and quic_frame_protocol.header['frame_type'] & 0x01 != 0) + \
        set_( \
            quic_frame_protocol.perm['expect_length'], \
            quic_frame_protocol.temp['offset'] + quic_frame_protocol.temp['length'] \
        ) + \
        manage_buf(['insertor', 'ejector'])

    quic_frame_protocol.psm['receiving_normal_frag'] = \
        from_('frag') + to_('frag') + \
        predict_(QUICStreamFrameStreamID and quic_frame_protocol.header['frame_type'] & 0x01 == 0) + \
        manage_buf(['insertor', 'ejector'])

    quic_frame_protocol.psm['receiving_all'] = \
        from_('frag') + to_('dump') + \
        predict_( \
            QUICStreamFrameStreamID and (not quic_frame_protocol.perm['expect_length'] == 0 or \
                quic_frame_protocol.header['frame_type'] & 0x01 != 0) and \
            not quic_frame_protocol.buf.has_hole() \
        ) + \
        manage_buf(['insertor', 'ejector'])

    quic_frame_protocol.psm['first_is_fin'] = \
        from_('dump') + to_('frag') + \
        predict_(QUICStreamFrameStreamID and quic_frame_protocol.header['frame_type'] & 0x01 != 0) + \
        manage_buf(['insertor', 'ejector'])


    quic_frame_protocol.buf.op['insertor'] = insert()
    quic_frame_protocol.buf.op['ejector'] = while_(quic_frame_protocol.buf.first_meta() == \
        quic_frame_protocol.perm['accept_length']) >> eject() + \
        set_(quic_frame_protocol.perm['accept_length'], \
            quic_frame_protocol.perm['accept_length'] + \
            quic_frame_protocol.SDU_length)
    return quic_frame_protocol, quic_frame_protocol.temp
