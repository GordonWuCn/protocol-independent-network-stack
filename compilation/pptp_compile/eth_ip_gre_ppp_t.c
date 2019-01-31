#include "eth_ip_gre_ppp_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct eth_ip_gre_ppp_instance_t *eth_ip_gre_ppp_instance;
struct eth_ip_gre_ppp_instance_t *eth_ip_gre_ppp_instance_reverse;
struct eth_ip_gre_ppp_select_t *eth_ip_gre_ppp_select;
struct eth_ip_gre_ppp_select_t *eth_ip_gre_ppp_select_reverse;
struct eth_ip_gre_ppp_instance_t *eth_ip_gre_ppp_fake_instance;
struct eth_ip_gre_ppp_instance_t *eth_ip_gre_ppp_fake_instance_reverse;
tommy_hashdyn eth_ip_gre_ppp_hashtable;
struct timer eth_ip_gre_ppp_list;
struct timeval eth_ip_gre_ppp_gap;
struct eth_ip_gre_ppp_PPP_header_t *eth_ip_gre_ppp_PPP_header;
struct eth_ip_gre_ppp_PPP_CHAP_header_0_t *eth_ip_gre_ppp_PPP_CHAP_header_0;
struct eth_ip_gre_ppp_PPP_CHAP_header_1_t *eth_ip_gre_ppp_PPP_CHAP_header_1;
struct eth_ip_gre_ppp_PPP_CCP_header_0_t *eth_ip_gre_ppp_PPP_CCP_header_0;
struct eth_ip_gre_ppp_PPP_CCP_header_1_t *eth_ip_gre_ppp_PPP_CCP_header_1;
struct eth_ip_gre_ppp_PPP_IPCP_header_0_t *eth_ip_gre_ppp_PPP_IPCP_header_0;
struct eth_ip_gre_ppp_PPP_IPCP_header_1_t *eth_ip_gre_ppp_PPP_IPCP_header_1;
struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t *eth_ip_gre_ppp_PPP_IPV6CP_header_0;
struct eth_ip_gre_ppp_PPP_IPV6CP_header_1_t *eth_ip_gre_ppp_PPP_IPV6CP_header_1;
struct eth_ip_gre_ppp_PPP_LCP_header_t *eth_ip_gre_ppp_PPP_LCP_header;
struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_0_t
	*eth_ip_gre_ppp_PPP_LCP_ACCM_option_0;
struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_1_t
	*eth_ip_gre_ppp_PPP_LCP_ACCM_option_1;
struct eth_ip_gre_ppp_PPP_LCP_AP_option_0_t *eth_ip_gre_ppp_PPP_LCP_AP_option_0;
struct eth_ip_gre_ppp_PPP_LCP_AP_option_1_t *eth_ip_gre_ppp_PPP_LCP_AP_option_1;
struct eth_ip_gre_ppp_PPP_LCP_MN_option_0_t *eth_ip_gre_ppp_PPP_LCP_MN_option_0;
struct eth_ip_gre_ppp_PPP_LCP_MN_option_1_t *eth_ip_gre_ppp_PPP_LCP_MN_option_1;
struct eth_ip_gre_ppp_PPP_LCP_PFC_option_t *eth_ip_gre_ppp_PPP_LCP_PFC_option;
struct eth_ip_gre_ppp_PPP_LCP_ACFC_option_t *eth_ip_gre_ppp_PPP_LCP_ACFC_option;
struct eth_ip_gre_ppp_PPP_LCP_MRU_option_0_t
	*eth_ip_gre_ppp_PPP_LCP_MRU_option_0;
struct eth_ip_gre_ppp_PPP_LCP_MRU_option_1_t
	*eth_ip_gre_ppp_PPP_LCP_MRU_option_1;
