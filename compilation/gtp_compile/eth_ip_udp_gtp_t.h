#ifndef _ETH_IP_UDP_GTP_T_
#define _ETH_IP_UDP_GTP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_udp_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct eth_ip_udp_gtp_gtp_hdr_t{
	unsigned PN:1;
	unsigned S:1;
	unsigned E:1;
	unsigned Reserved:1;
	unsigned PT:1;
	unsigned version:3;
	uint8_t MT;
	uint16_t Total_length;
	uint32_t TEID;
};
struct eth_ip_udp_gtp_var_header_t{
	uint16_t seq_no_upper;
	uint8_t NPDU_no;
	uint8_t Next_header_type;
};
struct eth_ip_udp_gtp_gtp_extension_header_0_t{
	uint8_t extension_length;
};
struct eth_ip_udp_gtp_gtp_extension_header_1_t{
	u_char* extension_data;
};
struct eth_ip_udp_gtp_gtp_extension_header_2_t{
	uint8_t next_type;
};
struct eth_ip_udp_gtp_rubik_bitmap_t{
	unsigned eth_ip_udp_gtp_gtp_hdr: 1;
	unsigned eth_ip_udp_gtp_var_header: 1;
	unsigned eth_ip_udp_gtp_gtp_extension_header: 1;
	unsigned blank: 5;
};
struct eth_ip_udp_gtp_select_t {
	uint32_t src_TEID;
	uint32_t dst_TEID;
};
struct eth_ip_udp_gtp_transition_bitmap_t{
	unsigned direct_dump: 1;
	unsigned blank: 7;
};
struct eth_ip_udp_gtp_instance_t {
	struct eth_ip_udp_gtp_select_t eth_ip_udp_gtp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
};
void eth_ip_udp_gtp_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_udp_gtp_init(void);
extern struct eth_ip_udp_udp_hdr_t* eth_ip_udp_udp_hdr;
extern struct eth_ip_udp_rubik_bitmap_t* eth_ip_udp_rubik_bitmap;
extern struct eth_ip_udp_transition_bitmap_t* eth_ip_udp_transition_bitmap;
#endif
