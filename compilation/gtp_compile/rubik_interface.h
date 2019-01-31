#ifndef RUBIK_INTERFACE_H
#define RUBIK_INTERFACE_H

#include <stdint.h>
struct pure_ip_data_t {
	uint32_t buf_len;
};
struct pure_ip_temp_data_t {
	uint16_t frag_offset;
	uint32_t buf_len;
};
struct data_t {
	uint32_t cur_seq_num;
	uint32_t active_buf_len;
	uint32_t passive_buf_len;
	uint32_t active_seq;
	uint32_t passive_seq;
	uint64_t active_window;
	uint64_t passive_window;
	uint32_t active_ws;
	uint32_t passive_ws;
	uint32_t active_ack;
	uint32_t passive_ack;
};
struct temp_t {
	uint8_t tcp_hdr_len;
	uint32_t buf_len;
	uint32_t cur_seq;
	uint32_t window;
};




#endif