struct eth_ip_gre_ppp_PPP_short_header_t *eth_ip_gre_ppp_PPP_short_header;
char eth_ip_gre_ppp_has_buf = 0;
u_char *eth_ip_gre_ppp_buf;
int eth_ip_gre_ppp_buf_length;
u_char *eth_ip_gre_ppp_payload;
int eth_ip_gre_ppp_payload_length;
struct eth_ip_gre_ppp_rubik_bitmap_t *eth_ip_gre_ppp_rubik_bitmap;
struct eth_ip_gre_ppp_transition_bitmap_t *eth_ip_gre_ppp_transition_bitmap;
struct buf_queue *eth_ip_gre_ppp_bufs;
void eth_ip_gre_ppp_init ()
{
	tommy_hashdyn_init (&eth_ip_gre_ppp_hashtable);
	eth_ip_gre_ppp_gap.tv_sec = 10;
	eth_ip_gre_ppp_gap.tv_usec = 0;
	eth_ip_gre_ppp_list.head = NULL;
	eth_ip_gre_ppp_list.tail = NULL;
	eth_ip_gre_ppp_instance = NULL;
	eth_ip_gre_ppp_fake_instance =
		malloc (sizeof (struct eth_ip_gre_ppp_instance_t));
	eth_ip_gre_ppp_fake_instance->is_active_part = malloc (sizeof (char));
	*(eth_ip_gre_ppp_fake_instance->is_active_part) = 1;
	eth_ip_gre_ppp_fake_instance->stand = 0;
	eth_ip_gre_ppp_fake_instance_reverse =
		malloc (sizeof (struct eth_ip_gre_ppp_instance_t));
	eth_ip_gre_ppp_fake_instance_reverse->is_active_part =
		eth_ip_gre_ppp_fake_instance->is_active_part;
	eth_ip_gre_ppp_fake_instance_reverse->stand = 1;
	eth_ip_gre_ppp_select = malloc (sizeof (struct eth_ip_gre_ppp_select_t));
	eth_ip_gre_ppp_select_reverse =
		malloc (sizeof (struct eth_ip_gre_ppp_select_t));
	memset (eth_ip_gre_ppp_select, 0, sizeof (struct eth_ip_gre_ppp_select_t));
	memset (eth_ip_gre_ppp_select_reverse, 0,
		sizeof (struct eth_ip_gre_ppp_select_t));
	eth_ip_gre_ppp_rubik_bitmap =
		malloc (sizeof (struct eth_ip_gre_ppp_rubik_bitmap_t));
	eth_ip_gre_ppp_transition_bitmap =
		malloc (sizeof (struct eth_ip_gre_ppp_transition_bitmap_t));
	memset (eth_ip_gre_ppp_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_rubik_bitmap_t));
	memset (eth_ip_gre_ppp_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_transition_bitmap_t));
	eth_ip_gre_ppp_PPP_CHAP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CHAP_header_0_t));
	eth_ip_gre_ppp_PPP_CHAP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CHAP_header_1_t));
	eth_ip_gre_ppp_PPP_CCP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CCP_header_0_t));
	eth_ip_gre_ppp_PPP_CCP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CCP_header_1_t));
	eth_ip_gre_ppp_PPP_IPCP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPCP_header_0_t));
	eth_ip_gre_ppp_PPP_IPCP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPCP_header_1_t));
	eth_ip_gre_ppp_PPP_IPV6CP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t));
	eth_ip_gre_ppp_PPP_IPV6CP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPV6CP_header_1_t));
	eth_ip_gre_ppp_PPP_LCP_ACCM_option_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_1_t));
	eth_ip_gre_ppp_PPP_LCP_AP_option_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_LCP_AP_option_1_t));
	eth_ip_gre_ppp_PPP_LCP_MN_option_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_LCP_MN_option_1_t));
	eth_ip_gre_ppp_PPP_LCP_MRU_option_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_LCP_MRU_option_1_t));
	eth_ip_gre_ppp_PPP_CHAP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CHAP_header_0_t));
	eth_ip_gre_ppp_PPP_CHAP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CHAP_header_1_t));
	eth_ip_gre_ppp_PPP_CCP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CCP_header_0_t));
	eth_ip_gre_ppp_PPP_CCP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_CCP_header_1_t));
	eth_ip_gre_ppp_PPP_IPCP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPCP_header_0_t));
	eth_ip_gre_ppp_PPP_IPCP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPCP_header_1_t));
	eth_ip_gre_ppp_PPP_IPV6CP_header_0 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t));
	eth_ip_gre_ppp_PPP_IPV6CP_header_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_PPP_IPV6CP_header_1_t));
}

