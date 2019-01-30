#include "loopback_ip_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
#define loopback_ip_THRESHOLD 10
struct loopback_ip_instance_t *loopback_ip_instance;
struct loopback_ip_select_t *loopback_ip_select;
struct loopback_ip_instance_t *loopback_ip_fake_instance;
tommy_hashdyn loopback_ip_hashtable;
struct timer loopback_ip_list;
struct timeval loopback_ip_gap;
struct loopback_ip_ip_hdr_t *loopback_ip_ip_hdr;
loopback_ip_data_t *loopback_ip_data;
char loopback_ip_has_buf = 0;
u_char *loopback_ip_buf;
int loopback_ip_buf_length;
u_char *loopback_ip_payload;
int loopback_ip_payload_length;
struct loopback_ip_rubik_bitmap_t *loopback_ip_rubik_bitmap;
struct loopback_ip_transition_bitmap_t *loopback_ip_transition_bitmap;
struct buf_queue *loopback_ip_bufs;
void loopback_ip_init ()
{
	tommy_hashdyn_init (&loopback_ip_hashtable);
	loopback_ip_gap.tv_sec = 10;
	loopback_ip_gap.tv_usec = 0;
	loopback_ip_list.head = NULL;
	loopback_ip_list.tail = NULL;
	loopback_ip_instance = NULL;
	loopback_ip_fake_instance = malloc (sizeof (struct loopback_ip_instance_t));
	loopback_ip_select = malloc (sizeof (struct loopback_ip_select_t));
	memset (loopback_ip_select, 0, sizeof (struct loopback_ip_select_t));
	loopback_ip_rubik_bitmap =
		malloc (sizeof (struct loopback_ip_rubik_bitmap_t));
	loopback_ip_transition_bitmap =
		malloc (sizeof (struct loopback_ip_transition_bitmap_t));
	memset (loopback_ip_rubik_bitmap, 0,
		sizeof (struct loopback_ip_rubik_bitmap_t));
	memset (loopback_ip_transition_bitmap, 0,
		sizeof (struct loopback_ip_transition_bitmap_t));
}

char loopback_ip_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t loopback_ip_hash (void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int loopback_ip_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_select_t);
	return memcmp (arg, obj, size);
}

void loopback_ip_destroy ()
{
	free (loopback_ip_instance->loopback_ip_data);
	free_buf_list (loopback_ip_instance->bufs);
	tommy_hashdyn_remove_existing (&loopback_ip_hashtable,
		&loopback_ip_instance->node);
	deregister_timer (&loopback_ip_list, loopback_ip_instance->rec_ptr);
	free (loopback_ip_instance);
}

void loopback_ip_free (void *inst)
{
	free (((struct loopback_ip_instance_t *) inst)->loopback_ip_data);
	free_buf_list (((struct loopback_ip_instance_t *) inst)->bufs);
}

