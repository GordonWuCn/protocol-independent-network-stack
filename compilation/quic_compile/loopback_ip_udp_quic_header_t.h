#ifndef _LOOPBACK_IP_UDP_QUIC_HEADER_T_
#define _LOOPBACK_IP_UDP_QUIC_HEADER_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "loopback_ip_udp_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct loopback_ip_udp_quic_header_QUICHeaderFormPacketType_t{
	uint8_t header_form_packet_type;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderPart1_t{
	uint32_t version;
	uint8_t dst_src_conn_id_len;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0_t{
	uint64_t dst_conn_id;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0_t{
	uint64_t src_conn_id;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderPart2_t{
	uint8_t payload_length_first_byte;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0_t{
	uint64_t payload_length_tail;
};
struct loopback_ip_udp_quic_header_QUICLongHeaderPart3_t{
	uint32_t packet_number;
};
struct loopback_ip_udp_quic_header_QUICShortHeader_0_t{
	uint64_t dst_conn_id;
};
struct loopback_ip_udp_quic_header_QUICShortHeader_1_t{
	uint8_t packet_number;
};
struct loopback_ip_udp_quic_header_rubik_bitmap_t{
	unsigned loopback_ip_udp_quic_header_QUICHeaderFormPacketType: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderPart1: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderPart2: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail: 1;
	unsigned loopback_ip_udp_quic_header_QUICLongHeaderPart3: 1;
	unsigned loopback_ip_udp_quic_header_QUICShortHeader: 1;
};
struct loopback_ip_udp_quic_header_select_t {
	uint32_t src_src_addr;
	uint16_t src_src_port;
	uint32_t dst_dst_addr;
	uint16_t dst_dst_port;
};
struct loopback_ip_udp_quic_header_transition_bitmap_t{
	unsigned loop: 1;
	unsigned blank: 7;
};
struct loopback_ip_udp_quic_header_instance_t {
	struct loopback_ip_udp_quic_header_select_t loopback_ip_udp_quic_header_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	char time_record_leader;
	char* is_active_part;
	char stand;
	struct loopback_ip_udp_quic_header_instance_t * pair_instance;};
void loopback_ip_udp_quic_header_parse(u_char *payload, uint32_t length, struct timeval * now);
void loopback_ip_udp_quic_header_init(void);
extern struct loopback_ip_udp_udp_hdr_t* loopback_ip_udp_udp_hdr;
extern struct loopback_ip_udp_rubik_bitmap_t* loopback_ip_udp_rubik_bitmap;
extern struct loopback_ip_udp_transition_bitmap_t* loopback_ip_udp_transition_bitmap;
extern loopback_ip_udp_data_t*loopback_ip_udp_data;
#endif
