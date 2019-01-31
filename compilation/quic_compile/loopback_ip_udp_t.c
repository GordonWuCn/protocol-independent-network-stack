#include "loopback_ip_udp_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct loopback_ip_udp_instance_t *loopback_ip_udp_instance;
struct loopback_ip_udp_select_t *loopback_ip_udp_select;
struct loopback_ip_udp_instance_t *loopback_ip_udp_fake_instance;
tommy_hashdyn loopback_ip_udp_hashtable;
struct timer loopback_ip_udp_list;
struct timeval loopback_ip_udp_gap;
struct loopback_ip_udp_udp_hdr_t *loopback_ip_udp_udp_hdr;
loopback_ip_udp_data_t *loopback_ip_udp_data;
char loopback_ip_udp_has_buf = 0;
u_char *loopback_ip_udp_buf;
int loopback_ip_udp_buf_length;
u_char *loopback_ip_udp_payload;
int loopback_ip_udp_payload_length;
struct loopback_ip_udp_rubik_bitmap_t *loopback_ip_udp_rubik_bitmap;
struct loopback_ip_udp_transition_bitmap_t *loopback_ip_udp_transition_bitmap;
struct buf_queue *loopback_ip_udp_bufs;
void loopback_ip_udp_init ()
{
	tommy_hashdyn_init (&loopback_ip_udp_hashtable);
	loopback_ip_udp_gap.tv_sec = 10;
	loopback_ip_udp_gap.tv_usec = 0;
	loopback_ip_udp_list.head = NULL;
	loopback_ip_udp_list.tail = NULL;
	loopback_ip_udp_instance = NULL;
	loopback_ip_udp_fake_instance =
		malloc (sizeof (struct loopback_ip_udp_instance_t));
	loopback_ip_udp_select = malloc (sizeof (struct loopback_ip_udp_select_t));
	memset (loopback_ip_udp_select, 0,
		sizeof (struct loopback_ip_udp_select_t));
	loopback_ip_udp_rubik_bitmap =
		malloc (sizeof (struct loopback_ip_udp_rubik_bitmap_t));
	loopback_ip_udp_transition_bitmap =
		malloc (sizeof (struct loopback_ip_udp_transition_bitmap_t));
	memset (loopback_ip_udp_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_rubik_bitmap_t));
	memset (loopback_ip_udp_transition_bitmap, 0,
		sizeof (struct loopback_ip_udp_transition_bitmap_t));
}

char loopback_ip_udp_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t loopback_ip_udp_hash (void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_udp_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int loopback_ip_udp_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_udp_select_t);
	return memcmp (arg, obj, size);
}

void loopback_ip_udp_destroy ()
{
	free (loopback_ip_udp_instance->loopback_ip_udp_data);
	free_buf_list (loopback_ip_udp_instance->bufs);
	tommy_hashdyn_remove_existing (&loopback_ip_udp_hashtable,
		&loopback_ip_udp_instance->node);
	deregister_timer (&loopback_ip_udp_list, loopback_ip_udp_instance->rec_ptr);
	free (loopback_ip_udp_instance);
}

void loopback_ip_udp_free (void *inst)
{
	free (((struct loopback_ip_udp_instance_t *) inst)->loopback_ip_udp_data);
	free_buf_list (((struct loopback_ip_udp_instance_t *) inst)->bufs);
}

static void loopback_ip_udp_start (void);
void loopback_ip_udp_start ()
{
	if (1)
	{
		loopback_ip_udp_transition_bitmap->direct_dump = 1;
		loopback_ip_udp_instance->state = loopback_ip_udp_start;
		loopback_ip_udp_buf_length = loopback_ip_udp_payload_length;
		loopback_ip_udp_buf = loopback_ip_udp_payload;
		return;
	}
	return;
}

void loopback_ip_udp_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	loopback_ip_udp_rubik_bitmap->loopback_ip_udp_udp_hdr = 1;
	loopback_ip_udp_udp_hdr =
		(struct loopback_ip_udp_udp_hdr_t *) (payload + cur_pos);
	cur_pos += 8;
	loopback_ip_udp_payload_length -= cur_pos;
	loopback_ip_udp_payload += cur_pos;
	loopback_ip_udp_select->src_src_port = loopback_ip_udp_udp_hdr->src_port;
	loopback_ip_udp_select->dst_dst_port = loopback_ip_udp_udp_hdr->dst_port;
}

void loopback_ip_udp_selector (struct timeval *now)
{
	if (0)
	{
		loopback_ip_udp_instance = loopback_ip_udp_fake_instance;
		loopback_ip_udp_instance->state = loopback_ip_udp_start;
		loopback_ip_udp_instance->loopback_ip_udp_data = NULL;
		loopback_ip_udp_instance->bufs = NULL;
		return;
	}
	uint32_t hash = loopback_ip_udp_hash (loopback_ip_udp_select);
	loopback_ip_udp_instance =
		tommy_hashdyn_search (&loopback_ip_udp_hashtable,
		loopback_ip_udp_compare, loopback_ip_udp_select, hash);
	if (!loopback_ip_udp_instance)
	{
		loopback_ip_udp_instance =
			(struct loopback_ip_udp_instance_t *) malloc (sizeof (struct
				loopback_ip_udp_instance_t));
		memset (loopback_ip_udp_instance, 0,
			sizeof (struct loopback_ip_udp_select_t));
		loopback_ip_udp_data =
			(loopback_ip_udp_data_t *) malloc (sizeof (loopback_ip_udp_data_t));
		loopback_ip_udp_instance->loopback_ip_udp_select =
			*loopback_ip_udp_select;
		loopback_ip_udp_instance->loopback_ip_udp_data = loopback_ip_udp_data;
		loopback_ip_udp_instance->state = loopback_ip_udp_start;
		loopback_ip_udp_instance->rec_ptr =
			timer_update (&loopback_ip_udp_list, loopback_ip_udp_instance, NULL,
			now);
		init_buf_list (&loopback_ip_udp_instance->bufs);
		hash = loopback_ip_udp_hash (loopback_ip_udp_select);
		tommy_hashdyn_insert (&loopback_ip_udp_hashtable,
			&loopback_ip_udp_instance->node, loopback_ip_udp_instance, hash);
	}
	else
	{
		loopback_ip_udp_data = loopback_ip_udp_instance->loopback_ip_udp_data;
		loopback_ip_udp_instance->rec_ptr =
			timer_update (&loopback_ip_udp_list, loopback_ip_udp_instance,
			loopback_ip_udp_instance->rec_ptr, now);
	}
}

void loopback_ip_udp_quic_header_parse (u_char *, uint32_t, struct timeval *);
void loopback_ip_udp_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is udp layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	loopback_ip_udp_payload = payload;
	loopback_ip_udp_payload_length = length;
	loopback_ip_udp_data_assignment (payload);
	loopback_ip_udp_selector (now);
	loopback_ip_udp_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&loopback_ip_udp_list,
			&loopback_ip_udp_gap, &loopback_ip_udp_hashtable,
			offsetof (struct loopback_ip_udp_instance_t, node),
			loopback_ip_udp_free, now);
		ts = int_now;
	}
	loopback_ip_udp_quic_header_parse (loopback_ip_udp_buf,
		loopback_ip_udp_buf_length, now);
	memset (loopback_ip_udp_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_rubik_bitmap_t));
	memset (loopback_ip_udp_transition_bitmap, 0,
		sizeof (struct loopback_ip_udp_transition_bitmap_t));
	if (loopback_ip_udp_has_buf)
	{
		free (loopback_ip_udp_buf);
		loopback_ip_udp_has_buf = 0;
	}
}