static void loopback_ip_direct_dump (void);
static void loopback_ip_buffering (void);
void loopback_ip_direct_dump ()
{
	if ((loopback_ip_ip_hdr->dont_frag || (!loopback_ip_ip_hdr->dont_frag
				&& !loopback_ip_ip_hdr->more_frag)))
	{
		loopback_ip_transition_bitmap->no_buffer = 1;
		loopback_ip_instance->state = loopback_ip_direct_dump;
		loopback_ip_buf = loopback_ip_payload;
		loopback_ip_buf_length = loopback_ip_payload_length;
		return;
	}
	if ((loopback_ip_ip_hdr->more_frag && !loopback_ip_ip_hdr->dont_frag))
	{
		loopback_ip_transition_bitmap->has_buffer = 1;
		loopback_ip_instance->state = loopback_ip_buffering;
		loopback_ip_bufs = loopback_ip_instance->bufs;
		if (loopback_ip_bufs->is_tree
			|| loopback_ip_bufs->packet_count > loopback_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (loopback_ip_payload_length);
			memcpy (node->buf.buf, loopback_ip_payload,
				loopback_ip_payload_length);
			node->buf.len = loopback_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(loopback_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_buf_length =
					((struct buffer_node *) parent)->buf.len;
				uint64_t meta = ((struct buffer_node *) parent)->buf.meta;
				hr = COMPARE_ASC ((struct avl_node *) node, parent);

				if (hr == -1)
				{
					dup = parent;
					break;
				}
				else if (hr == 1)
				{
					link = &(parent->left);
				}
				else if (hr == 2)
				{

					dup = parent;
					break;
				}
				else if (hr == 3)
				{

					dup = parent;
					break;
				}
				else
				{
					link = &(parent->right);
				}
			}
			if (dup == NULL)
			{

				if (!loopback_ip_bufs->root->node)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_bufs->root->head) == 1)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_bufs->packet_count++;
				loopback_ip_bufs->buf_len += loopback_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_bufs->head->next == NULL)
			{

				loopback_ip_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				loopback_ip_bufs->head->next->buf.buf =
					malloc (loopback_ip_payload_length);
				loopback_ip_bufs->head->next->next = NULL;
				memcpy (loopback_ip_bufs->head->next->buf.buf,
					loopback_ip_payload, loopback_ip_payload_length);
				loopback_ip_bufs->head->next->buf.len =
					loopback_ip_payload_length;
				loopback_ip_bufs->buf_len = loopback_ip_payload_length;
				loopback_ip_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_bufs->packet_count >= loopback_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_buf_length =
								((struct buffer_node *) parent)->buf.len;
							uint64_t meta =
								((struct buffer_node *) parent)->buf.meta;
							hr = COMPARE_ASC ((struct avl_node *) node, parent);

							if (hr == -1)
							{
								dup = parent;
								break;
							}
							else if (hr == 1)
							{
								link = &(parent->left);
							}
							else if (hr == 2)
							{

								dup = parent;
								break;
							}
							else if (hr == 3)
							{

								dup = parent;
								break;
							}
							else
							{
								link = &(parent->right);
							}
						}
						if (dup == NULL)
						{
							if (!loopback_ip_bufs->root->node)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_bufs->root->head) == 1)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (loopback_ip_payload_length);
					memcpy (node->buf.buf, loopback_ip_payload,
						loopback_ip_payload_length);
					node->buf.len = loopback_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(loopback_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_buf_length =
							((struct buffer_node *) parent)->buf.len;
						uint64_t meta =
							((struct buffer_node *) parent)->buf.meta;
						hr = COMPARE_ASC ((struct avl_node *) node, parent);
						if (hr == -1)
						{
							dup = parent;
							break;
						}
						else if (hr == 1)
						{
							link = &(parent->left);
						}
						else if (hr == 2)
						{
							dup = parent;
							break;
						}
						else if (hr == 3)
						{
							dup = parent;
							break;
						}
						else
						{
							link = &(parent->right);
						}
					}
					if (dup == NULL)
					{

						if (!loopback_ip_bufs->root->node)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_bufs->root->head) == 1)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_bufs->packet_count++;
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = loopback_ip_bufs->head;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						loopback_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (loopback_ip_payload_length);
							pre_buf->next->buf.len = loopback_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
								loopback_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_bufs->buf_len +=
								loopback_ip_payload_length;
							loopback_ip_bufs->packet_count++;
							inserted = 1;
							break;
						}
						else if (hr == -1)
						{
							inserted = 1;
							break;
						}
						else if (hr == 2)
						{

							inserted = 1;
							break;
						}
						else if (hr == 3)
						{

							inserted = 1;
							break;
						}
						else
						{
							pre_buf = cur_buf;
							cur_buf = cur_buf->next;
						}
					}
					if (!inserted)
					{

						pre_buf->next = malloc (sizeof (struct buf_list));
						pre_buf->next->buf.buf =
							malloc (loopback_ip_payload_length);
						pre_buf->next->buf.len = loopback_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
							loopback_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;
						loopback_ip_bufs->packet_count++;
					}
				}
			}
		} return;
	}
	return;
}