char eth_ip_gre_ppp_has_hole (uint64_t meta, int length, struct buf_queue *buf)
{
	if (buf->packet_count)
	{
		if (buf->is_tree)
		{
			uint64_t left_meta =
				((struct buffer_node *) (buf->root->head))->buf.meta;
			struct avl_node *ptr = buf->root->head;
			do
			{
				if (left_meta == ((struct buffer_node *) ptr)->buf.meta)
				{
					left_meta += ((struct buffer_node *) ptr)->buf.len;
				}
				else if (left_meta > ((struct buffer_node *) ptr)->buf.meta)
				{
					return 1;
				}
				else
				{
					if (left_meta == meta)
					{
						left_meta += length;
					}
					else
					{
						return 1;
					}
				}
			}
			while ((ptr = avl_node_next (ptr)));
		}
		else
		{
			uint64_t left_meta = buf->head->next->buf.meta;
			struct buf_list *cur = buf->head->next;
			while (cur != NULL)
			{
				if (left_meta == ((struct buffer_node *) cur)->buf.meta)
				{
					left_meta += ((struct buffer_node *) cur)->buf.len;
				}
				else if (left_meta > ((struct buffer_node *) cur)->buf.meta)
				{
					return 1;
				}
				else
				{
					if (left_meta == meta)
					{
						left_meta += length;
					}
					else
					{
						return 1;
					}
				}
				cur = cur->next;
			}
		}
		return 0;
	}
	return 0;
}

uint32_t eth_ip_gre_ppp_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_ppp_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_gre_ppp_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_ppp_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_gre_ppp_destroy (void)
{
	free_buf_list (eth_ip_gre_ppp_instance->bufs);
	free_buf_list (eth_ip_gre_ppp_instance_reverse->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_hashtable,
		&eth_ip_gre_ppp_instance->node);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_hashtable,
		&eth_ip_gre_ppp_instance_reverse->node);
	if (eth_ip_gre_ppp_instance->time_record_leader)
		deregister_timer (&eth_ip_gre_ppp_list,
			eth_ip_gre_ppp_instance->rec_ptr);
	else
		deregister_timer (&eth_ip_gre_ppp_list,
			eth_ip_gre_ppp_instance_reverse->rec_ptr);
	free (eth_ip_gre_ppp_instance->is_active_part);
	free (eth_ip_gre_ppp_instance);
	free (eth_ip_gre_ppp_instance_reverse);
}

void eth_ip_gre_ppp_free (void *inst)
{
	struct eth_ip_gre_ppp_instance_t *reverse =
		((struct eth_ip_gre_ppp_instance_t *) inst)->pair_instance;
	free_buf_list (reverse->bufs);
	free (reverse->is_active_part);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_hashtable, &reverse->node);
	free (reverse);
	free_buf_list (((struct eth_ip_gre_ppp_instance_t *) inst)->bufs);
}

