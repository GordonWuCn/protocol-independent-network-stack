#include "eth_ip_gre_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct eth_ip_gre_instance_t *eth_ip_gre_instance;
struct eth_ip_gre_instance_t *eth_ip_gre_instance_reverse;
struct eth_ip_gre_select_t *eth_ip_gre_select;
struct eth_ip_gre_select_t *eth_ip_gre_select_reverse;
struct eth_ip_gre_instance_t *eth_ip_gre_fake_instance;
struct eth_ip_gre_instance_t *eth_ip_gre_fake_instance_reverse;
tommy_hashdyn eth_ip_gre_hashtable;
struct timer eth_ip_gre_list;
struct timeval eth_ip_gre_gap;
struct eth_ip_gre_GRE_header_t *eth_ip_gre_GRE_header;
struct eth_ip_gre_GRE_sequence_number_t *eth_ip_gre_GRE_sequence_number;
struct eth_ip_gre_GRE_ack_number_t *eth_ip_gre_GRE_ack_number;
eth_ip_gre_data_t *eth_ip_gre_data;
char eth_ip_gre_has_buf = 0;
u_char *eth_ip_gre_buf;
int eth_ip_gre_buf_length;
u_char *eth_ip_gre_payload;
int eth_ip_gre_payload_length;
struct eth_ip_gre_rubik_bitmap_t *eth_ip_gre_rubik_bitmap;
struct eth_ip_gre_transition_bitmap_t *eth_ip_gre_transition_bitmap;
struct buf_queue *eth_ip_gre_bufs;
void eth_ip_gre_init ()
{
	tommy_hashdyn_init (&eth_ip_gre_hashtable);
	eth_ip_gre_gap.tv_sec = 10;
	eth_ip_gre_gap.tv_usec = 0;
	eth_ip_gre_list.head = NULL;
	eth_ip_gre_list.tail = NULL;
	eth_ip_gre_instance = NULL;
	eth_ip_gre_fake_instance = malloc (sizeof (struct eth_ip_gre_instance_t));
	eth_ip_gre_fake_instance->is_active_part = malloc (sizeof (char));
	*(eth_ip_gre_fake_instance->is_active_part) = 1;
	eth_ip_gre_fake_instance->stand = 0;
	eth_ip_gre_fake_instance_reverse =
		malloc (sizeof (struct eth_ip_gre_instance_t));
	eth_ip_gre_fake_instance_reverse->is_active_part =
		eth_ip_gre_fake_instance->is_active_part;
	eth_ip_gre_fake_instance_reverse->stand = 1;
	eth_ip_gre_select = malloc (sizeof (struct eth_ip_gre_select_t));
	eth_ip_gre_select_reverse = malloc (sizeof (struct eth_ip_gre_select_t));
	memset (eth_ip_gre_select, 0, sizeof (struct eth_ip_gre_select_t));
	memset (eth_ip_gre_select_reverse, 0, sizeof (struct eth_ip_gre_select_t));
	eth_ip_gre_rubik_bitmap =
		malloc (sizeof (struct eth_ip_gre_rubik_bitmap_t));
	eth_ip_gre_transition_bitmap =
		malloc (sizeof (struct eth_ip_gre_transition_bitmap_t));
	memset (eth_ip_gre_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_rubik_bitmap_t));
	memset (eth_ip_gre_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_transition_bitmap_t));
}

char eth_ip_gre_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t eth_ip_gre_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_gre_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_gre_destroy (void)
{
	free_buf_list (eth_ip_gre_instance->bufs);
	free_buf_list (eth_ip_gre_instance_reverse->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_gre_hashtable,
		&eth_ip_gre_instance->node);
	tommy_hashdyn_remove_existing (&eth_ip_gre_hashtable,
		&eth_ip_gre_instance_reverse->node);
	if (eth_ip_gre_instance->time_record_leader)
		deregister_timer (&eth_ip_gre_list, eth_ip_gre_instance->rec_ptr);
	else
		deregister_timer (&eth_ip_gre_list,
			eth_ip_gre_instance_reverse->rec_ptr);
	free (eth_ip_gre_instance->eth_ip_gre_data);
	free (eth_ip_gre_instance->is_active_part);
	free (eth_ip_gre_instance);
	free (eth_ip_gre_instance_reverse);
}

