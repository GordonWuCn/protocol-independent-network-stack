#ifndef _LOOPBACK_IP_UDP_T_
#define _LOOPBACK_IP_UDP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "loopback_ip_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
typedef struct udp_perm_t loopback_ip_udp_data_t;
struct loopback_ip_udp_udp_hdr_t{
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t pkt_length;
	uint16_t checksum;
};
struct loopback_ip_udp_rubik_bitmap_t{
	unsigned loopback_ip_udp_udp_hdr: 1;
	unsigned blank: 7;
};
struct loopback_ip_udp_select_t {
	uint16_t src_src_port;
	uint16_t dst_dst_port;
};
struct loopback_ip_udp_transition_bitmap_t{
	unsigned direct_dump: 1;
	unsigned blank: 7;
};
struct loopback_ip_udp_instance_t {
	struct loopback_ip_udp_select_t loopback_ip_udp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	loopback_ip_udp_data_t *loopback_ip_udp_data;
};
void loopback_ip_udp_parse(u_char *payload, uint32_t length, struct timeval * now);
void loopback_ip_udp_init(void);
extern struct loopback_ip_ip_hdr_t* loopback_ip_ip_hdr;
extern struct loopback_ip_rubik_bitmap_t* loopback_ip_rubik_bitmap;
extern struct loopback_ip_transition_bitmap_t* loopback_ip_transition_bitmap;
extern loopback_ip_data_t*loopback_ip_data;
#endif
