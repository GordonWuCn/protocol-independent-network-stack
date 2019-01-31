#include "loopback_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct loopback_instance_t *loopback_instance;
struct loopback_select_t *loopback_select;
struct loopback_instance_t *loopback_fake_instance;
tommy_hashdyn loopback_hashtable;
struct timer loopback_list;
struct timeval loopback_gap;
struct loopback_loopback_header_t *loopback_loopback_header;
char loopback_has_buf = 0;
u_char *loopback_buf;
int loopback_buf_length;
u_char *loopback_payload;
int loopback_payload_length;
struct loopback_rubik_bitmap_t *loopback_rubik_bitmap;
struct loopback_transition_bitmap_t *loopback_transition_bitmap;
struct buf_queue *loopback_bufs;
void loopback_init ()
{
	tommy_hashdyn_init (&loopback_hashtable);
	loopback_gap.tv_sec = 10;
	loopback_gap.tv_usec = 0;
	loopback_list.head = NULL;
	loopback_list.tail = NULL;
	loopback_instance = NULL;
	loopback_fake_instance = malloc (sizeof (struct loopback_instance_t));
	loopback_select = malloc (sizeof (struct loopback_select_t));
	memset (loopback_select, 0, sizeof (struct loopback_select_t));
	loopback_rubik_bitmap = malloc (sizeof (struct loopback_rubik_bitmap_t));
	loopback_transition_bitmap =
		malloc (sizeof (struct loopback_transition_bitmap_t));
	memset (loopback_rubik_bitmap, 0, sizeof (struct loopback_rubik_bitmap_t));
	memset (loopback_transition_bitmap, 0,
		sizeof (struct loopback_transition_bitmap_t));
}

char loopback_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t loopback_hash (void *obj)
{
	uint64_t size = sizeof (struct loopback_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int loopback_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct loopback_select_t);
	return memcmp (arg, obj, size);
}

void loopback_destroy ()
{
	free_buf_list (loopback_instance->bufs);
	tommy_hashdyn_remove_existing (&loopback_hashtable,
		&loopback_instance->node);
	deregister_timer (&loopback_list, loopback_instance->rec_ptr);
	free (loopback_instance);
}

void loopback_free (void *inst)
{
	free_buf_list (((struct loopback_instance_t *) inst)->bufs);
}

static void loopback_dump (void);
void loopback_dump ()
{
	if (1)
	{
		loopback_transition_bitmap->incoming = 1;
		loopback_instance->state = loopback_dump;
		loopback_buf = loopback_payload;
		loopback_buf_length = loopback_payload_length;
		return;
	}
	return;
}

void loopback_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	loopback_rubik_bitmap->loopback_loopback_header = 1;
	loopback_loopback_header =
		(struct loopback_loopback_header_t *) (payload + cur_pos);
	cur_pos += 4;
	loopback_payload_length -= cur_pos;
	loopback_payload += cur_pos;
	loopback_select->src_family = loopback_loopback_header->family;
	loopback_select->dst_family = loopback_loopback_header->family;
}

void loopback_selector (struct timeval *now)
{
	if (!0)
	{
		loopback_instance = loopback_fake_instance;
		loopback_instance->state = loopback_dump;
		loopback_instance->bufs = NULL;
		return;
	}
	uint32_t hash = loopback_hash (loopback_select);
	loopback_instance =
		tommy_hashdyn_search (&loopback_hashtable, loopback_compare,
		loopback_select, hash);
	if (!loopback_instance)
	{
		loopback_instance =
			(struct loopback_instance_t *) malloc (sizeof (struct
				loopback_instance_t));
		memset (loopback_instance, 0, sizeof (struct loopback_select_t));
		loopback_instance->loopback_select = *loopback_select;
		loopback_instance->state = loopback_dump;
		loopback_instance->rec_ptr =
			timer_update (&loopback_list, loopback_instance, NULL, now);
		init_buf_list (&loopback_instance->bufs);
		hash = loopback_hash (loopback_select);
		tommy_hashdyn_insert (&loopback_hashtable, &loopback_instance->node,
			loopback_instance, hash);
	}
	else
	{
		loopback_instance->rec_ptr =
			timer_update (&loopback_list, loopback_instance,
			loopback_instance->rec_ptr, now);
	}
}

void loopback_ip_parse (u_char *, uint32_t, struct timeval *);
void loopback_parse (u_char * payload, uint32_t length, struct timeval *now)
{
	printf ("----------incoming packet---------\n");
	printf ("this is loopback layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	loopback_payload = payload;
	loopback_payload_length = length;
	loopback_data_assignment (payload);
	loopback_selector (now);
	loopback_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&loopback_list, &loopback_gap,
			&loopback_hashtable, offsetof (struct loopback_instance_t, node),
			loopback_free, now);
		ts = int_now;
	}
	loopback_ip_parse (loopback_buf, loopback_buf_length, now);
	memset (loopback_rubik_bitmap, 0, sizeof (struct loopback_rubik_bitmap_t));
	memset (loopback_transition_bitmap, 0,
		sizeof (struct loopback_transition_bitmap_t));
	if (loopback_has_buf)
	{
		free (loopback_buf);
		loopback_has_buf = 0;
	}
}
