#ifndef _ETH_IP_GRE_PPP_T_
#define _ETH_IP_GRE_PPP_T_
#include <stdint.h>
#include <sys/types.h>
#include "tommyds/tommy.h"
#include "eth_ip_gre_t.h"
#include "rubik_interface.h"
typedef void(*automaton)(void);
struct eth_ip_gre_ppp_PPP_header_t{
	uint8_t address;
	uint8_t control;
	uint16_t protocol;
};
struct eth_ip_gre_ppp_PPP_CHAP_header_0_t{
	uint8_t CHAP_code;
	uint8_t CHAP_ID;
	uint16_t CHAP_length;
};
struct eth_ip_gre_ppp_PPP_CHAP_header_1_t{
	u_char* CHAP_data;
};
struct eth_ip_gre_ppp_PPP_CCP_header_0_t{
	uint8_t CCP_code;
	uint8_t CCP_ID;
	uint16_t CCP_length;
};
struct eth_ip_gre_ppp_PPP_CCP_header_1_t{
	u_char* CCP_data;
};
struct eth_ip_gre_ppp_PPP_IPCP_header_0_t{
	uint8_t PPP_IPCP_code;
	uint8_t PPP_IPCP_ID;
	uint16_t PPP_IPCP_length;
};
struct eth_ip_gre_ppp_PPP_IPCP_header_1_t{
	u_char* PPP_IPCP_data;
};
struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t{
	uint8_t IPV6CP_code;
	uint8_t IPV6CP_ID;
	uint16_t IPV6CP_length;
};
struct eth_ip_gre_ppp_PPP_IPV6CP_header_1_t{
	u_char* IPV6CP_data;
};
struct eth_ip_gre_ppp_PPP_LCP_header_t{
	uint8_t LCP_code;
	uint8_t LCP_ID;
	uint16_t LCP_length;
};
struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_0_t{
	uint8_t ACCM_type;
	uint8_t ACCM_length;
};
struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_1_t{
	u_char* ACCM_value;
};
struct eth_ip_gre_ppp_PPP_LCP_AP_option_0_t{
	uint8_t AP_type;
	uint8_t AP_length;
};
struct eth_ip_gre_ppp_PPP_LCP_AP_option_1_t{
	u_char* AP_value;
};
struct eth_ip_gre_ppp_PPP_LCP_MN_option_0_t{
	uint8_t MN_type;
	uint8_t MN_length;
};
struct eth_ip_gre_ppp_PPP_LCP_MN_option_1_t{
	u_char* MN_value;
};
struct eth_ip_gre_ppp_PPP_LCP_PFC_option_t{
	uint8_t PFC_type;
	uint8_t PFC_length;
};
struct eth_ip_gre_ppp_PPP_LCP_ACFC_option_t{
	uint8_t ACFC_type;
	uint8_t ACFC_length;
};
struct eth_ip_gre_ppp_PPP_LCP_MRU_option_0_t{
	uint8_t MRU_type;
	uint8_t MRU_length;
};
struct eth_ip_gre_ppp_PPP_LCP_MRU_option_1_t{
	u_char* MRU_value;
};
struct eth_ip_gre_ppp_PPP_short_header_t{
	uint8_t short_protocol;
};
struct eth_ip_gre_ppp_rubik_bitmap_t{
	unsigned eth_ip_gre_ppp_PPP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_CHAP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_CCP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_IPCP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_IPV6CP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_header: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_ACCM_option: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_AP_option: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_MN_option: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_PFC_option: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_ACFC_option: 1;
	unsigned eth_ip_gre_ppp_PPP_LCP_MRU_option: 1;
	unsigned eth_ip_gre_ppp_PPP_short_header: 1;
	unsigned blank: 3;
};
struct eth_ip_gre_ppp_select_t {
	uint32_t src_src_addr;
	uint32_t dst_dst_addr;
};
struct eth_ip_gre_ppp_transition_bitmap_t{
	unsigned config_a: 1;
	unsigned config_p: 1;
	unsigned p_sent_AFCF: 1;
	unsigned a_after_p_sent_AFCF: 1;
	unsigned a_AFCF_acked: 1;
	unsigned a_p_AFCF_acked: 1;
	unsigned tunneling_a: 1;
	unsigned tunneling_p: 1;
};
struct eth_ip_gre_ppp_instance_t {
	struct eth_ip_gre_ppp_select_t eth_ip_gre_ppp_select;
	struct buf_queue* bufs;
	struct time_record * rec_ptr;
	tommy_node node;
	automaton state;
	char time_record_leader;
	char* is_active_part;
	char stand;
	struct eth_ip_gre_ppp_instance_t * pair_instance;};
void eth_ip_gre_ppp_parse(u_char *payload, uint32_t length, struct timeval * now);
void eth_ip_gre_ppp_init(void);
extern struct eth_ip_gre_GRE_header_t* eth_ip_gre_GRE_header;
extern struct eth_ip_gre_GRE_sequence_number_t* eth_ip_gre_GRE_sequence_number;
extern struct eth_ip_gre_GRE_ack_number_t* eth_ip_gre_GRE_ack_number;
extern struct eth_ip_gre_rubik_bitmap_t* eth_ip_gre_rubik_bitmap;
extern struct eth_ip_gre_transition_bitmap_t* eth_ip_gre_transition_bitmap;
extern eth_ip_gre_data_t*eth_ip_gre_data;
#endif
