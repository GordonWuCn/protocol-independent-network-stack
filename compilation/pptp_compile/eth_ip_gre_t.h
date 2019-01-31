#ifndef _ETH_IP_GRE_T_
#define _ETH_IP_GRE_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct GRE_perm_t eth_ip_gre_data_t;
struct eth_ip_gre_GRE_header_t{
	unsigned recursion_control:3;
	unsigned strict_source_route:1;
	unsigned S:1;
	unsigned K:1;
	unsigned R:1;
	unsigned C:1;
	unsigned version:3;
	unsigned reserved:4;
	unsigned A:1;
	uint16_t protocol;
	uint16_t payload_length;
	uint16_t call_ID;
};
struct eth_ip_gre_GRE_sequence_number_t{
	uint32_t sequence_number;
};
struct eth_ip_gre_GRE_ack_number_t{
	uint32_t ack_number;
};
struct eth_ip_gre_rubik_bitmap_t{
	unsigned eth_ip_gre_GRE_header: 1;
	unsigned eth_ip_gre_GRE_sequence_number: 1;
	unsigned eth_ip_gre_GRE_ack_number: 1;
	unsigned blank: 5;
};
struct eth_ip_gre_select_t {
	uint32_t src_src_addr;
	uint32_t dst_dst_addr;
};
struct eth_ip_gre_transition_bitmap_t{
	unsigned tunneling_p: 1;
	unsigned tunneling_a: 1;
	unsigned only_ack_p: 1;
	unsigned only_ack_a: 1;
	unsigned blank: 4;
};
struct eth_ip_gre_instance_t {
	struct eth_ip_gre_select_t eth_ip_gre_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	eth_ip_gre_data_t *eth_ip_gre_data;
	char time_record_leader;
	char* is_active_part;
	char stand;
	struct eth_ip_gre_instance_t * pair_instance;};
void eth_ip_gre_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_gre_init(void);
extern struct eth_ip_ip_hdr_t* eth_ip_ip_hdr;
extern struct eth_ip_rubik_bitmap_t* eth_ip_rubik_bitmap;
extern struct eth_ip_transition_bitmap_t* eth_ip_transition_bitmap;
extern eth_ip_data_t*eth_ip_data;
#endif