void loopback_ip_buffering ()
{
	if ((loopback_ip_ip_hdr->more_frag && !loopback_ip_ip_hdr->dont_frag))
	{
		loopback_ip_transition_bitmap->still_has_buffer = 1;
		loopback_ip_instance->state = loopback_ip_buffering;
		loopback_ip_bufs = loopback_ip_instance->bufs;
		if (loopback_ip_bufs->is_tree
			|| loopback_ip_bufs->packet_count > loopback_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (loopback_ip_payload_length);
			memcpy (node->buf.buf, loopback_ip_payload,
				loopback_ip_payload_length);
			node->buf.len = loopback_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(loopback_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_buf_length =
					((struct buffer_node *) parent)->buf.len;
				uint64_t meta = ((struct buffer_node *) parent)->buf.meta;
				hr = COMPARE_ASC ((struct avl_node *) node, parent);

				if (hr == -1)
				{
					dup = parent;
					break;
				}
				else if (hr == 1)
				{
					link = &(parent->left);
				}
				else if (hr == 2)
				{

					dup = parent;
					break;
				}
				else if (hr == 3)
				{

					dup = parent;
					break;
				}
				else
				{
					link = &(parent->right);
				}
			}
			if (dup == NULL)
			{

				if (!loopback_ip_bufs->root->node)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_bufs->root->head) == 1)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_bufs->packet_count++;
				loopback_ip_bufs->buf_len += loopback_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_bufs->head->next == NULL)
			{

				loopback_ip_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				loopback_ip_bufs->head->next->buf.buf =
					malloc (loopback_ip_payload_length);
				loopback_ip_bufs->head->next->next = NULL;
				memcpy (loopback_ip_bufs->head->next->buf.buf,
					loopback_ip_payload, loopback_ip_payload_length);
				loopback_ip_bufs->head->next->buf.len =
					loopback_ip_payload_length;
				loopback_ip_bufs->buf_len = loopback_ip_payload_length;
				loopback_ip_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_bufs->packet_count >= loopback_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_buf_length =
								((struct buffer_node *) parent)->buf.len;
							uint64_t meta =
								((struct buffer_node *) parent)->buf.meta;
							hr = COMPARE_ASC ((struct avl_node *) node, parent);

							if (hr == -1)
							{
								dup = parent;
								break;
							}
							else if (hr == 1)
							{
								link = &(parent->left);
							}
							else if (hr == 2)
							{

								dup = parent;
								break;
							}
							else if (hr == 3)
							{

								dup = parent;
								break;
							}
							else
							{
								link = &(parent->right);
							}
						}
						if (dup == NULL)
						{
							if (!loopback_ip_bufs->root->node)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_bufs->root->head) == 1)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (loopback_ip_payload_length);
					memcpy (node->buf.buf, loopback_ip_payload,
						loopback_ip_payload_length);
					node->buf.len = loopback_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(loopback_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_buf_length =
							((struct buffer_node *) parent)->buf.len;
						uint64_t meta =
							((struct buffer_node *) parent)->buf.meta;
						hr = COMPARE_ASC ((struct avl_node *) node, parent);
						if (hr == -1)
						{
							dup = parent;
							break;
						}
						else if (hr == 1)
						{
							link = &(parent->left);
						}
						else if (hr == 2)
						{
							dup = parent;
							break;
						}
						else if (hr == 3)
						{
							dup = parent;
							break;
						}
						else
						{
							link = &(parent->right);
						}
					}
					if (dup == NULL)
					{

						if (!loopback_ip_bufs->root->node)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_bufs->root->head) == 1)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_bufs->packet_count++;
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = loopback_ip_bufs->head;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						loopback_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (loopback_ip_payload_length);
							pre_buf->next->buf.len = loopback_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
								loopback_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_bufs->buf_len +=
								loopback_ip_payload_length;
							loopback_ip_bufs->packet_count++;
							inserted = 1;
							break;
						}
						else if (hr == -1)
						{
							inserted = 1;
							break;
						}
						else if (hr == 2)
						{

							inserted = 1;
							break;
						}
						else if (hr == 3)
						{

							inserted = 1;
							break;
						}
						else
						{
							pre_buf = cur_buf;
							cur_buf = cur_buf->next;
						}
					}
					if (!inserted)
					{

						pre_buf->next = malloc (sizeof (struct buf_list));
						pre_buf->next->buf.buf =
							malloc (loopback_ip_payload_length);
						pre_buf->next->buf.len = loopback_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
							loopback_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;
						loopback_ip_bufs->packet_count++;
					}
				}
			}
		} return;
	}
	if ((!loopback_ip_ip_hdr->more_frag && !loopback_ip_ip_hdr->dont_frag))
	{
		loopback_ip_transition_bitmap->last_buffer = 1;
		loopback_ip_instance->state = loopback_ip_direct_dump;
		loopback_ip_bufs = loopback_ip_instance->bufs;
		if (loopback_ip_bufs->is_tree
			|| loopback_ip_bufs->packet_count > loopback_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (loopback_ip_payload_length);
			memcpy (node->buf.buf, loopback_ip_payload,
				loopback_ip_payload_length);
			node->buf.len = loopback_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(loopback_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_buf_length =
					((struct buffer_node *) parent)->buf.len;
				uint64_t meta = ((struct buffer_node *) parent)->buf.meta;
				hr = COMPARE_ASC ((struct avl_node *) node, parent);

				if (hr == -1)
				{
					dup = parent;
					break;
				}
				else if (hr == 1)
				{
					link = &(parent->left);
				}
				else if (hr == 2)
				{

					dup = parent;
					break;
				}
				else if (hr == 3)
				{

					dup = parent;
					break;
				}
				else
				{
					link = &(parent->right);
				}
			}
			if (dup == NULL)
			{

				if (!loopback_ip_bufs->root->node)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_bufs->root->head) == 1)
					loopback_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_bufs->packet_count++;
				loopback_ip_bufs->buf_len += loopback_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_bufs->head->next == NULL)
			{

				loopback_ip_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				loopback_ip_bufs->head->next->buf.buf =
					malloc (loopback_ip_payload_length);
				loopback_ip_bufs->head->next->next = NULL;
				memcpy (loopback_ip_bufs->head->next->buf.buf,
					loopback_ip_payload, loopback_ip_payload_length);
				loopback_ip_bufs->head->next->buf.len =
					loopback_ip_payload_length;
				loopback_ip_bufs->buf_len = loopback_ip_payload_length;
				loopback_ip_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_bufs->packet_count >= loopback_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_buf_length =
								((struct buffer_node *) parent)->buf.len;
							uint64_t meta =
								((struct buffer_node *) parent)->buf.meta;
							hr = COMPARE_ASC ((struct avl_node *) node, parent);

							if (hr == -1)
							{
								dup = parent;
								break;
							}
							else if (hr == 1)
							{
								link = &(parent->left);
							}
							else if (hr == 2)
							{

								dup = parent;
								break;
							}
							else if (hr == 3)
							{

								dup = parent;
								break;
							}
							else
							{
								link = &(parent->right);
							}
						}
						if (dup == NULL)
						{
							if (!loopback_ip_bufs->root->node)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_bufs->root->head) == 1)
								loopback_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (loopback_ip_payload_length);
					memcpy (node->buf.buf, loopback_ip_payload,
						loopback_ip_payload_length);
					node->buf.len = loopback_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(loopback_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_buf_length =
							((struct buffer_node *) parent)->buf.len;
						uint64_t meta =
							((struct buffer_node *) parent)->buf.meta;
						hr = COMPARE_ASC ((struct avl_node *) node, parent);
						if (hr == -1)
						{
							dup = parent;
							break;
						}
						else if (hr == 1)
						{
							link = &(parent->left);
						}
						else if (hr == 2)
						{
							dup = parent;
							break;
						}
						else if (hr == 3)
						{
							dup = parent;
							break;
						}
						else
						{
							link = &(parent->right);
						}
					}
					if (dup == NULL)
					{

						if (!loopback_ip_bufs->root->node)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_bufs->root->head) == 1)
							loopback_ip_bufs->root->head =
								(struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_bufs->packet_count++;
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = loopback_ip_bufs->head;
					struct buf_list *cur_buf = loopback_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						loopback_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (loopback_ip_payload_length);
							pre_buf->next->buf.len = loopback_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
								loopback_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_bufs->buf_len +=
								loopback_ip_payload_length;
							loopback_ip_bufs->packet_count++;
							inserted = 1;
							break;
						}
						else if (hr == -1)
						{
							inserted = 1;
							break;
						}
						else if (hr == 2)
						{

							inserted = 1;
							break;
						}
						else if (hr == 3)
						{

							inserted = 1;
							break;
						}
						else
						{
							pre_buf = cur_buf;
							cur_buf = cur_buf->next;
						}
					}
					if (!inserted)
					{

						pre_buf->next = malloc (sizeof (struct buf_list));
						pre_buf->next->buf.buf =
							malloc (loopback_ip_payload_length);
						pre_buf->next->buf.len = loopback_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, loopback_ip_payload,
							loopback_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						loopback_ip_bufs->buf_len += loopback_ip_payload_length;
						loopback_ip_bufs->packet_count++;
					}
				}
			}
		} loopback_ip_bufs = loopback_ip_instance->bufs;
		if (1)
		{
			if (loopback_ip_bufs->is_tree
				|| loopback_ip_bufs->packet_count > loopback_ip_THRESHOLD)
			{
				loopback_ip_buf = malloc (loopback_ip_bufs->buf_len);
				loopback_ip_buf_length = loopback_ip_bufs->buf_len;
				int offset = 0;
				struct avl_node *stack[loopback_ip_bufs->packet_count];
				int stack_ptr = 0;
				struct avl_node *cur_ptr = loopback_ip_bufs->root->node;
				struct avl_node *tmp;
				while (loopback_ip_bufs->packet_count > 0)
				{
					if (cur_ptr)
					{
						stack[stack_ptr++] = cur_ptr;
						cur_ptr = cur_ptr->left;
					}
					else
					{
						cur_ptr = stack[--stack_ptr];
						memcpy (loopback_ip_buf + offset,
							((struct buffer_node *) cur_ptr)->buf.buf,
							((struct buffer_node *) cur_ptr)->buf.len);
						offset += ((struct buffer_node *) cur_ptr)->buf.len;
						free (((struct buffer_node *) cur_ptr)->buf.buf);
						tmp = cur_ptr;
						cur_ptr = cur_ptr->right;
						free (tmp);
						loopback_ip_bufs->packet_count--;
					}
				}

				loopback_ip_bufs->buf_len = 0;
				loopback_ip_bufs->is_tree = 0;
				loopback_ip_bufs->root->node = NULL;
				loopback_ip_bufs->root->head = NULL;
				loopback_ip_has_buf = 1;
			}
			else
			{
				loopback_ip_buf = malloc (loopback_ip_bufs->buf_len);
				loopback_ip_buf_length = loopback_ip_bufs->buf_len;
				int offset = 0;
				struct buf_list *cur_buf;
				struct buf_list *pre_buf;
				for (cur_buf = loopback_ip_bufs->head->next; cur_buf != NULL;)
				{
					memcpy (loopback_ip_buf + offset, cur_buf->buf.buf,
						cur_buf->buf.len);
					offset += cur_buf->buf.len;
					pre_buf = cur_buf;
					cur_buf = cur_buf->next;
					free (pre_buf->buf.buf);
					free (pre_buf);
				}

				loopback_ip_bufs->buf_len = 0;
				loopback_ip_bufs->packet_count = 0;
				loopback_ip_bufs->head->next = NULL;
				loopback_ip_has_buf = 1;
			}
		}
		return;
	}
	return;
}

