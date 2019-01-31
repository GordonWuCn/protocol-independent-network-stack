#ifndef _ETH_IP_TCP_PPTP_T_
#define _ETH_IP_TCP_PPTP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_tcp_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct eth_ip_tcp_pptp_pptp_general_t{
	uint16_t length;
	uint16_t pptp_message_type;
	uint32_t magic_cookie;
};
struct eth_ip_tcp_pptp_start_control_connection_request_0_t{
	uint16_t SCCRQ_type;
	uint16_t SCCRQ_reserved0;
	uint16_t SCCRQ_protocol_version;
	uint16_t SCCRQ_reserved1;
	uint32_t SCCRQ_framing_capabilities;
	uint32_t SCCRQ_bearer_capabilities;
	uint16_t SCCRQ_maximum_channels;
	uint16_t SCCRQ_firmware_revision;
};
struct eth_ip_tcp_pptp_start_control_connection_request_1_t{
	u_char* SCCRQ_host_name;
};
struct eth_ip_tcp_pptp_start_control_connection_request_2_t{
	u_char* SCCRQ_vandor_name;
};
struct eth_ip_tcp_pptp_start_control_connection_reply_0_t{
	uint16_t SCCRP_type;
	uint16_t SCCRP_reserved0;
	uint16_t SCCRP_protocol_version;
	uint8_t SCCRP_result_code;
	uint8_t SCCRP_error_code;
	uint32_t SCCRP_framing_capabilities;
	uint32_t SCCRP_bearer_capabilities;
	uint16_t SCCRP_maximum_channels;
	uint16_t SCCRP_firmware_revision;
};
struct eth_ip_tcp_pptp_start_control_connection_reply_1_t{
	u_char* SCCRP_host_name;
};
struct eth_ip_tcp_pptp_start_control_connection_reply_2_t{
	u_char* SCCRP_vandor_name;
};
struct eth_ip_tcp_pptp_outgoing_call_request_0_t{
	uint16_t OCRQ_type;
	uint16_t OCRQ_reserved0;
	uint16_t OCRQ_call_ID;
	uint16_t OCRQ_call_serial_number;
	uint32_t OCRQ_minimum_BPS;
	uint32_t OCRQ_maximum_BPS;
	uint32_t OCRQ_bearer_type;
	uint32_t OCRQ_framing_type;
	uint16_t OCRQ_packet_recv_ws;
	uint16_t OCRQ_packet_processing_delay;
	uint16_t OCRQ_phone_number_length;
	uint16_t OCRQ_reserved;
};
struct eth_ip_tcp_pptp_outgoing_call_request_1_t{
	u_char* OCRQ_phone_number;
};
struct eth_ip_tcp_pptp_outgoing_call_request_2_t{
	u_char* OCRQ_subaddress;
};
struct eth_ip_tcp_pptp_outgoing_call_reply_t{
	uint16_t OCRP_type;
	uint16_t OCRP_reserved0;
	uint16_t OCRP_call_ID;
	uint16_t OCRP_peer_call_ID;
	uint8_t OCRP_result_code;
	uint8_t OCRP_error_code;
	uint16_t OCRP_cause_code;
	uint32_t OCRP_connect_speed;
	uint16_t OCRP_packet_recv_ws;
	uint16_t OCRP_packet_processing_delay;
	uint32_t OCRP_physical_channel_ID;
};
struct eth_ip_tcp_pptp_set_link_info_t{
	uint16_t SLI_type;
	uint16_t SLI_reserved0;
	uint16_t SLI_peer_call_ID;
	uint16_t SLI_reserved;
	uint32_t SLI_send_ACCM;
	uint32_t SLI_recv_ACCM;
};
struct eth_ip_tcp_pptp_echo_request_t{
	uint16_t ERQ_type;
	uint16_t ERQ_reserved0;
	uint32_t ERQ_identifier;
};
struct eth_ip_tcp_pptp_echo_reply_t{
	uint16_t ERP_type;
	uint16_t ERP_reserved0;
	uint32_t ERP_identifier;
	uint8_t ERP_result_code;
	uint8_t ERP_error_code;
	uint16_t ERP_reserved1;
};
struct eth_ip_tcp_pptp_rubik_bitmap_t{
	unsigned eth_ip_tcp_pptp_pptp_general: 1;
	unsigned eth_ip_tcp_pptp_start_control_connection_request: 1;
	unsigned eth_ip_tcp_pptp_start_control_connection_reply: 1;
	unsigned eth_ip_tcp_pptp_outgoing_call_request: 1;
	unsigned eth_ip_tcp_pptp_outgoing_call_reply: 1;
	unsigned eth_ip_tcp_pptp_set_link_info: 1;
	unsigned eth_ip_tcp_pptp_echo_request: 1;
	unsigned eth_ip_tcp_pptp_echo_reply: 1;
};
struct eth_ip_tcp_pptp_select_t {
	uint32_t src_src_addr;
	uint32_t dst_dst_addr;
};
struct eth_ip_tcp_pptp_transition_bitmap_t{
	unsigned SCCRQ_sent: 1;
	unsigned SCCRP_sent: 1;
	unsigned OCRQ_sent: 1;
	unsigned OCRP_sent: 1;
	unsigned session_config_passive: 1;
	unsigned session_config_active: 1;
	unsigned keep_alive: 1;
	unsigned maintain_connection: 1;
};
struct eth_ip_tcp_pptp_instance_t {
	struct eth_ip_tcp_pptp_select_t eth_ip_tcp_pptp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	char time_record_leader;
	char* is_active_part;
	char stand;
	struct eth_ip_tcp_pptp_instance_t * pair_instance;};
void eth_ip_tcp_pptp_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_tcp_pptp_init(void);
extern struct eth_ip_tcp_tcp_hdr_t* eth_ip_tcp_tcp_hdr;
extern struct eth_ip_tcp_tcp_eol_t* eth_ip_tcp_tcp_eol;
extern struct eth_ip_tcp_tcp_nop_t* eth_ip_tcp_tcp_nop;
extern struct eth_ip_tcp_tcp_mss_t* eth_ip_tcp_tcp_mss;
extern struct eth_ip_tcp_tcp_ws_t* eth_ip_tcp_tcp_ws;
extern struct eth_ip_tcp_tcp_SACK_permitted_t* eth_ip_tcp_tcp_SACK_permitted;
extern struct eth_ip_tcp_tcp_SACK_0_t* eth_ip_tcp_tcp_SACK_0;
extern struct eth_ip_tcp_tcp_SACK_1_t* eth_ip_tcp_tcp_SACK_1;
extern struct eth_ip_tcp_tcp_TS_t* eth_ip_tcp_tcp_TS;
extern struct eth_ip_tcp_tcp_cc_new_t* eth_ip_tcp_tcp_cc_new;
extern struct eth_ip_tcp_rubik_bitmap_t* eth_ip_tcp_rubik_bitmap;
extern struct eth_ip_tcp_transition_bitmap_t* eth_ip_tcp_transition_bitmap;
extern eth_ip_tcp_data_t*eth_ip_tcp_data;
#endif
