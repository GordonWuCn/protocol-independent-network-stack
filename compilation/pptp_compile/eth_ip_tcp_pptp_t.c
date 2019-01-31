#include "eth_ip_tcp_pptp_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct eth_ip_tcp_pptp_instance_t *eth_ip_tcp_pptp_instance;
struct eth_ip_tcp_pptp_instance_t *eth_ip_tcp_pptp_instance_reverse;
struct eth_ip_tcp_pptp_select_t *eth_ip_tcp_pptp_select;
struct eth_ip_tcp_pptp_select_t *eth_ip_tcp_pptp_select_reverse;
struct eth_ip_tcp_pptp_instance_t *eth_ip_tcp_pptp_fake_instance;
struct eth_ip_tcp_pptp_instance_t *eth_ip_tcp_pptp_fake_instance_reverse;
tommy_hashdyn eth_ip_tcp_pptp_hashtable;
struct timer eth_ip_tcp_pptp_list;
struct timeval eth_ip_tcp_pptp_gap;
struct eth_ip_tcp_pptp_pptp_general_t *eth_ip_tcp_pptp_pptp_general;
struct eth_ip_tcp_pptp_start_control_connection_request_0_t
	*eth_ip_tcp_pptp_start_control_connection_request_0;
struct eth_ip_tcp_pptp_start_control_connection_request_1_t
	*eth_ip_tcp_pptp_start_control_connection_request_1;
struct eth_ip_tcp_pptp_start_control_connection_request_2_t
	*eth_ip_tcp_pptp_start_control_connection_request_2;
struct eth_ip_tcp_pptp_start_control_connection_reply_0_t
	*eth_ip_tcp_pptp_start_control_connection_reply_0;
struct eth_ip_tcp_pptp_start_control_connection_reply_1_t
	*eth_ip_tcp_pptp_start_control_connection_reply_1;
struct eth_ip_tcp_pptp_start_control_connection_reply_2_t
	*eth_ip_tcp_pptp_start_control_connection_reply_2;
struct eth_ip_tcp_pptp_outgoing_call_request_0_t
	*eth_ip_tcp_pptp_outgoing_call_request_0;
struct eth_ip_tcp_pptp_outgoing_call_request_1_t
	*eth_ip_tcp_pptp_outgoing_call_request_1;
struct eth_ip_tcp_pptp_outgoing_call_request_2_t
	*eth_ip_tcp_pptp_outgoing_call_request_2;
struct eth_ip_tcp_pptp_outgoing_call_reply_t
	*eth_ip_tcp_pptp_outgoing_call_reply;
