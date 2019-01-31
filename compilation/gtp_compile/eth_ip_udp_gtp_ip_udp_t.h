#ifndef _ETH_IP_UDP_GTP_IP_UDP_T_
#define _ETH_IP_UDP_GTP_IP_UDP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_udp_gtp_ip_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct eth_ip_udp_gtp_ip_udp_udp_hdr_t{
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t pkt_length;
	uint16_t checksum;
};
struct eth_ip_udp_gtp_ip_udp_rubik_bitmap_t{
	unsigned eth_ip_udp_gtp_ip_udp_udp_hdr: 1;
	unsigned blank: 7;
};
struct eth_ip_udp_gtp_ip_udp_select_t {
	uint16_t src_src_port;
	uint16_t dst_dst_port;
};
struct eth_ip_udp_gtp_ip_udp_transition_bitmap_t{
	unsigned direct_dump: 1;
	unsigned blank: 7;
};
struct eth_ip_udp_gtp_ip_udp_instance_t {
	struct eth_ip_udp_gtp_ip_udp_select_t eth_ip_udp_gtp_ip_udp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
};
void eth_ip_udp_gtp_ip_udp_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_udp_gtp_ip_udp_init(void);
extern struct eth_ip_udp_gtp_ip_ip_hdr_t* eth_ip_udp_gtp_ip_ip_hdr;
extern struct eth_ip_udp_gtp_ip_rubik_bitmap_t* eth_ip_udp_gtp_ip_rubik_bitmap;
extern struct eth_ip_udp_gtp_ip_transition_bitmap_t* eth_ip_udp_gtp_ip_transition_bitmap;
extern eth_ip_udp_gtp_ip_data_t*eth_ip_udp_gtp_ip_data;
#endif
