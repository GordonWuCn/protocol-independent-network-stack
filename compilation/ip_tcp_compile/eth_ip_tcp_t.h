#ifndef _ETH_IP_TCP_T_
#define _ETH_IP_TCP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct data_t eth_ip_tcp_data_t;
struct eth_ip_tcp_tcp_hdr_t{
	uint16_t srcport;
	uint16_t dstport;
	uint32_t seq_num;
	uint32_t ack_num;
	unsigned blank:4;
	unsigned hdr_len:4;
	unsigned fin:1;
	unsigned syn:1;
	unsigned rst:1;
	unsigned psh:1;
	unsigned ack:1;
	unsigned urg:1;
	unsigned ece:1;
	unsigned cwr:1;
	uint16_t window_size;
	uint16_t checksum;
	uint16_t urgent_pointer;
};
struct eth_ip_tcp_tcp_eol_t{
	uint8_t eol_type;
};
struct eth_ip_tcp_tcp_nop_t{
	uint8_t nop_type;
};
struct eth_ip_tcp_tcp_mss_t{
	uint8_t mss_type;
	uint8_t mss_len;
	uint16_t mss_value;
};
struct eth_ip_tcp_tcp_ws_t{
	uint8_t ws_type;
	uint8_t ws_len;
	uint8_t ws_value;
};
struct eth_ip_tcp_tcp_SACK_permitted_t{
	uint8_t SCAK_permitted_type;
	uint8_t SCAK_permitted_len;
};
struct eth_ip_tcp_tcp_SACK_0_t{
	uint8_t SACK_type;
	uint8_t SACK_len;
};
struct eth_ip_tcp_tcp_SACK_1_t{
	u_char* SACK_value;
};
struct eth_ip_tcp_tcp_TS_t{
	uint8_t TS_type;
	uint8_t TS_len;
	uint32_t TS_value;
	uint32_t TS_echo_reply;
};
struct eth_ip_tcp_tcp_cc_new_t{
	uint8_t cc_new_type;
	uint8_t cc_new_len;
	uint32_t cc_new_value;
};
struct eth_ip_tcp_tcp_mptcp_0_t{
	uint8_t mptcp_type;
	uint8_t mptcp_len;
};
struct eth_ip_tcp_tcp_mptcp_1_t{
	u_char* mptcp_value;
};
struct eth_ip_tcp_tcp_unknown_0_t{
	uint8_t unknown_type;
	uint8_t unknown_len;
};
struct eth_ip_tcp_tcp_unknown_1_t{
	u_char* unknown_value;
};
struct eth_ip_tcp_tcp_blank_t{
	uint32_t blank;
};
struct eth_ip_tcp_rubik_bitmap_t{
	unsigned eth_ip_tcp_tcp_hdr: 1;
	unsigned eth_ip_tcp_tcp_eol: 1;
	unsigned eth_ip_tcp_tcp_nop: 1;
	unsigned eth_ip_tcp_tcp_mss: 1;
	unsigned eth_ip_tcp_tcp_ws: 1;
	unsigned eth_ip_tcp_tcp_SACK_permitted: 1;
	unsigned eth_ip_tcp_tcp_SACK: 1;
	unsigned eth_ip_tcp_tcp_TS: 1;
	unsigned eth_ip_tcp_tcp_cc_new: 1;
	unsigned eth_ip_tcp_tcp_mptcp: 1;
	unsigned eth_ip_tcp_tcp_unknown: 1;
	unsigned eth_ip_tcp_tcp_blank: 1;
	unsigned blank: 4;
};
struct eth_ip_tcp_select_t {
	uint32_t src_src_addr;
	uint16_t src_srcport;
	uint32_t dst_dst_addr;
	uint16_t dst_dstport;
};
struct eth_ip_tcp_transition_bitmap_t{
	unsigned first_hs: 1;
	unsigned rst_1: 1;
	unsigned rst_2: 1;
	unsigned rst_3: 1;
	unsigned rst_4: 1;
	unsigned rst_5: 1;
	unsigned rst_6: 1;
	unsigned second_hs: 1;
	unsigned third_hs: 1;
	unsigned rst_7: 1;
	unsigned rst_8: 1;
	unsigned buffering_passive: 1;
	unsigned ff_passive: 1;
	unsigned retrx_passive: 1;
	unsigned out_of_window_passive: 1;
	unsigned buffering_active: 1;
	unsigned ff_active: 1;
	unsigned retrx_active: 1;
	unsigned out_of_window_active: 1;
	unsigned disconnected_1st_hs: 1;
	unsigned rst_9: 1;
	unsigned rst_10: 1;
	unsigned rst_11: 1;
	unsigned rst_12: 1;
	unsigned rst_13: 1;
	unsigned rst_14: 1;
	unsigned disconnected_2nd_hs: 1;
	unsigned disconnected_2nd_hs_fast: 1;
	unsigned disconnected_3rd_hs: 1;
	unsigned disconnected_4th_hs: 1;
	unsigned blank: 2;
};
struct eth_ip_tcp_instance_t {
	struct eth_ip_tcp_select_t eth_ip_tcp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	eth_ip_tcp_data_t *eth_ip_tcp_data;
	char time_record_leader;
	char* is_active_part;
	char stand;
	struct eth_ip_tcp_instance_t * pair_instance;};
void eth_ip_tcp_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_tcp_init(void);
extern struct eth_ip_ip_hdr_t* eth_ip_ip_hdr;
extern struct eth_ip_rubik_bitmap_t* eth_ip_rubik_bitmap;
extern struct eth_ip_transition_bitmap_t* eth_ip_transition_bitmap;
extern eth_ip_data_t*eth_ip_data;
#endif