struct eth_ip_tcp_pptp_set_link_info_t *eth_ip_tcp_pptp_set_link_info;
struct eth_ip_tcp_pptp_echo_request_t *eth_ip_tcp_pptp_echo_request;
struct eth_ip_tcp_pptp_echo_reply_t *eth_ip_tcp_pptp_echo_reply;
char eth_ip_tcp_pptp_has_buf = 0;
u_char *eth_ip_tcp_pptp_buf;
int eth_ip_tcp_pptp_buf_length;
u_char *eth_ip_tcp_pptp_payload;
int eth_ip_tcp_pptp_payload_length;
struct eth_ip_tcp_pptp_rubik_bitmap_t *eth_ip_tcp_pptp_rubik_bitmap;
struct eth_ip_tcp_pptp_transition_bitmap_t *eth_ip_tcp_pptp_transition_bitmap;
struct buf_queue *eth_ip_tcp_pptp_bufs;
void eth_ip_tcp_pptp_init ()
{
	tommy_hashdyn_init (&eth_ip_tcp_pptp_hashtable);
	eth_ip_tcp_pptp_gap.tv_sec = 120;
	eth_ip_tcp_pptp_gap.tv_usec = 0;
	eth_ip_tcp_pptp_list.head = NULL;
	eth_ip_tcp_pptp_list.tail = NULL;
	eth_ip_tcp_pptp_instance = NULL;
	eth_ip_tcp_pptp_fake_instance =
		malloc (sizeof (struct eth_ip_tcp_pptp_instance_t));
	eth_ip_tcp_pptp_fake_instance->is_active_part = malloc (sizeof (char));
	*(eth_ip_tcp_pptp_fake_instance->is_active_part) = 1;
	eth_ip_tcp_pptp_fake_instance->stand = 0;
	eth_ip_tcp_pptp_fake_instance_reverse =
		malloc (sizeof (struct eth_ip_tcp_pptp_instance_t));
	eth_ip_tcp_pptp_fake_instance_reverse->is_active_part =
		eth_ip_tcp_pptp_fake_instance->is_active_part;
	eth_ip_tcp_pptp_fake_instance_reverse->stand = 1;
	eth_ip_tcp_pptp_select = malloc (sizeof (struct eth_ip_tcp_pptp_select_t));
	eth_ip_tcp_pptp_select_reverse =
		malloc (sizeof (struct eth_ip_tcp_pptp_select_t));
	memset (eth_ip_tcp_pptp_select, 0,
		sizeof (struct eth_ip_tcp_pptp_select_t));
	memset (eth_ip_tcp_pptp_select_reverse, 0,
		sizeof (struct eth_ip_tcp_pptp_select_t));
	eth_ip_tcp_pptp_rubik_bitmap =
		malloc (sizeof (struct eth_ip_tcp_pptp_rubik_bitmap_t));
	eth_ip_tcp_pptp_transition_bitmap =
		malloc (sizeof (struct eth_ip_tcp_pptp_transition_bitmap_t));
	memset (eth_ip_tcp_pptp_rubik_bitmap, 0,
		sizeof (struct eth_ip_tcp_pptp_rubik_bitmap_t));
	memset (eth_ip_tcp_pptp_transition_bitmap, 0,
		sizeof (struct eth_ip_tcp_pptp_transition_bitmap_t));
	eth_ip_tcp_pptp_start_control_connection_request_1 =
		malloc (sizeof (struct
			eth_ip_tcp_pptp_start_control_connection_request_1_t));
	eth_ip_tcp_pptp_start_control_connection_request_2 =
		malloc (sizeof (struct
			eth_ip_tcp_pptp_start_control_connection_request_2_t));
	eth_ip_tcp_pptp_start_control_connection_reply_1 =
		malloc (sizeof (struct
			eth_ip_tcp_pptp_start_control_connection_reply_1_t));
	eth_ip_tcp_pptp_start_control_connection_reply_2 =
		malloc (sizeof (struct
			eth_ip_tcp_pptp_start_control_connection_reply_2_t));
	eth_ip_tcp_pptp_outgoing_call_request_1 =
		malloc (sizeof (struct eth_ip_tcp_pptp_outgoing_call_request_1_t));
	eth_ip_tcp_pptp_outgoing_call_request_2 =
		malloc (sizeof (struct eth_ip_tcp_pptp_outgoing_call_request_2_t));
}

char eth_ip_tcp_pptp_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t eth_ip_tcp_pptp_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_tcp_pptp_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_tcp_pptp_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_tcp_pptp_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_tcp_pptp_destroy (void)
{
	free_buf_list (eth_ip_tcp_pptp_instance->bufs);
	free_buf_list (eth_ip_tcp_pptp_instance_reverse->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_tcp_pptp_hashtable,
		&eth_ip_tcp_pptp_instance->node);
	tommy_hashdyn_remove_existing (&eth_ip_tcp_pptp_hashtable,
		&eth_ip_tcp_pptp_instance_reverse->node);
	if (eth_ip_tcp_pptp_instance->time_record_leader)
		deregister_timer (&eth_ip_tcp_pptp_list,
			eth_ip_tcp_pptp_instance->rec_ptr);
	else
		deregister_timer (&eth_ip_tcp_pptp_list,
			eth_ip_tcp_pptp_instance_reverse->rec_ptr);
	free (eth_ip_tcp_pptp_instance->is_active_part);
	free (eth_ip_tcp_pptp_instance);
	free (eth_ip_tcp_pptp_instance_reverse);
}

void eth_ip_tcp_pptp_free (void *inst)
{
	struct eth_ip_tcp_pptp_instance_t *reverse =
		((struct eth_ip_tcp_pptp_instance_t *) inst)->pair_instance;
	free_buf_list (reverse->bufs);
	free (reverse->is_active_part);
	tommy_hashdyn_remove_existing (&eth_ip_tcp_pptp_hashtable, &reverse->node);
	free (reverse);
	free_buf_list (((struct eth_ip_tcp_pptp_instance_t *) inst)->bufs);
}