static void eth_ip_gre_ppp_SESSION (void);
static void eth_ip_gre_ppp_passive_sent_ACFC_active_no (void);
static void eth_ip_gre_ppp_active_pasive_sent_ACFC (void);
static void eth_ip_gre_ppp_active_ACFC_acked_passive_no (void);
void eth_ip_gre_ppp_SESSION ()
{
	if (*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
		stand)
	{
		if ((1 && (PPP_temp_data->protocol != 33)
				&& !eth_ip_gre_ppp_rubik_bitmap->
				eth_ip_gre_ppp_PPP_LCP_ACFC_option))
		{
			eth_ip_gre_ppp_transition_bitmap->config_a = 1;
			eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			return;
		}
		if ((1 &&
				eth_ip_gre_ppp_rubik_bitmap->
				eth_ip_gre_ppp_PPP_LCP_ACFC_option))
		{
			eth_ip_gre_ppp_transition_bitmap->p_sent_AFCF = 1;
			eth_ip_gre_ppp_instance->state =
				eth_ip_gre_ppp_passive_sent_ACFC_active_no;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			return;
		}
		if ((1 && (PPP_temp_data->protocol == 33)))
		{
			eth_ip_gre_ppp_transition_bitmap->tunneling_a = 1;
			eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			eth_ip_gre_ppp_buf = eth_ip_gre_ppp_payload;
			eth_ip_gre_ppp_buf_length = eth_ip_gre_ppp_payload_length;
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
			stand))
	{
		if ((1 && (PPP_temp_data->protocol != 33)
				&& !eth_ip_gre_ppp_rubik_bitmap->
				eth_ip_gre_ppp_PPP_LCP_ACFC_option))
		{
			eth_ip_gre_ppp_transition_bitmap->config_p = 1;
			eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			return;
		}
		if ((1 && (PPP_temp_data->protocol == 33)))
		{
			eth_ip_gre_ppp_transition_bitmap->tunneling_p = 1;
			eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			eth_ip_gre_ppp_buf = eth_ip_gre_ppp_payload;
			eth_ip_gre_ppp_buf_length = eth_ip_gre_ppp_payload_length;
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_passive_sent_ACFC_active_no ()
{
	if (*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
		stand)
	{
		return;
	}
	if (!(*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
			stand))
	{
		if ((1 &&
				eth_ip_gre_ppp_rubik_bitmap->
				eth_ip_gre_ppp_PPP_LCP_ACFC_option))
		{
			eth_ip_gre_ppp_transition_bitmap->a_after_p_sent_AFCF = 1;
			eth_ip_gre_ppp_instance->state =
				eth_ip_gre_ppp_active_pasive_sent_ACFC;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_active_pasive_sent_ACFC ()
{
	if (*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
		stand)
	{
		if (1)
		{
			eth_ip_gre_ppp_transition_bitmap->a_AFCF_acked = 1;
			eth_ip_gre_ppp_instance->state =
				eth_ip_gre_ppp_active_ACFC_acked_passive_no;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
			stand))
	{
		return;
	}
}

void eth_ip_gre_ppp_active_ACFC_acked_passive_no ()
{
	if (*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
		stand)
	{
		return;
	}
	if (!(*(eth_ip_gre_ppp_instance->is_active_part) ^ eth_ip_gre_ppp_instance->
			stand))
	{
		if (1)
		{
			eth_ip_gre_ppp_transition_bitmap->a_p_AFCF_acked = 1;
			eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
			eth_ip_gre_ppp_instance_reverse->state =
				eth_ip_gre_ppp_instance->state;
			eth_ip_gre_data->short_PPP = 1;
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	if (!eth_ip_gre_data->short_PPP)
	{
		eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_header = 1;
		eth_ip_gre_ppp_PPP_header =
			(struct eth_ip_gre_ppp_PPP_header_t *) (payload + cur_pos);
		cur_pos += 4;
		eth_ip_gre_ppp_PPP_header->protocol =
			ntohs (eth_ip_gre_ppp_PPP_header->protocol);
		if ((eth_ip_gre_ppp_PPP_header->protocol == 49699))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_CHAP_header = 1;
			eth_ip_gre_ppp_PPP_CHAP_header_0 =
				(struct eth_ip_gre_ppp_PPP_CHAP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length =
				ntohs (eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length);
			eth_ip_gre_ppp_PPP_CHAP_header_1->CHAP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_header->protocol == 33021))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_CCP_header = 1;
			eth_ip_gre_ppp_PPP_CCP_header_0 =
				(struct eth_ip_gre_ppp_PPP_CCP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length =
				ntohs (eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length);
			eth_ip_gre_ppp_PPP_CCP_header_1->CCP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_header->protocol == 32801))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_IPCP_header = 1;
			eth_ip_gre_ppp_PPP_IPCP_header_0 =
				(struct eth_ip_gre_ppp_PPP_IPCP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length =
				ntohs (eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length);
			eth_ip_gre_ppp_PPP_IPCP_header_1->PPP_IPCP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_header->protocol == 32855))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_IPV6CP_header = 1;
			eth_ip_gre_ppp_PPP_IPV6CP_header_0 =
				(struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length =
				ntohs (eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length);
			eth_ip_gre_ppp_PPP_IPV6CP_header_1->IPV6CP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_header->protocol == 49185))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_LCP_header = 1;
			eth_ip_gre_ppp_PPP_LCP_header =
				(struct eth_ip_gre_ppp_PPP_LCP_header_t *) (payload + cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_LCP_header->LCP_length =
				ntohs (eth_ip_gre_ppp_PPP_LCP_header->LCP_length);
			while ((cur_pos < (eth_ip_gre_ppp_PPP_LCP_header->LCP_length + 4)))
			{
				any_parse = 1;
				any_parse = 0;
				if (((struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_0_t *) (payload
							+ cur_pos))->ACCM_type == 2)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_ACCM_option = 1;
					eth_ip_gre_ppp_PPP_LCP_ACCM_option_0 =
						(struct eth_ip_gre_ppp_PPP_LCP_ACCM_option_0_t
						*) (payload + cur_pos);
					cur_pos += 2;
					eth_ip_gre_ppp_PPP_LCP_ACCM_option_1->ACCM_value =
						payload + cur_pos;
					cur_pos +=
						(eth_ip_gre_ppp_PPP_LCP_ACCM_option_0->ACCM_length - 2);
				}
				else if (((struct eth_ip_gre_ppp_PPP_LCP_AP_option_0_t
							*) (payload + cur_pos))->AP_type == 3)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_AP_option = 1;
					eth_ip_gre_ppp_PPP_LCP_AP_option_0 =
						(struct eth_ip_gre_ppp_PPP_LCP_AP_option_0_t *) (payload
						+ cur_pos);
					cur_pos += 2;
					eth_ip_gre_ppp_PPP_LCP_AP_option_1->AP_value =
						payload + cur_pos;
					cur_pos +=
						(eth_ip_gre_ppp_PPP_LCP_AP_option_0->AP_length - 2);
				}
				else if (((struct eth_ip_gre_ppp_PPP_LCP_MN_option_0_t
							*) (payload + cur_pos))->MN_type == 5)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_MN_option = 1;
					eth_ip_gre_ppp_PPP_LCP_MN_option_0 =
						(struct eth_ip_gre_ppp_PPP_LCP_MN_option_0_t *) (payload
						+ cur_pos);
					cur_pos += 2;
					eth_ip_gre_ppp_PPP_LCP_MN_option_1->MN_value =
						payload + cur_pos;
					cur_pos +=
						(eth_ip_gre_ppp_PPP_LCP_MN_option_0->MN_length - 2);
				}
				else if (((struct eth_ip_gre_ppp_PPP_LCP_PFC_option_t
							*) (payload + cur_pos))->PFC_type == 7)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_PFC_option = 1;
					eth_ip_gre_ppp_PPP_LCP_PFC_option =
						(struct eth_ip_gre_ppp_PPP_LCP_PFC_option_t *) (payload
						+ cur_pos);
					cur_pos += 2;
				}
				else if (((struct eth_ip_gre_ppp_PPP_LCP_ACFC_option_t
							*) (payload + cur_pos))->ACFC_type == 8)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_ACFC_option = 1;
					eth_ip_gre_ppp_PPP_LCP_ACFC_option =
						(struct eth_ip_gre_ppp_PPP_LCP_ACFC_option_t *) (payload
						+ cur_pos);
					cur_pos += 2;
				}
				else if (((struct eth_ip_gre_ppp_PPP_LCP_MRU_option_0_t
							*) (payload + cur_pos))->MRU_type == 1)
				{
					any_parse = 1;
					eth_ip_gre_ppp_rubik_bitmap->
						eth_ip_gre_ppp_PPP_LCP_MRU_option = 1;
					eth_ip_gre_ppp_PPP_LCP_MRU_option_0 =
						(struct eth_ip_gre_ppp_PPP_LCP_MRU_option_0_t
						*) (payload + cur_pos);
					cur_pos += 2;
					eth_ip_gre_ppp_PPP_LCP_MRU_option_1->MRU_value =
						payload + cur_pos;
					cur_pos +=
						(eth_ip_gre_ppp_PPP_LCP_MRU_option_0->MRU_length - 2);
				}
				if (!any_parse)
				{
					break;
				}
			}
		}
	}
	if (eth_ip_gre_data->short_PPP)
	{
		eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_short_header = 1;
		eth_ip_gre_ppp_PPP_short_header =
			(struct eth_ip_gre_ppp_PPP_short_header_t *) (payload + cur_pos);
		cur_pos += 1;
		if ((eth_ip_gre_ppp_PPP_short_header->short_protocol == 49699))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_CHAP_header = 1;
			eth_ip_gre_ppp_PPP_CHAP_header_0 =
				(struct eth_ip_gre_ppp_PPP_CHAP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length =
				ntohs (eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length);
			eth_ip_gre_ppp_PPP_CHAP_header_1->CHAP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_CHAP_header_0->CHAP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_short_header->short_protocol == 33021))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_CCP_header = 1;
			eth_ip_gre_ppp_PPP_CCP_header_0 =
				(struct eth_ip_gre_ppp_PPP_CCP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length =
				ntohs (eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length);
			eth_ip_gre_ppp_PPP_CCP_header_1->CCP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_CCP_header_0->CCP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_short_header->short_protocol == 32801))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_IPCP_header = 1;
			eth_ip_gre_ppp_PPP_IPCP_header_0 =
				(struct eth_ip_gre_ppp_PPP_IPCP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length =
				ntohs (eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length);
			eth_ip_gre_ppp_PPP_IPCP_header_1->PPP_IPCP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_IPCP_header_0->PPP_IPCP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_short_header->short_protocol == 32855))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_IPV6CP_header = 1;
			eth_ip_gre_ppp_PPP_IPV6CP_header_0 =
				(struct eth_ip_gre_ppp_PPP_IPV6CP_header_0_t *) (payload +
				cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length =
				ntohs (eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length);
			eth_ip_gre_ppp_PPP_IPV6CP_header_1->IPV6CP_data = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_PPP_IPV6CP_header_0->IPV6CP_length - 4);
		}
		if ((eth_ip_gre_ppp_PPP_short_header->short_protocol == 49185))
		{
			eth_ip_gre_ppp_rubik_bitmap->eth_ip_gre_ppp_PPP_LCP_header = 1;
			eth_ip_gre_ppp_PPP_LCP_header =
				(struct eth_ip_gre_ppp_PPP_LCP_header_t *) (payload + cur_pos);
			cur_pos += 4;
			eth_ip_gre_ppp_PPP_LCP_header->LCP_length =
				ntohs (eth_ip_gre_ppp_PPP_LCP_header->LCP_length);
		}
	}
	eth_ip_gre_ppp_payload_length -= cur_pos;
	eth_ip_gre_ppp_payload += cur_pos;
	eth_ip_gre_ppp_select->src_src_addr = eth_ip_ip_hdr->src_addr;
	eth_ip_gre_ppp_select->dst_dst_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_gre_ppp_select_reverse->src_src_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_gre_ppp_select_reverse->dst_dst_addr = eth_ip_ip_hdr->src_addr;
}

