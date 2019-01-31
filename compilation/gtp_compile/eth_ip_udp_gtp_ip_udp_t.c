#include "eth_ip_udp_gtp_ip_udp_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct eth_ip_udp_gtp_ip_udp_instance_t *eth_ip_udp_gtp_ip_udp_instance;
struct eth_ip_udp_gtp_ip_udp_select_t *eth_ip_udp_gtp_ip_udp_select;
struct eth_ip_udp_gtp_ip_udp_instance_t *eth_ip_udp_gtp_ip_udp_fake_instance;
tommy_hashdyn eth_ip_udp_gtp_ip_udp_hashtable;
struct timer eth_ip_udp_gtp_ip_udp_list;
struct timeval eth_ip_udp_gtp_ip_udp_gap;
struct eth_ip_udp_gtp_ip_udp_udp_hdr_t *eth_ip_udp_gtp_ip_udp_udp_hdr;
char eth_ip_udp_gtp_ip_udp_has_buf = 0;
u_char *eth_ip_udp_gtp_ip_udp_buf;
int eth_ip_udp_gtp_ip_udp_buf_length;
u_char *eth_ip_udp_gtp_ip_udp_payload;
int eth_ip_udp_gtp_ip_udp_payload_length;
struct eth_ip_udp_gtp_ip_udp_rubik_bitmap_t *eth_ip_udp_gtp_ip_udp_rubik_bitmap;
struct eth_ip_udp_gtp_ip_udp_transition_bitmap_t
	*eth_ip_udp_gtp_ip_udp_transition_bitmap;
struct buf_queue *eth_ip_udp_gtp_ip_udp_bufs;
void eth_ip_udp_gtp_ip_udp_init ()
{
	tommy_hashdyn_init (&eth_ip_udp_gtp_ip_udp_hashtable);
	eth_ip_udp_gtp_ip_udp_gap.tv_sec = 10;
	eth_ip_udp_gtp_ip_udp_gap.tv_usec = 0;
	eth_ip_udp_gtp_ip_udp_list.head = NULL;
	eth_ip_udp_gtp_ip_udp_list.tail = NULL;
	eth_ip_udp_gtp_ip_udp_instance = NULL;
	eth_ip_udp_gtp_ip_udp_fake_instance =
		malloc (sizeof (struct eth_ip_udp_gtp_ip_udp_instance_t));
	eth_ip_udp_gtp_ip_udp_select =
		malloc (sizeof (struct eth_ip_udp_gtp_ip_udp_select_t));
	memset (eth_ip_udp_gtp_ip_udp_select, 0,
		sizeof (struct eth_ip_udp_gtp_ip_udp_select_t));
	eth_ip_udp_gtp_ip_udp_rubik_bitmap =
		malloc (sizeof (struct eth_ip_udp_gtp_ip_udp_rubik_bitmap_t));
	eth_ip_udp_gtp_ip_udp_transition_bitmap =
		malloc (sizeof (struct eth_ip_udp_gtp_ip_udp_transition_bitmap_t));
	memset (eth_ip_udp_gtp_ip_udp_rubik_bitmap, 0,
		sizeof (struct eth_ip_udp_gtp_ip_udp_rubik_bitmap_t));
	memset (eth_ip_udp_gtp_ip_udp_transition_bitmap, 0,
		sizeof (struct eth_ip_udp_gtp_ip_udp_transition_bitmap_t));
}

char eth_ip_udp_gtp_ip_udp_has_hole (uint64_t meta, int length,
	struct buf_queue *buf)
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

uint32_t eth_ip_udp_gtp_ip_udp_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_udp_gtp_ip_udp_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_udp_gtp_ip_udp_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_udp_gtp_ip_udp_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_udp_gtp_ip_udp_destroy ()
{
	free_buf_list (eth_ip_udp_gtp_ip_udp_instance->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_udp_gtp_ip_udp_hashtable,
		&eth_ip_udp_gtp_ip_udp_instance->node);
	deregister_timer (&eth_ip_udp_gtp_ip_udp_list,
		eth_ip_udp_gtp_ip_udp_instance->rec_ptr);
	free (eth_ip_udp_gtp_ip_udp_instance);
}

void eth_ip_udp_gtp_ip_udp_free (void *inst)
{
	free_buf_list (((struct eth_ip_udp_gtp_ip_udp_instance_t *) inst)->bufs);
}

static void eth_ip_udp_gtp_ip_udp_start (void);
void eth_ip_udp_gtp_ip_udp_start ()
{
	if (1)
	{
		eth_ip_udp_gtp_ip_udp_transition_bitmap->direct_dump = 1;
		eth_ip_udp_gtp_ip_udp_instance->state = eth_ip_udp_gtp_ip_udp_start;
		eth_ip_udp_gtp_ip_udp_buf_length = eth_ip_udp_gtp_ip_udp_payload_length;
		eth_ip_udp_gtp_ip_udp_buf = eth_ip_udp_gtp_ip_udp_payload;
		return;
	}
	return;
}