static void eth_ip_tcp_pptp_CLOSED (void);
static void eth_ip_tcp_pptp_REQUEST_CONNECT (void);
static void eth_ip_tcp_pptp_CONNECTION_ESTABLISHED (void);
static void eth_ip_tcp_pptp_REQUEST_SESSION (void);
static void eth_ip_tcp_pptp_SESSION_ESTABLISHED (void);
static void eth_ip_tcp_pptp_ECHO_SENT (void);
void eth_ip_tcp_pptp_CLOSED ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		if ((1 &&
				eth_ip_tcp_pptp_rubik_bitmap->
				eth_ip_tcp_pptp_start_control_connection_request))
		{
			eth_ip_tcp_pptp_transition_bitmap->SCCRQ_sent = 1;
			eth_ip_tcp_pptp_instance->state = eth_ip_tcp_pptp_REQUEST_CONNECT;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		return;
	}
}

void eth_ip_tcp_pptp_REQUEST_CONNECT ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		if ((1 &&
				eth_ip_tcp_pptp_rubik_bitmap->
				eth_ip_tcp_pptp_start_control_connection_reply))
		{
			eth_ip_tcp_pptp_transition_bitmap->SCCRP_sent = 1;
			eth_ip_tcp_pptp_instance->state =
				eth_ip_tcp_pptp_CONNECTION_ESTABLISHED;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_tcp_pptp_CONNECTION_ESTABLISHED ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		if ((1 &&
				eth_ip_tcp_pptp_rubik_bitmap->
				eth_ip_tcp_pptp_outgoing_call_request))
		{
			eth_ip_tcp_pptp_transition_bitmap->OCRQ_sent = 1;
			eth_ip_tcp_pptp_instance->state = eth_ip_tcp_pptp_REQUEST_SESSION;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		return;
	}
}

