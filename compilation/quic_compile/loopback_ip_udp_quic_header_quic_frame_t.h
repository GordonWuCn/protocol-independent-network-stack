#ifndef _LOOPBACK_IP_UDP_QUIC_HEADER_QUIC_FRAME_T_
#define _LOOPBACK_IP_UDP_QUIC_HEADER_QUIC_FRAME_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "loopback_ip_udp_quic_header_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct QUICFramePermData_t loopback_ip_udp_quic_header_quic_frame_data_t;
struct loopback_ip_udp_quic_header_quic_frame_QUICFrame_t{
	uint8_t frame_type;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0_t{
	uint16_t error_code;
	uint8_t reason_phrase_length;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1_t{
	u_char* reason_phrase;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_0_t{
	unsigned last_ack_lower:6;
	unsigned last_ack_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_1_t{
	u_char* last_ack_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_2_t{
	unsigned ack_delay_lower:6;
	unsigned ack_delay_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_3_t{
	u_char* ack_delay_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_4_t{
	unsigned ack_block_count_lower:6;
	unsigned ack_block_count_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_5_t{
	u_char* ack_block_count_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_6_t{
	unsigned ack_block_lower:6;
	unsigned ack_block_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_7_t{
	u_char* ack_block_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxData_t{
	uint8_t maximum_data;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0_t{
	unsigned max_data_stream_id_lower:6;
	unsigned max_data_stream_id_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1_t{
	uint64_t max_data_stream_id_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2_t{
	unsigned max_stream_data_lower:6;
	unsigned max_stream_data_upper:2;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3_t{
	u_char* max_stream_data_extra;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID_t{
	uint8_t stream_id;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0_t{
	u_char* stream_id_tail;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset_t{
	uint8_t frame_offset;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0_t{
	uint64_t frame_offset_tail;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength_t{
	uint8_t frame_length;
};
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0_t{
	uint64_t frame_length_tail;
};
struct loopback_ip_udp_quic_header_quic_frame_rubik_bitmap_t{
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICFrame: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICACK: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICMaxData: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength: 1;
	unsigned loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail: 1;
	unsigned blank: 5;
};
struct loopback_ip_udp_quic_header_quic_frame_select_t {
	uint32_t src_src_addr;
	uint16_t src_src_port;
	uint8_t src_stream_id;
	uint32_t dst_dst_addr;
	uint16_t dst_dst_port;
	uint8_t dst_stream_id;
	u_char* src_stream_id_tail;
	int src_length_stream_id_tail;
	u_char* dst_stream_id_tail;
	int dst_length_stream_id_tail;
};
struct loopback_ip_udp_quic_header_quic_frame_transition_bitmap_t{
	unsigned other_frame: 1;
	unsigned more_frag: 1;
	unsigned receiving_fin: 1;
	unsigned receiving_normal_frag: 1;
	unsigned receiving_all: 1;
	unsigned first_is_fin: 1;
	unsigned blank: 2;
};
struct loopback_ip_udp_quic_header_quic_frame_instance_t {
	struct loopback_ip_udp_quic_header_quic_frame_select_t loopback_ip_udp_quic_header_quic_frame_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	loopback_ip_udp_quic_header_quic_frame_data_t *loopback_ip_udp_quic_header_quic_frame_data;
};
void loopback_ip_udp_quic_header_quic_frame_parse(u_char *payload, uint32_t length, struct timeval * now);
void loopback_ip_udp_quic_header_quic_frame_init(void);
extern struct loopback_ip_udp_quic_header_QUICHeaderFormPacketType_t* loopback_ip_udp_quic_header_QUICHeaderFormPacketType;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderPart1_t* loopback_ip_udp_quic_header_QUICLongHeaderPart1;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0_t* loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0_t* loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderPart2_t* loopback_ip_udp_quic_header_QUICLongHeaderPart2;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0_t* loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0;
extern struct loopback_ip_udp_quic_header_QUICLongHeaderPart3_t* loopback_ip_udp_quic_header_QUICLongHeaderPart3;
extern struct loopback_ip_udp_quic_header_QUICShortHeader_0_t* loopback_ip_udp_quic_header_QUICShortHeader_0;
extern struct loopback_ip_udp_quic_header_QUICShortHeader_1_t* loopback_ip_udp_quic_header_QUICShortHeader_1;
extern struct loopback_ip_udp_quic_header_rubik_bitmap_t* loopback_ip_udp_quic_header_rubik_bitmap;
extern struct loopback_ip_udp_quic_header_transition_bitmap_t* loopback_ip_udp_quic_header_transition_bitmap;
#endif
