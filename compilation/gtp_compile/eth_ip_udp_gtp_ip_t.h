#ifndef _ETH_IP_UDP_GTP_IP_T_
#define _ETH_IP_UDP_GTP_IP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_udp_gtp_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct pure_ip_data_t eth_ip_udp_gtp_ip_data_t;
struct eth_ip_udp_gtp_ip_ip_hdr_t{
	unsigned hdr_len:4;
	unsigned version:4;
	uint8_t TOS;
	uint16_t total_len;
	uint16_t identifier;
	unsigned frag_offset_upper:5;
	unsigned more_frag:1;
	unsigned dont_frag:1;
	unsigned blank:1;
	uint8_t frag_offset_lower;
	uint8_t TTL;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t src_addr;
	uint32_t dst_addr;
};
struct eth_ip_udp_gtp_ip_rubik_bitmap_t{
	unsigned eth_ip_udp_gtp_ip_ip_hdr: 1;
	unsigned blank: 7;
};
struct eth_ip_udp_gtp_ip_select_t {
	uint32_t src_src_addr;
	uint32_t dst_dst_addr;
};
struct eth_ip_udp_gtp_ip_transition_bitmap_t{
	unsigned no_buffer: 1;
	unsigned has_buffer: 1;
	unsigned still_has_buffer: 1;
	unsigned last_buffer: 1;
	unsigned blank: 4;
};
struct eth_ip_udp_gtp_ip_instance_t {
	struct eth_ip_udp_gtp_ip_select_t eth_ip_udp_gtp_ip_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	eth_ip_udp_gtp_ip_data_t *eth_ip_udp_gtp_ip_data;
};
void eth_ip_udp_gtp_ip_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_udp_gtp_ip_init(void);
extern struct eth_ip_udp_gtp_gtp_hdr_t* eth_ip_udp_gtp_gtp_hdr;
extern struct eth_ip_udp_gtp_var_header_t* eth_ip_udp_gtp_var_header;
extern struct eth_ip_udp_gtp_gtp_extension_header_0_t* eth_ip_udp_gtp_gtp_extension_header_0;
extern struct eth_ip_udp_gtp_gtp_extension_header_1_t* eth_ip_udp_gtp_gtp_extension_header_1;
extern struct eth_ip_udp_gtp_gtp_extension_header_2_t* eth_ip_udp_gtp_gtp_extension_header_2;
extern struct eth_ip_udp_gtp_rubik_bitmap_t* eth_ip_udp_gtp_rubik_bitmap;
extern struct eth_ip_udp_gtp_transition_bitmap_t* eth_ip_udp_gtp_transition_bitmap;
#endif