void eth_ip_udp_gtp_ip_udp_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_ip_udp_gtp_ip_udp_rubik_bitmap->eth_ip_udp_gtp_ip_udp_udp_hdr = 1;
	eth_ip_udp_gtp_ip_udp_udp_hdr =
		(struct eth_ip_udp_gtp_ip_udp_udp_hdr_t *) (payload + cur_pos);
	cur_pos += 8;
	eth_ip_udp_gtp_ip_udp_payload_length -= cur_pos;
	eth_ip_udp_gtp_ip_udp_payload += cur_pos;
	eth_ip_udp_gtp_ip_udp_select->src_src_port =
		eth_ip_udp_gtp_ip_udp_udp_hdr->src_port;
	eth_ip_udp_gtp_ip_udp_select->dst_dst_port =
		eth_ip_udp_gtp_ip_udp_udp_hdr->dst_port;
}

void eth_ip_udp_gtp_ip_udp_selector (struct timeval *now)
{
	if (!0)
	{
		eth_ip_udp_gtp_ip_udp_instance = eth_ip_udp_gtp_ip_udp_fake_instance;
		eth_ip_udp_gtp_ip_udp_instance->state = eth_ip_udp_gtp_ip_udp_start;
		eth_ip_udp_gtp_ip_udp_instance->bufs = NULL;
		return;
	}
	uint32_t hash = eth_ip_udp_gtp_ip_udp_hash (eth_ip_udp_gtp_ip_udp_select);
	eth_ip_udp_gtp_ip_udp_instance =
		tommy_hashdyn_search (&eth_ip_udp_gtp_ip_udp_hashtable,
		eth_ip_udp_gtp_ip_udp_compare, eth_ip_udp_gtp_ip_udp_select, hash);
	if (!eth_ip_udp_gtp_ip_udp_instance)
	{
		eth_ip_udp_gtp_ip_udp_instance =
			(struct eth_ip_udp_gtp_ip_udp_instance_t *) malloc (sizeof (struct
				eth_ip_udp_gtp_ip_udp_instance_t));
		memset (eth_ip_udp_gtp_ip_udp_instance, 0,
			sizeof (struct eth_ip_udp_gtp_ip_udp_select_t));
		eth_ip_udp_gtp_ip_udp_instance->eth_ip_udp_gtp_ip_udp_select =
			*eth_ip_udp_gtp_ip_udp_select;
		eth_ip_udp_gtp_ip_udp_instance->state = eth_ip_udp_gtp_ip_udp_start;
		eth_ip_udp_gtp_ip_udp_instance->rec_ptr =
			timer_update (&eth_ip_udp_gtp_ip_udp_list,
			eth_ip_udp_gtp_ip_udp_instance, NULL, now);
		init_buf_list (&eth_ip_udp_gtp_ip_udp_instance->bufs);
		hash = eth_ip_udp_gtp_ip_udp_hash (eth_ip_udp_gtp_ip_udp_select);
		tommy_hashdyn_insert (&eth_ip_udp_gtp_ip_udp_hashtable,
			&eth_ip_udp_gtp_ip_udp_instance->node,
			eth_ip_udp_gtp_ip_udp_instance, hash);
	}
	else
	{
		eth_ip_udp_gtp_ip_udp_instance->rec_ptr =
			timer_update (&eth_ip_udp_gtp_ip_udp_list,
			eth_ip_udp_gtp_ip_udp_instance,
			eth_ip_udp_gtp_ip_udp_instance->rec_ptr, now);
	}
}

void eth_ip_udp_gtp_ip_udp_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is udp layer\n");
	printf ("packet length is %d\n", length);
	printf ("------------packet end------------\n");
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_udp_gtp_ip_udp_payload = payload;
	eth_ip_udp_gtp_ip_udp_payload_length = length;
	eth_ip_udp_gtp_ip_udp_data_assignment (payload);
	eth_ip_udp_gtp_ip_udp_selector (now);
	eth_ip_udp_gtp_ip_udp_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_udp_gtp_ip_udp_list,
			&eth_ip_udp_gtp_ip_udp_gap, &eth_ip_udp_gtp_ip_udp_hashtable,
			offsetof (struct eth_ip_udp_gtp_ip_udp_instance_t, node),
			eth_ip_udp_gtp_ip_udp_free, now);
		ts = int_now;
	}
	memset (eth_ip_udp_gtp_ip_udp_rubik_bitmap, 0,
		sizeof (struct eth_ip_udp_gtp_ip_udp_rubik_bitmap_t));
	memset (eth_ip_udp_gtp_ip_udp_transition_bitmap, 0,
		sizeof (struct eth_ip_udp_gtp_ip_udp_transition_bitmap_t));
	if (eth_ip_udp_gtp_ip_udp_has_buf)
	{
		free (eth_ip_udp_gtp_ip_udp_buf);
		eth_ip_udp_gtp_ip_udp_has_buf = 0;
	}
}
