#ifndef _LOOPBACK_T_
#define _LOOPBACK_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct loopback_loopback_header_t{
	uint32_t family;
};
struct loopback_rubik_bitmap_t{
	unsigned loopback_loopback_header: 1;
	unsigned blank: 7;
};
struct loopback_select_t {
	uint32_t src_family;
	uint32_t dst_family;
};
struct loopback_transition_bitmap_t{
	unsigned incoming: 1;
	unsigned blank: 7;
};
struct loopback_instance_t {
	struct loopback_select_t loopback_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
};
void loopback_parse(u_char *payload, uint32_t length, struct timeval * now);
void loopback_init(void);
#endif