void eth_ip_gre_free (void *inst)
{
	struct eth_ip_gre_instance_t *reverse =
		((struct eth_ip_gre_instance_t *) inst)->pair_instance;
	free_buf_list (reverse->bufs);
	free (reverse->eth_ip_gre_data);
	free (reverse->is_active_part);
	tommy_hashdyn_remove_existing (&eth_ip_gre_hashtable, &reverse->node);
	free (reverse);
	free_buf_list (((struct eth_ip_gre_instance_t *) inst)->bufs);
}

static void eth_ip_gre_dump (void);
void eth_ip_gre_dump ()
{
	if (*(eth_ip_gre_instance->is_active_part) ^ eth_ip_gre_instance->stand)
	{
		if ((1 && (eth_ip_gre_GRE_header->payload_length > 0)))
		{
			eth_ip_gre_transition_bitmap->tunneling_a = 1;
			eth_ip_gre_instance->state = eth_ip_gre_dump;
			eth_ip_gre_instance_reverse->state = eth_ip_gre_instance->state;
			eth_ip_gre_buf = eth_ip_gre_payload;
			eth_ip_gre_buf_length = eth_ip_gre_payload_length;
			return;
		}
		if ((1 && (eth_ip_gre_GRE_header->payload_length == 0)))
		{
			eth_ip_gre_transition_bitmap->only_ack_a = 1;
			eth_ip_gre_instance->state = eth_ip_gre_dump;
			eth_ip_gre_instance_reverse->state = eth_ip_gre_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_instance->is_active_part) ^ eth_ip_gre_instance->stand))
	{
		if ((1 && (eth_ip_gre_GRE_header->payload_length > 0)))
		{
			eth_ip_gre_transition_bitmap->tunneling_p = 1;
			eth_ip_gre_instance->state = eth_ip_gre_dump;
			eth_ip_gre_instance_reverse->state = eth_ip_gre_instance->state;
			eth_ip_gre_buf = eth_ip_gre_payload;
			eth_ip_gre_buf_length = eth_ip_gre_payload_length;
			return;
		}
		if ((1 && (eth_ip_gre_GRE_header->payload_length == 0)))
		{
			eth_ip_gre_transition_bitmap->only_ack_p = 1;
			eth_ip_gre_instance->state = eth_ip_gre_dump;
			eth_ip_gre_instance_reverse->state = eth_ip_gre_instance->state;
			return;
		}
		return;
	}
}

void eth_ip_gre_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_ip_gre_rubik_bitmap->eth_ip_gre_GRE_header = 1;
	eth_ip_gre_GRE_header =
		(struct eth_ip_gre_GRE_header_t *) (payload + cur_pos);
	cur_pos += 8;
	eth_ip_gre_GRE_header->protocol = ntohs (eth_ip_gre_GRE_header->protocol);
	eth_ip_gre_GRE_header->payload_length =
		ntohs (eth_ip_gre_GRE_header->payload_length);
	if (eth_ip_gre_GRE_header->S)
	{
		eth_ip_gre_rubik_bitmap->eth_ip_gre_GRE_sequence_number = 1;
		eth_ip_gre_GRE_sequence_number =
			(struct eth_ip_gre_GRE_sequence_number_t *) (payload + cur_pos);
		cur_pos += 4;
	}
	if (eth_ip_gre_GRE_header->A)
	{
		eth_ip_gre_rubik_bitmap->eth_ip_gre_GRE_ack_number = 1;
		eth_ip_gre_GRE_ack_number =
			(struct eth_ip_gre_GRE_ack_number_t *) (payload + cur_pos);
		cur_pos += 4;
	}
	eth_ip_gre_payload_length -= cur_pos;
	eth_ip_gre_payload += cur_pos;
	eth_ip_gre_select->src_src_addr = eth_ip_ip_hdr->src_addr;
	eth_ip_gre_select->dst_dst_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_gre_select_reverse->src_src_addr = eth_ip_ip_hdr->dst_addr;
	eth_ip_gre_select_reverse->dst_dst_addr = eth_ip_ip_hdr->src_addr;
}