void loopback_ip_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	loopback_ip_rubik_bitmap->loopback_ip_ip_hdr = 1;
	loopback_ip_ip_hdr = (struct loopback_ip_ip_hdr_t *) (payload + cur_pos);
	cur_pos += 20;
	loopback_ip_payload_length -= cur_pos;
	loopback_ip_payload += cur_pos;
	loopback_ip_select->src_src_addr = loopback_ip_ip_hdr->src_addr;
	loopback_ip_select->dst_dst_addr = loopback_ip_ip_hdr->dst_addr;
}

void loopback_ip_selector (struct timeval *now)
{
	if (! !loopback_ip_ip_hdr->dont_frag)
	{
		loopback_ip_instance = loopback_ip_fake_instance;
		loopback_ip_instance->state = loopback_ip_direct_dump;
		loopback_ip_instance->loopback_ip_data = NULL;
		loopback_ip_instance->bufs = NULL;
		pure_ip_temp_data->frag_offset =
			(((loopback_ip_ip_hdr->frag_offset_upper << 8) +
				loopback_ip_ip_hdr->frag_offset_lower) * 8);
		pure_ip_temp_data->buf_len = 0;
		return;
	}
	uint32_t hash = loopback_ip_hash (loopback_ip_select);
	loopback_ip_instance =
		tommy_hashdyn_search (&loopback_ip_hashtable, loopback_ip_compare,
		loopback_ip_select, hash);
	if (!loopback_ip_instance)
	{
		loopback_ip_instance =
			(struct loopback_ip_instance_t *) malloc (sizeof (struct
				loopback_ip_instance_t));
		memset (loopback_ip_instance, 0, sizeof (struct loopback_ip_select_t));
		loopback_ip_data =
			(loopback_ip_data_t *) malloc (sizeof (loopback_ip_data_t));
		loopback_ip_data->buf_len = 0;
		loopback_ip_instance->loopback_ip_select = *loopback_ip_select;
		loopback_ip_instance->loopback_ip_data = loopback_ip_data;
		loopback_ip_instance->state = loopback_ip_direct_dump;
		loopback_ip_instance->rec_ptr =
			timer_update (&loopback_ip_list, loopback_ip_instance, NULL, now);
		init_buf_list (&loopback_ip_instance->bufs);
		hash = loopback_ip_hash (loopback_ip_select);
		tommy_hashdyn_insert (&loopback_ip_hashtable,
			&loopback_ip_instance->node, loopback_ip_instance, hash);
	}
	else
	{
		loopback_ip_data = loopback_ip_instance->loopback_ip_data;
		loopback_ip_instance->rec_ptr =
			timer_update (&loopback_ip_list, loopback_ip_instance,
			loopback_ip_instance->rec_ptr, now);
	}
	pure_ip_temp_data->frag_offset =
		(((loopback_ip_ip_hdr->frag_offset_upper << 8) +
			loopback_ip_ip_hdr->frag_offset_lower) * 8);
	pure_ip_temp_data->buf_len = 0;
}

void loopback_ip_udp_parse (u_char *, uint32_t, struct timeval *);
void loopback_ip_parse (u_char * payload, uint32_t length, struct timeval *now)
{
	printf ("this is ip layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	loopback_ip_payload = payload;
	loopback_ip_payload_length = length;
	loopback_ip_data_assignment (payload);
	loopback_ip_selector (now);
	loopback_ip_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&loopback_ip_list, &loopback_ip_gap,
			&loopback_ip_hashtable, offsetof (struct loopback_ip_instance_t,
				node), loopback_ip_free, now);
		ts = int_now;
	}
	loopback_ip_udp_parse (loopback_ip_buf, loopback_ip_buf_length, now);
	memset (loopback_ip_rubik_bitmap, 0,
		sizeof (struct loopback_ip_rubik_bitmap_t));
	memset (loopback_ip_transition_bitmap, 0,
		sizeof (struct loopback_ip_transition_bitmap_t));
	if (loopback_ip_has_buf)
	{
		free (loopback_ip_buf);
		loopback_ip_has_buf = 0;
	}
}
