#ifndef _LOOPBACK_IP_T_
#define _LOOPBACK_IP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "loopback_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct pure_ip_data_t loopback_ip_data_t;
struct loopback_ip_ip_hdr_t{
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
struct loopback_ip_rubik_bitmap_t{
	unsigned loopback_ip_ip_hdr: 1;
	unsigned blank: 7;
};
struct loopback_ip_select_t {
	uint32_t src_src_addr;
	uint32_t dst_dst_addr;
};
struct loopback_ip_transition_bitmap_t{
	unsigned no_buffer: 1;
	unsigned has_buffer: 1;
	unsigned still_has_buffer: 1;
	unsigned last_buffer: 1;
	unsigned blank: 4;
};
struct loopback_ip_instance_t {
	struct loopback_ip_select_t loopback_ip_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	loopback_ip_data_t *loopback_ip_data;
};
void loopback_ip_parse(u_char *payload, uint32_t length, struct timeval * now);
void loopback_ip_init(void);
extern struct loopback_loopback_header_t* loopback_loopback_header;
extern struct loopback_rubik_bitmap_t* loopback_rubik_bitmap;
extern struct loopback_transition_bitmap_t* loopback_transition_bitmap;
#endif
