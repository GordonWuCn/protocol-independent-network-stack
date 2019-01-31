#include "eth_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct eth_instance_t *eth_instance;
struct eth_select_t *eth_select;
struct eth_instance_t *eth_fake_instance;
tommy_hashdyn eth_hashtable;
struct timer eth_list;
struct timeval eth_gap;
struct eth_eth_header_t *eth_eth_header;
char eth_has_buf = 0;
u_char *eth_buf;
int eth_buf_length;
u_char *eth_payload;
int eth_payload_length;
struct eth_rubik_bitmap_t *eth_rubik_bitmap;
struct eth_transition_bitmap_t *eth_transition_bitmap;
struct buf_queue *eth_bufs;
void eth_init ()
{
	tommy_hashdyn_init (&eth_hashtable);
	eth_gap.tv_sec = 10;
	eth_gap.tv_usec = 0;
	eth_list.head = NULL;
	eth_list.tail = NULL;
	eth_instance = NULL;
	eth_fake_instance = malloc (sizeof (struct eth_instance_t));
	eth_select = malloc (sizeof (struct eth_select_t));
	memset (eth_select, 0, sizeof (struct eth_select_t));
	eth_rubik_bitmap = malloc (sizeof (struct eth_rubik_bitmap_t));
	eth_transition_bitmap = malloc (sizeof (struct eth_transition_bitmap_t));
	memset (eth_rubik_bitmap, 0, sizeof (struct eth_rubik_bitmap_t));
	memset (eth_transition_bitmap, 0, sizeof (struct eth_transition_bitmap_t));
}

char eth_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t eth_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_select_t);
	return memcmp (arg, obj, size);
}

void eth_destroy ()
{
	free_buf_list (eth_instance->bufs);
	tommy_hashdyn_remove_existing (&eth_hashtable, &eth_instance->node);
	deregister_timer (&eth_list, eth_instance->rec_ptr);
	free (eth_instance);
}

void eth_free (void *inst)
{
	free_buf_list (((struct eth_instance_t *) inst)->bufs);
}

static void eth_dump (void);
void eth_dump ()
{
	if (1)
	{
		eth_transition_bitmap->incoming = 1;
		eth_instance->state = eth_dump;
		eth_buf = eth_payload;
		eth_buf_length = eth_payload_length;
		return;
	}
	return;
}

void eth_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_rubik_bitmap->eth_eth_header = 1;
	eth_eth_header = (struct eth_eth_header_t *) (payload + cur_pos);
	cur_pos += 14;
	eth_eth_header->eth_type = ntohs (eth_eth_header->eth_type);
	eth_payload_length -= cur_pos;
	eth_payload += cur_pos;
	eth_select->src_eth_src_upper = eth_eth_header->eth_src_upper;
	eth_select->src_eth_src_middle = eth_eth_header->eth_src_middle;
	eth_select->src_eth_src_lower = eth_eth_header->eth_src_lower;
	eth_select->dst_eth_dst_upper = eth_eth_header->eth_dst_upper;
	eth_select->dst_eth_dst_middle = eth_eth_header->eth_dst_middle;
	eth_select->dst_eth_dst_lower = eth_eth_header->eth_dst_lower;
}

void eth_selector (struct timeval *now)
{
	if (!0)
	{
		eth_instance = eth_fake_instance;
		eth_instance->state = eth_dump;
		eth_instance->bufs = NULL;
		return;
	}
	uint32_t hash = eth_hash (eth_select);
	eth_instance =
		tommy_hashdyn_search (&eth_hashtable, eth_compare, eth_select, hash);
	if (!eth_instance)
	{
		eth_instance =
			(struct eth_instance_t *) malloc (sizeof (struct eth_instance_t));
		memset (eth_instance, 0, sizeof (struct eth_select_t));
		eth_instance->eth_select = *eth_select;
		eth_instance->state = eth_dump;
		eth_instance->rec_ptr =
			timer_update (&eth_list, eth_instance, NULL, now);
		init_buf_list (&eth_instance->bufs);
		hash = eth_hash (eth_select);
		tommy_hashdyn_insert (&eth_hashtable, &eth_instance->node, eth_instance,
			hash);
	}
	else
	{
		eth_instance->rec_ptr =
			timer_update (&eth_list, eth_instance, eth_instance->rec_ptr, now);
	}
}

void eth_ip_parse (u_char *, uint32_t, struct timeval *);
void eth_parse (u_char * payload, uint32_t length, struct timeval *now)
{
	printf ("----------incoming packet---------\n");
	printf ("this is eth layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_payload = payload;
	eth_payload_length = length;
	eth_data_assignment (payload);
	eth_selector (now);
	eth_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_list, &eth_gap, &eth_hashtable,
			offsetof (struct eth_instance_t, node), eth_free, now);
		ts = int_now;
	}
	eth_ip_parse (eth_buf, eth_buf_length, now);
	memset (eth_rubik_bitmap, 0, sizeof (struct eth_rubik_bitmap_t));
	memset (eth_transition_bitmap, 0, sizeof (struct eth_transition_bitmap_t));
	if (eth_has_buf)
	{
		free (eth_buf);
		eth_has_buf = 0;
	}
}
