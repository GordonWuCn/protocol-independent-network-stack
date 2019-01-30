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
struct udp_perm_t {
	uint8_t dst_conn_id_len;
};
struct QUICFrameTempData_t {
	uint32_t length;
	uint64_t offset;
	uint32_t payload_len;
};
struct QUICFramePermData_t {
	uint32_t accept_length;
	uint32_t expect_length;
};




#endif