void eth_ip_gre_ppp_selector (struct timeval *now)
{
	uint32_t hash = eth_ip_gre_ppp_hash (eth_ip_gre_ppp_select);
	eth_ip_gre_ppp_instance =
		tommy_hashdyn_search (&eth_ip_gre_ppp_hashtable, eth_ip_gre_ppp_compare,
		eth_ip_gre_ppp_select, hash);
	if (!eth_ip_gre_ppp_instance)
	{
		eth_ip_gre_ppp_instance =
			(struct eth_ip_gre_ppp_instance_t *) malloc (sizeof (struct
				eth_ip_gre_ppp_instance_t));
		memset (eth_ip_gre_ppp_instance, 0,
			sizeof (struct eth_ip_gre_ppp_select_t));
		eth_ip_gre_ppp_instance_reverse =
			(struct eth_ip_gre_ppp_instance_t *) malloc (sizeof (struct
				eth_ip_gre_ppp_instance_t));
		memset (eth_ip_gre_ppp_instance_reverse, 0,
			sizeof (struct eth_ip_gre_ppp_select_t));
		eth_ip_gre_ppp_instance->eth_ip_gre_ppp_select = *eth_ip_gre_ppp_select;
		eth_ip_gre_ppp_instance->time_record_leader = 1;
		eth_ip_gre_ppp_instance->is_active_part = malloc (sizeof (char));
		eth_ip_gre_ppp_instance->stand = 0;
		*(eth_ip_gre_ppp_instance->is_active_part) = 1;
		eth_ip_gre_ppp_instance->state = eth_ip_gre_ppp_SESSION;
		eth_ip_gre_ppp_instance->rec_ptr =
			timer_update (&eth_ip_gre_ppp_list, eth_ip_gre_ppp_instance, NULL,
			now);
		eth_ip_gre_ppp_instance->pair_instance =
			eth_ip_gre_ppp_instance_reverse;
		init_buf_list (&eth_ip_gre_ppp_instance->bufs);
		hash = eth_ip_gre_ppp_hash (eth_ip_gre_ppp_select);
		tommy_hashdyn_insert (&eth_ip_gre_ppp_hashtable,
			&eth_ip_gre_ppp_instance->node, eth_ip_gre_ppp_instance, hash);
		eth_ip_gre_ppp_instance_reverse->eth_ip_gre_ppp_select =
			*eth_ip_gre_ppp_select_reverse;
		eth_ip_gre_ppp_instance_reverse->time_record_leader = 0;
		eth_ip_gre_ppp_instance_reverse->is_active_part =
			eth_ip_gre_ppp_instance->is_active_part;
		eth_ip_gre_ppp_instance_reverse->stand = 1;
		eth_ip_gre_ppp_instance_reverse->state = eth_ip_gre_ppp_SESSION;
		eth_ip_gre_ppp_instance_reverse->pair_instance =
			eth_ip_gre_ppp_instance;
		init_buf_list (&eth_ip_gre_ppp_instance_reverse->bufs);
		hash = eth_ip_gre_ppp_hash (eth_ip_gre_ppp_select_reverse);
		tommy_hashdyn_insert (&eth_ip_gre_ppp_hashtable,
			&eth_ip_gre_ppp_instance_reverse->node,
			eth_ip_gre_ppp_instance_reverse, hash);
	}
	else
	{
		eth_ip_gre_ppp_instance_reverse =
			eth_ip_gre_ppp_instance->pair_instance;
		if (eth_ip_gre_ppp_instance->time_record_leader)
			eth_ip_gre_ppp_instance->rec_ptr =
				timer_update (&eth_ip_gre_ppp_list, eth_ip_gre_ppp_instance,
				eth_ip_gre_ppp_instance->rec_ptr, now);
		else
			eth_ip_gre_ppp_instance_reverse->rec_ptr =
				timer_update (&eth_ip_gre_ppp_list,
				eth_ip_gre_ppp_instance_reverse,
				eth_ip_gre_ppp_instance_reverse->rec_ptr, now);
	}
	if (eth_ip_gre_data->short_PPP)
	{
		PPP_temp_data->protocol =
			eth_ip_gre_ppp_PPP_short_header->short_protocol;
	}
	if (!eth_ip_gre_data->short_PPP)
	{
		PPP_temp_data->protocol = eth_ip_gre_ppp_PPP_header->protocol;
	}
}

void eth_ip_gre_ppp_ip_parse (u_char *, uint32_t, struct timeval *);
void eth_ip_gre_ppp_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is ppp layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_gre_ppp_payload = payload;
	eth_ip_gre_ppp_payload_length = length;
	eth_ip_gre_ppp_data_assignment (payload);
	eth_ip_gre_ppp_selector (now);
	eth_ip_gre_ppp_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_gre_ppp_list,
			&eth_ip_gre_ppp_gap, &eth_ip_gre_ppp_hashtable,
			offsetof (struct eth_ip_gre_ppp_instance_t, node),
			eth_ip_gre_ppp_free, now);
		ts = int_now;
	}
	if ((PPP_temp_data->protocol == 33))
	{
		eth_ip_gre_ppp_ip_parse (eth_ip_gre_ppp_buf, eth_ip_gre_ppp_buf_length,
			now);
	}
	memset (eth_ip_gre_ppp_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_rubik_bitmap_t));
	memset (eth_ip_gre_ppp_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_transition_bitmap_t));
	if (eth_ip_gre_ppp_has_buf)
	{
		free (eth_ip_gre_ppp_buf);
		eth_ip_gre_ppp_has_buf = 0;
	}
}