void eth_ip_gre_selector (struct timeval *now)
{
	uint32_t hash = eth_ip_gre_hash (eth_ip_gre_select);
	eth_ip_gre_instance =
		tommy_hashdyn_search (&eth_ip_gre_hashtable, eth_ip_gre_compare,
		eth_ip_gre_select, hash);
	if (!eth_ip_gre_instance)
	{
		eth_ip_gre_instance =
			(struct eth_ip_gre_instance_t *) malloc (sizeof (struct
				eth_ip_gre_instance_t));
		memset (eth_ip_gre_instance, 0, sizeof (struct eth_ip_gre_select_t));
		eth_ip_gre_instance_reverse =
			(struct eth_ip_gre_instance_t *) malloc (sizeof (struct
				eth_ip_gre_instance_t));
		memset (eth_ip_gre_instance_reverse, 0,
			sizeof (struct eth_ip_gre_select_t));
		eth_ip_gre_data =
			(eth_ip_gre_data_t *) malloc (sizeof (eth_ip_gre_data_t));
		eth_ip_gre_data->short_PPP = 0;
		eth_ip_gre_instance->eth_ip_gre_select = *eth_ip_gre_select;
		eth_ip_gre_instance->eth_ip_gre_data = eth_ip_gre_data;
		eth_ip_gre_instance->time_record_leader = 1;
		eth_ip_gre_instance->is_active_part = malloc (sizeof (char));
		eth_ip_gre_instance->stand = 0;
		*(eth_ip_gre_instance->is_active_part) = 1;
		eth_ip_gre_instance->state = eth_ip_gre_dump;
		eth_ip_gre_instance->rec_ptr =
			timer_update (&eth_ip_gre_list, eth_ip_gre_instance, NULL, now);
		eth_ip_gre_instance->pair_instance = eth_ip_gre_instance_reverse;
		init_buf_list (&eth_ip_gre_instance->bufs);
		hash = eth_ip_gre_hash (eth_ip_gre_select);
		tommy_hashdyn_insert (&eth_ip_gre_hashtable, &eth_ip_gre_instance->node,
			eth_ip_gre_instance, hash);
		eth_ip_gre_instance_reverse->eth_ip_gre_select =
			*eth_ip_gre_select_reverse;
		eth_ip_gre_instance_reverse->eth_ip_gre_data = eth_ip_gre_data;
		eth_ip_gre_instance_reverse->time_record_leader = 0;
		eth_ip_gre_instance_reverse->is_active_part =
			eth_ip_gre_instance->is_active_part;
		eth_ip_gre_instance_reverse->stand = 1;
		eth_ip_gre_instance_reverse->state = eth_ip_gre_dump;
		eth_ip_gre_instance_reverse->pair_instance = eth_ip_gre_instance;
		init_buf_list (&eth_ip_gre_instance_reverse->bufs);
		hash = eth_ip_gre_hash (eth_ip_gre_select_reverse);
		tommy_hashdyn_insert (&eth_ip_gre_hashtable,
			&eth_ip_gre_instance_reverse->node, eth_ip_gre_instance_reverse,
			hash);
	}
	else
	{
		eth_ip_gre_instance_reverse = eth_ip_gre_instance->pair_instance;
		eth_ip_gre_data = eth_ip_gre_instance->eth_ip_gre_data;
		if (eth_ip_gre_instance->time_record_leader)
			eth_ip_gre_instance->rec_ptr =
				timer_update (&eth_ip_gre_list, eth_ip_gre_instance,
				eth_ip_gre_instance->rec_ptr, now);
		else
			eth_ip_gre_instance_reverse->rec_ptr =
				timer_update (&eth_ip_gre_list, eth_ip_gre_instance_reverse,
				eth_ip_gre_instance_reverse->rec_ptr, now);
	}
}

void eth_ip_gre_ppp_parse (u_char *, uint32_t, struct timeval *);
void eth_ip_gre_parse (u_char * payload, uint32_t length, struct timeval *now)
{
	printf ("this is gre layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_gre_payload = payload;
	eth_ip_gre_payload_length = length;
	eth_ip_gre_data_assignment (payload);
	eth_ip_gre_selector (now);
	eth_ip_gre_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_gre_list, &eth_ip_gre_gap,
			&eth_ip_gre_hashtable, offsetof (struct eth_ip_gre_instance_t,
				node), eth_ip_gre_free, now);
		ts = int_now;
	}
	if (((eth_ip_gre_GRE_header->protocol == 34827)
			&& (eth_ip_gre_transition_bitmap->tunneling_a
				|| eth_ip_gre_transition_bitmap->tunneling_p)))
	{
		eth_ip_gre_ppp_parse (eth_ip_gre_buf, eth_ip_gre_buf_length, now);
	}
	memset (eth_ip_gre_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_rubik_bitmap_t));
	memset (eth_ip_gre_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_transition_bitmap_t));
	if (eth_ip_gre_has_buf)
	{
		free (eth_ip_gre_buf);
		eth_ip_gre_has_buf = 0;
	}
}