void eth_ip_tcp_pptp_REQUEST_SESSION ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		if ((1 &&
				eth_ip_tcp_pptp_rubik_bitmap->
				eth_ip_tcp_pptp_outgoing_call_reply))
		{
			eth_ip_tcp_pptp_transition_bitmap->OCRP_sent = 1;
			eth_ip_tcp_pptp_instance->state =
				eth_ip_tcp_pptp_SESSION_ESTABLISHED;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_tcp_pptp_SESSION_ESTABLISHED ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		if ((1 && eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_echo_request))
		{
			eth_ip_tcp_pptp_transition_bitmap->keep_alive = 1;
			eth_ip_tcp_pptp_instance->state = eth_ip_tcp_pptp_ECHO_SENT;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		if ((1 && eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_set_link_info))
		{
			eth_ip_tcp_pptp_transition_bitmap->session_config_passive = 1;
			eth_ip_tcp_pptp_instance->state =
				eth_ip_tcp_pptp_SESSION_ESTABLISHED;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		if ((1 && eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_set_link_info))
		{
			eth_ip_tcp_pptp_transition_bitmap->session_config_active = 1;
			eth_ip_tcp_pptp_instance->state =
				eth_ip_tcp_pptp_SESSION_ESTABLISHED;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_tcp_pptp_ECHO_SENT ()
{
	if (*(eth_ip_tcp_pptp_instance->is_active_part) ^ eth_ip_tcp_pptp_instance->
		stand)
	{
		return;
	}
	if (!(*(eth_ip_tcp_pptp_instance->
				is_active_part) ^ eth_ip_tcp_pptp_instance->stand))
	{
		if ((1 && eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_echo_reply))
		{
			eth_ip_tcp_pptp_transition_bitmap->maintain_connection = 1;
			eth_ip_tcp_pptp_instance->state =
				eth_ip_tcp_pptp_SESSION_ESTABLISHED;
			eth_ip_tcp_pptp_instance_reverse->state =
				eth_ip_tcp_pptp_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_tcp_pptp_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_pptp_general = 1;
	eth_ip_tcp_pptp_pptp_general =
		(struct eth_ip_tcp_pptp_pptp_general_t *) (payload + cur_pos);
	cur_pos += 8;
	eth_ip_tcp_pptp_pptp_general->length =
		ntohs (eth_ip_tcp_pptp_pptp_general->length);
	eth_ip_tcp_pptp_pptp_general->pptp_message_type =
		ntohs (eth_ip_tcp_pptp_pptp_general->pptp_message_type);
	any_parse = 0;
	if (((struct eth_ip_tcp_pptp_start_control_connection_request_0_t
				*) (payload + cur_pos))->SCCRQ_type == 256)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->
			eth_ip_tcp_pptp_start_control_connection_request = 1;
		eth_ip_tcp_pptp_start_control_connection_request_0 =
			(struct eth_ip_tcp_pptp_start_control_connection_request_0_t
			*) (payload + cur_pos);
		cur_pos += 20;
		eth_ip_tcp_pptp_start_control_connection_request_1->SCCRQ_host_name =
			payload + cur_pos;
		cur_pos += 64;
		eth_ip_tcp_pptp_start_control_connection_request_2->SCCRQ_vandor_name =
			payload + cur_pos;
		cur_pos += 64;
	}
	else if (((struct eth_ip_tcp_pptp_start_control_connection_reply_0_t
				*) (payload + cur_pos))->SCCRP_type == 512)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->
			eth_ip_tcp_pptp_start_control_connection_reply = 1;
		eth_ip_tcp_pptp_start_control_connection_reply_0 =
			(struct eth_ip_tcp_pptp_start_control_connection_reply_0_t
			*) (payload + cur_pos);
		cur_pos += 20;
		eth_ip_tcp_pptp_start_control_connection_reply_1->SCCRP_host_name =
			payload + cur_pos;
		cur_pos += 64;
		eth_ip_tcp_pptp_start_control_connection_reply_2->SCCRP_vandor_name =
			payload + cur_pos;
		cur_pos += 64;
	}
	else if (((struct eth_ip_tcp_pptp_outgoing_call_request_0_t *) (payload +
				cur_pos))->OCRQ_type == 1792)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_outgoing_call_request = 1;
		eth_ip_tcp_pptp_outgoing_call_request_0 =
			(struct eth_ip_tcp_pptp_outgoing_call_request_0_t *) (payload +
			cur_pos);
		cur_pos += 32;
		eth_ip_tcp_pptp_outgoing_call_request_1->OCRQ_phone_number =
			payload + cur_pos;
		cur_pos += 64;
		eth_ip_tcp_pptp_outgoing_call_request_2->OCRQ_subaddress =
			payload + cur_pos;
		cur_pos += 64;
	}
	else if (((struct eth_ip_tcp_pptp_outgoing_call_reply_t *) (payload +
				cur_pos))->OCRP_type == 2048)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_outgoing_call_reply = 1;
		eth_ip_tcp_pptp_outgoing_call_reply =
			(struct eth_ip_tcp_pptp_outgoing_call_reply_t *) (payload +
			cur_pos);
		cur_pos += 24;
	}
	else if (((struct eth_ip_tcp_pptp_set_link_info_t *) (payload +
				cur_pos))->SLI_type == 3840)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_set_link_info = 1;
		eth_ip_tcp_pptp_set_link_info =
			(struct eth_ip_tcp_pptp_set_link_info_t *) (payload + cur_pos);
		cur_pos += 16;
	}
	else if (((struct eth_ip_tcp_pptp_echo_request_t *) (payload +
				cur_pos))->ERQ_type == 1280)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_echo_request = 1;
		eth_ip_tcp_pptp_echo_request =
			(struct eth_ip_tcp_pptp_echo_request_t *) (payload + cur_pos);
		cur_pos += 8;
	}
	else if (((struct eth_ip_tcp_pptp_echo_reply_t *) (payload +
				cur_pos))->ERP_type == 1536)
	{
		any_parse = 1;
		eth_ip_tcp_pptp_rubik_bitmap->eth_ip_tcp_pptp_echo_reply = 1;
		eth_ip_tcp_pptp_echo_reply =
			(struct eth_ip_tcp_pptp_echo_reply_t *) (payload + cur_pos);
		cur_pos += 12;
	}
	eth_ip_tcp_pptp_payload_length -= cur_pos;
	eth_ip_tcp_pptp_payload += cur_pos;
	eth_ip_tcp_pptp_select->src_src_addr = eth_ip_ip_hdr->src_addr;
	eth_ip_tcp_pptp_select->dst_dst_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_tcp_pptp_select_reverse->src_src_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_tcp_pptp_select_reverse->dst_dst_addr = eth_ip_ip_hdr->src_addr;
}

