#ifndef _ETH_T_
#define _ETH_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct eth_eth_header_t{
	uint16_t eth_dst_upper;
	uint16_t eth_dst_middle;
	uint16_t eth_dst_lower;
	uint16_t eth_src_upper;
	uint16_t eth_src_middle;
	uint16_t eth_src_lower;
	uint16_t eth_type;
};
struct eth_rubik_bitmap_t{
	unsigned eth_eth_header: 1;
	unsigned blank: 7;
};
struct eth_select_t {
	uint16_t src_eth_src_upper;
	uint16_t src_eth_src_middle;
	uint16_t src_eth_src_lower;
	uint16_t dst_eth_dst_upper;
	uint16_t dst_eth_dst_middle;
	uint16_t dst_eth_dst_lower;
};
struct eth_transition_bitmap_t{
	unsigned incoming: 1;
	unsigned blank: 7;
};
struct eth_instance_t {
	struct eth_select_t eth_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
};
void eth_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_init(void);
#endif