void eth_ip_tcp_pptp_selector (struct timeval *now)
{
	uint32_t hash = eth_ip_tcp_pptp_hash (eth_ip_tcp_pptp_select);
	eth_ip_tcp_pptp_instance =
		tommy_hashdyn_search (&eth_ip_tcp_pptp_hashtable,
		eth_ip_tcp_pptp_compare, eth_ip_tcp_pptp_select, hash);
	if (!eth_ip_tcp_pptp_instance)
	{
		eth_ip_tcp_pptp_instance =
			(struct eth_ip_tcp_pptp_instance_t *) malloc (sizeof (struct
				eth_ip_tcp_pptp_instance_t));
		memset (eth_ip_tcp_pptp_instance, 0,
			sizeof (struct eth_ip_tcp_pptp_select_t));
		eth_ip_tcp_pptp_instance_reverse =
			(struct eth_ip_tcp_pptp_instance_t *) malloc (sizeof (struct
				eth_ip_tcp_pptp_instance_t));
		memset (eth_ip_tcp_pptp_instance_reverse, 0,
			sizeof (struct eth_ip_tcp_pptp_select_t));
		eth_ip_tcp_pptp_instance->eth_ip_tcp_pptp_select =
			*eth_ip_tcp_pptp_select;
		eth_ip_tcp_pptp_instance->time_record_leader = 1;
		eth_ip_tcp_pptp_instance->is_active_part = malloc (sizeof (char));
		eth_ip_tcp_pptp_instance->stand = 0;
		*(eth_ip_tcp_pptp_instance->is_active_part) = 1;
		eth_ip_tcp_pptp_instance->state = eth_ip_tcp_pptp_CLOSED;
		eth_ip_tcp_pptp_instance->rec_ptr =
			timer_update (&eth_ip_tcp_pptp_list, eth_ip_tcp_pptp_instance, NULL,
			now);
		eth_ip_tcp_pptp_instance->pair_instance =
			eth_ip_tcp_pptp_instance_reverse;
		init_buf_list (&eth_ip_tcp_pptp_instance->bufs);
		hash = eth_ip_tcp_pptp_hash (eth_ip_tcp_pptp_select);
		tommy_hashdyn_insert (&eth_ip_tcp_pptp_hashtable,
			&eth_ip_tcp_pptp_instance->node, eth_ip_tcp_pptp_instance, hash);
		eth_ip_tcp_pptp_instance_reverse->eth_ip_tcp_pptp_select =
			*eth_ip_tcp_pptp_select_reverse;
		eth_ip_tcp_pptp_instance_reverse->time_record_leader = 0;
		eth_ip_tcp_pptp_instance_reverse->is_active_part =
			eth_ip_tcp_pptp_instance->is_active_part;
		eth_ip_tcp_pptp_instance_reverse->stand = 1;
		eth_ip_tcp_pptp_instance_reverse->state = eth_ip_tcp_pptp_CLOSED;
		eth_ip_tcp_pptp_instance_reverse->pair_instance =
			eth_ip_tcp_pptp_instance;
		init_buf_list (&eth_ip_tcp_pptp_instance_reverse->bufs);
		hash = eth_ip_tcp_pptp_hash (eth_ip_tcp_pptp_select_reverse);
		tommy_hashdyn_insert (&eth_ip_tcp_pptp_hashtable,
			&eth_ip_tcp_pptp_instance_reverse->node,
			eth_ip_tcp_pptp_instance_reverse, hash);
	}
	else
	{
		eth_ip_tcp_pptp_instance_reverse =
			eth_ip_tcp_pptp_instance->pair_instance;
		if (eth_ip_tcp_pptp_instance->time_record_leader)
			eth_ip_tcp_pptp_instance->rec_ptr =
				timer_update (&eth_ip_tcp_pptp_list, eth_ip_tcp_pptp_instance,
				eth_ip_tcp_pptp_instance->rec_ptr, now);
		else
			eth_ip_tcp_pptp_instance_reverse->rec_ptr =
				timer_update (&eth_ip_tcp_pptp_list,
				eth_ip_tcp_pptp_instance_reverse,
				eth_ip_tcp_pptp_instance_reverse->rec_ptr, now);
	}
}

void eth_ip_tcp_pptp_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is pptp layer\n");
	printf ("packet length is %d\n", length);
	printf ("------------packet end------------\n");
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_tcp_pptp_payload = payload;
	eth_ip_tcp_pptp_payload_length = length;
	eth_ip_tcp_pptp_data_assignment (payload);
	eth_ip_tcp_pptp_selector (now);
	eth_ip_tcp_pptp_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_tcp_pptp_list,
			&eth_ip_tcp_pptp_gap, &eth_ip_tcp_pptp_hashtable,
			offsetof (struct eth_ip_tcp_pptp_instance_t, node),
			eth_ip_tcp_pptp_free, now);
		ts = int_now;
	}
	memset (eth_ip_tcp_pptp_rubik_bitmap, 0,
		sizeof (struct eth_ip_tcp_pptp_rubik_bitmap_t));
	memset (eth_ip_tcp_pptp_transition_bitmap, 0,
		sizeof (struct eth_ip_tcp_pptp_transition_bitmap_t));
	if (eth_ip_tcp_pptp_has_buf)
	{
		free (eth_ip_tcp_pptp_buf);
		eth_ip_tcp_pptp_has_buf = 0;
	}
}
