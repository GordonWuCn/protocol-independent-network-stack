#include "eth_ip_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
#define eth_ip_THRESHOLD 10
struct eth_ip_instance_t *eth_ip_instance;
struct eth_ip_select_t *eth_ip_select;
struct eth_ip_instance_t *eth_ip_fake_instance;
tommy_hashdyn eth_ip_hashtable;
struct timer eth_ip_list;
struct timeval eth_ip_gap;
struct eth_ip_ip_hdr_t *eth_ip_ip_hdr;
eth_ip_data_t *eth_ip_data;
char eth_ip_has_buf = 0;
u_char *eth_ip_buf;
int eth_ip_buf_length;
u_char *eth_ip_payload;
int eth_ip_payload_length;
struct eth_ip_rubik_bitmap_t *eth_ip_rubik_bitmap;
struct eth_ip_transition_bitmap_t *eth_ip_transition_bitmap;
struct buf_queue *eth_ip_bufs;
void eth_ip_init ()
{
	tommy_hashdyn_init (&eth_ip_hashtable);
	eth_ip_gap.tv_sec = 10;
	eth_ip_gap.tv_usec = 0;
	eth_ip_list.head = NULL;
	eth_ip_list.tail = NULL;
	eth_ip_instance = NULL;
	eth_ip_fake_instance = malloc (sizeof (struct eth_ip_instance_t));
	eth_ip_select = malloc (sizeof (struct eth_ip_select_t));
	memset (eth_ip_select, 0, sizeof (struct eth_ip_select_t));
	eth_ip_rubik_bitmap = malloc (sizeof (struct eth_ip_rubik_bitmap_t));
	eth_ip_transition_bitmap =
		malloc (sizeof (struct eth_ip_transition_bitmap_t));
	memset (eth_ip_rubik_bitmap, 0, sizeof (struct eth_ip_rubik_bitmap_t));
	memset (eth_ip_transition_bitmap, 0,
		sizeof (struct eth_ip_transition_bitmap_t));
}

char eth_ip_has_hole (uint64_t meta, int length, struct buf_queue *buf)
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

uint32_t eth_ip_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_destroy ()
{
	free (eth_ip_instance->eth_ip_data);
	free_buf_list (eth_ip_instance->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_hashtable, &eth_ip_instance->node);
	deregister_timer (&eth_ip_list, eth_ip_instance->rec_ptr);
	free (eth_ip_instance);
}

void eth_ip_free (void *inst)
{
	free (((struct eth_ip_instance_t *) inst)->eth_ip_data);
	free_buf_list (((struct eth_ip_instance_t *) inst)->bufs);
}

static void eth_ip_direct_dump (void);
static void eth_ip_buffering (void);
void eth_ip_direct_dump ()
{
	if ((eth_ip_ip_hdr->dont_frag || (!eth_ip_ip_hdr->dont_frag
				&& !eth_ip_ip_hdr->more_frag)))
	{
		eth_ip_transition_bitmap->no_buffer = 1;
		eth_ip_instance->state = eth_ip_direct_dump;
		eth_ip_buf = eth_ip_payload;
		eth_ip_buf_length = eth_ip_payload_length;
		return;
	}
	if ((eth_ip_ip_hdr->more_frag && !eth_ip_ip_hdr->dont_frag))
	{
		eth_ip_transition_bitmap->has_buffer = 1;
		eth_ip_instance->state = eth_ip_buffering;
		eth_ip_bufs = eth_ip_instance->bufs;
		if (eth_ip_bufs->is_tree
			|| eth_ip_bufs->packet_count > eth_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (eth_ip_payload_length);
			memcpy (node->buf.buf, eth_ip_payload, eth_ip_payload_length);
			node->buf.len = eth_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(eth_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				eth_ip_buf_length = ((struct buffer_node *) parent)->buf.len;
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

				if (!eth_ip_bufs->root->node)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						eth_ip_bufs->root->head) == 1)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					eth_ip_bufs->root);
			}
			if (!dup)
			{
				eth_ip_bufs->packet_count++;
				eth_ip_bufs->buf_len += eth_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (eth_ip_bufs->head->next == NULL)
			{

				eth_ip_bufs->head->next = malloc (sizeof (struct buf_list));
				eth_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				eth_ip_bufs->head->next->buf.buf =
					malloc (eth_ip_payload_length);
				eth_ip_bufs->head->next->next = NULL;
				memcpy (eth_ip_bufs->head->next->buf.buf, eth_ip_payload,
					eth_ip_payload_length);
				eth_ip_bufs->head->next->buf.len = eth_ip_payload_length;
				eth_ip_bufs->buf_len = eth_ip_payload_length;
				eth_ip_bufs->packet_count++;
			}
			else
			{
				if (eth_ip_bufs->packet_count >= eth_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link = &(eth_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							eth_ip_buf_length =
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
							if (!eth_ip_bufs->root->node)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									eth_ip_bufs->root->head) == 1)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								eth_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					eth_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (eth_ip_payload_length);
					memcpy (node->buf.buf, eth_ip_payload,
						eth_ip_payload_length);
					node->buf.len = eth_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(eth_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						eth_ip_buf_length =
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

						if (!eth_ip_bufs->root->node)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								eth_ip_bufs->root->head) == 1)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							eth_ip_bufs->root);
					}
					if (!dup)
					{
						eth_ip_bufs->packet_count++;
						eth_ip_bufs->buf_len += eth_ip_payload_length;

					}
					else
					{
						free (node);
					}
					eth_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = eth_ip_bufs->head;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						eth_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (eth_ip_payload_length);
							pre_buf->next->buf.len = eth_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, eth_ip_payload,
								eth_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							eth_ip_bufs->buf_len += eth_ip_payload_length;
							eth_ip_bufs->packet_count++;
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
						pre_buf->next->buf.buf = malloc (eth_ip_payload_length);
						pre_buf->next->buf.len = eth_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, eth_ip_payload,
							eth_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						eth_ip_bufs->buf_len += eth_ip_payload_length;
						eth_ip_bufs->packet_count++;
					}
				}
			}
		} return;
	}
	return;
}

void eth_ip_buffering ()
{
	if ((eth_ip_ip_hdr->more_frag && !eth_ip_ip_hdr->dont_frag))
	{
		eth_ip_transition_bitmap->still_has_buffer = 1;
		eth_ip_instance->state = eth_ip_buffering;
		eth_ip_bufs = eth_ip_instance->bufs;
		if (eth_ip_bufs->is_tree
			|| eth_ip_bufs->packet_count > eth_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (eth_ip_payload_length);
			memcpy (node->buf.buf, eth_ip_payload, eth_ip_payload_length);
			node->buf.len = eth_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(eth_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				eth_ip_buf_length = ((struct buffer_node *) parent)->buf.len;
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

				if (!eth_ip_bufs->root->node)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						eth_ip_bufs->root->head) == 1)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					eth_ip_bufs->root);
			}
			if (!dup)
			{
				eth_ip_bufs->packet_count++;
				eth_ip_bufs->buf_len += eth_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (eth_ip_bufs->head->next == NULL)
			{

				eth_ip_bufs->head->next = malloc (sizeof (struct buf_list));
				eth_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				eth_ip_bufs->head->next->buf.buf =
					malloc (eth_ip_payload_length);
				eth_ip_bufs->head->next->next = NULL;
				memcpy (eth_ip_bufs->head->next->buf.buf, eth_ip_payload,
					eth_ip_payload_length);
				eth_ip_bufs->head->next->buf.len = eth_ip_payload_length;
				eth_ip_bufs->buf_len = eth_ip_payload_length;
				eth_ip_bufs->packet_count++;
			}
			else
			{
				if (eth_ip_bufs->packet_count >= eth_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link = &(eth_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							eth_ip_buf_length =
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
							if (!eth_ip_bufs->root->node)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									eth_ip_bufs->root->head) == 1)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								eth_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					eth_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (eth_ip_payload_length);
					memcpy (node->buf.buf, eth_ip_payload,
						eth_ip_payload_length);
					node->buf.len = eth_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(eth_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						eth_ip_buf_length =
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

						if (!eth_ip_bufs->root->node)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								eth_ip_bufs->root->head) == 1)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							eth_ip_bufs->root);
					}
					if (!dup)
					{
						eth_ip_bufs->packet_count++;
						eth_ip_bufs->buf_len += eth_ip_payload_length;

					}
					else
					{
						free (node);
					}
					eth_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = eth_ip_bufs->head;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						eth_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (eth_ip_payload_length);
							pre_buf->next->buf.len = eth_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, eth_ip_payload,
								eth_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							eth_ip_bufs->buf_len += eth_ip_payload_length;
							eth_ip_bufs->packet_count++;
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
						pre_buf->next->buf.buf = malloc (eth_ip_payload_length);
						pre_buf->next->buf.len = eth_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, eth_ip_payload,
							eth_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						eth_ip_bufs->buf_len += eth_ip_payload_length;
						eth_ip_bufs->packet_count++;
					}
				}
			}
		} return;
	}
	if ((!eth_ip_ip_hdr->more_frag && !eth_ip_ip_hdr->dont_frag))
	{
		eth_ip_transition_bitmap->last_buffer = 1;
		eth_ip_instance->state = eth_ip_direct_dump;
		eth_ip_bufs = eth_ip_instance->bufs;
		if (eth_ip_bufs->is_tree
			|| eth_ip_bufs->packet_count > eth_ip_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf = malloc (eth_ip_payload_length);
			memcpy (node->buf.buf, eth_ip_payload, eth_ip_payload_length);
			node->buf.len = eth_ip_payload_length;
			node->buf.meta = pure_ip_temp_data->frag_offset;	// meta assignment
			struct avl_node **link = &(eth_ip_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				eth_ip_buf_length = ((struct buffer_node *) parent)->buf.len;
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

				if (!eth_ip_bufs->root->node)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						eth_ip_bufs->root->head) == 1)
					eth_ip_bufs->root->head = (struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					eth_ip_bufs->root);
			}
			if (!dup)
			{
				eth_ip_bufs->packet_count++;
				eth_ip_bufs->buf_len += eth_ip_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (eth_ip_bufs->head->next == NULL)
			{

				eth_ip_bufs->head->next = malloc (sizeof (struct buf_list));
				eth_ip_bufs->head->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data_assignment here
				eth_ip_bufs->head->next->buf.buf =
					malloc (eth_ip_payload_length);
				eth_ip_bufs->head->next->next = NULL;
				memcpy (eth_ip_bufs->head->next->buf.buf, eth_ip_payload,
					eth_ip_payload_length);
				eth_ip_bufs->head->next->buf.len = eth_ip_payload_length;
				eth_ip_bufs->buf_len = eth_ip_payload_length;
				eth_ip_bufs->packet_count++;
			}
			else
			{
				if (eth_ip_bufs->packet_count >= eth_ip_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link = &(eth_ip_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							eth_ip_buf_length =
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
							if (!eth_ip_bufs->root->node)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									eth_ip_bufs->root->head) == 1)
								eth_ip_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								eth_ip_bufs->root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					eth_ip_bufs->head->next = NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf = malloc (eth_ip_payload_length);
					memcpy (node->buf.buf, eth_ip_payload,
						eth_ip_payload_length);
					node->buf.len = eth_ip_payload_length;
					node->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
					struct avl_node **link = &(eth_ip_bufs->root->node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						eth_ip_buf_length =
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

						if (!eth_ip_bufs->root->node)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								eth_ip_bufs->root->head) == 1)
							eth_ip_bufs->root->head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							eth_ip_bufs->root);
					}
					if (!dup)
					{
						eth_ip_bufs->packet_count++;
						eth_ip_bufs->buf_len += eth_ip_payload_length;

					}
					else
					{
						free (node);
					}
					eth_ip_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf = eth_ip_bufs->head;
					struct buf_list *cur_buf = eth_ip_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							pure_ip_temp_data->frag_offset);
						eth_ip_buf_length = cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc (eth_ip_payload_length);
							pre_buf->next->buf.len = eth_ip_payload_length;
							memcpy (pre_buf->next->buf.buf, eth_ip_payload,
								eth_ip_payload_length);
							pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							eth_ip_bufs->buf_len += eth_ip_payload_length;
							eth_ip_bufs->packet_count++;
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
						pre_buf->next->buf.buf = malloc (eth_ip_payload_length);
						pre_buf->next->buf.len = eth_ip_payload_length;
						memcpy (pre_buf->next->buf.buf, eth_ip_payload,
							eth_ip_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = pure_ip_temp_data->frag_offset;	//meta_data assignment here
						eth_ip_bufs->buf_len += eth_ip_payload_length;
						eth_ip_bufs->packet_count++;
					}
				}
			}
		} eth_ip_bufs = eth_ip_instance->bufs;
		if (1)
		{
			if (eth_ip_bufs->is_tree
				|| eth_ip_bufs->packet_count > eth_ip_THRESHOLD)
			{
				eth_ip_buf = malloc (eth_ip_bufs->buf_len);
				eth_ip_buf_length = eth_ip_bufs->buf_len;
				int offset = 0;
				struct avl_node *stack[eth_ip_bufs->packet_count];
				int stack_ptr = 0;
				struct avl_node *cur_ptr = eth_ip_bufs->root->node;
				struct avl_node *tmp;
				while (eth_ip_bufs->packet_count > 0)
				{
					if (cur_ptr)
					{
						stack[stack_ptr++] = cur_ptr;
						cur_ptr = cur_ptr->left;
					}
					else
					{
						cur_ptr = stack[--stack_ptr];
						memcpy (eth_ip_buf + offset,
							((struct buffer_node *) cur_ptr)->buf.buf,
							((struct buffer_node *) cur_ptr)->buf.len);
						offset += ((struct buffer_node *) cur_ptr)->buf.len;
						free (((struct buffer_node *) cur_ptr)->buf.buf);
						tmp = cur_ptr;
						cur_ptr = cur_ptr->right;
						free (tmp);
						eth_ip_bufs->packet_count--;
					}
				}

				eth_ip_bufs->buf_len = 0;
				eth_ip_bufs->is_tree = 0;
				eth_ip_bufs->root->node = NULL;
				eth_ip_bufs->root->head = NULL;
				eth_ip_has_buf = 1;
			}
			else
			{
				eth_ip_buf = malloc (eth_ip_bufs->buf_len);
				eth_ip_buf_length = eth_ip_bufs->buf_len;
				int offset = 0;
				struct buf_list *cur_buf;
				struct buf_list *pre_buf;
				for (cur_buf = eth_ip_bufs->head->next; cur_buf != NULL;)
				{
					memcpy (eth_ip_buf + offset, cur_buf->buf.buf,
						cur_buf->buf.len);
					offset += cur_buf->buf.len;
					pre_buf = cur_buf;
					cur_buf = cur_buf->next;
					free (pre_buf->buf.buf);
					free (pre_buf);
				}

				eth_ip_bufs->buf_len = 0;
				eth_ip_bufs->packet_count = 0;
				eth_ip_bufs->head->next = NULL;
				eth_ip_has_buf = 1;
			}
		}
		return;
	}
	return;
}

void eth_ip_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_ip_rubik_bitmap->eth_ip_ip_hdr = 1;
	eth_ip_ip_hdr = (struct eth_ip_ip_hdr_t *) (payload + cur_pos);
	cur_pos += 20;
	eth_ip_payload_length -= cur_pos;
	eth_ip_payload += cur_pos;
	eth_ip_select->src_src_addr = eth_ip_ip_hdr->src_addr;
	eth_ip_select->dst_dst_addr = eth_ip_ip_hdr->dst_addr;
}

void eth_ip_selector (struct timeval *now)
{
	if (! !eth_ip_ip_hdr->dont_frag)
	{
		eth_ip_instance = eth_ip_fake_instance;
		eth_ip_instance->state = eth_ip_direct_dump;
		eth_ip_instance->eth_ip_data = NULL;
		eth_ip_instance->bufs = NULL;
		pure_ip_temp_data->frag_offset =
			(((eth_ip_ip_hdr->frag_offset_upper << 8) +
				eth_ip_ip_hdr->frag_offset_lower) * 8);
		pure_ip_temp_data->buf_len = 0;
		return;
	}
	uint32_t hash = eth_ip_hash (eth_ip_select);
	eth_ip_instance =
		tommy_hashdyn_search (&eth_ip_hashtable, eth_ip_compare, eth_ip_select,
		hash);
	if (!eth_ip_instance)
	{
		eth_ip_instance =
			(struct eth_ip_instance_t *) malloc (sizeof (struct
				eth_ip_instance_t));
		memset (eth_ip_instance, 0, sizeof (struct eth_ip_select_t));
		eth_ip_data = (eth_ip_data_t *) malloc (sizeof (eth_ip_data_t));
		eth_ip_data->buf_len = 0;
		eth_ip_instance->eth_ip_select = *eth_ip_select;
		eth_ip_instance->eth_ip_data = eth_ip_data;
		eth_ip_instance->state = eth_ip_direct_dump;
		eth_ip_instance->rec_ptr =
			timer_update (&eth_ip_list, eth_ip_instance, NULL, now);
		init_buf_list (&eth_ip_instance->bufs);
		hash = eth_ip_hash (eth_ip_select);
		tommy_hashdyn_insert (&eth_ip_hashtable, &eth_ip_instance->node,
			eth_ip_instance, hash);
	}
	else
	{
		eth_ip_data = eth_ip_instance->eth_ip_data;
		eth_ip_instance->rec_ptr =
			timer_update (&eth_ip_list, eth_ip_instance,
			eth_ip_instance->rec_ptr, now);
	}
	pure_ip_temp_data->frag_offset =
		(((eth_ip_ip_hdr->frag_offset_upper << 8) +
			eth_ip_ip_hdr->frag_offset_lower) * 8);
	pure_ip_temp_data->buf_len = 0;
}

void eth_ip_tcp_parse (u_char *, uint32_t, struct timeval *);
void eth_ip_gre_parse (u_char *, uint32_t, struct timeval *);
void eth_ip_parse (u_char * payload, uint32_t length, struct timeval *now)
{
	printf ("this is ip layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_payload = payload;
	eth_ip_payload_length = length;
	eth_ip_data_assignment (payload);
	eth_ip_selector (now);
	eth_ip_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_list, &eth_ip_gap,
			&eth_ip_hashtable, offsetof (struct eth_ip_instance_t, node),
			eth_ip_free, now);
		ts = int_now;
	}
	if (((eth_ip_transition_bitmap->last_buffer
				|| eth_ip_transition_bitmap->no_buffer)
			&& (eth_ip_ip_hdr->protocol == 6)))
	{
		eth_ip_tcp_parse (eth_ip_buf, eth_ip_buf_length, now);
	}
	if (((eth_ip_transition_bitmap->last_buffer
				|| eth_ip_transition_bitmap->no_buffer)
			&& (eth_ip_ip_hdr->protocol == 47)))
	{
		eth_ip_gre_parse (eth_ip_buf, eth_ip_buf_length, now);
	}
	memset (eth_ip_rubik_bitmap, 0, sizeof (struct eth_ip_rubik_bitmap_t));
	memset (eth_ip_transition_bitmap, 0,
		sizeof (struct eth_ip_transition_bitmap_t));
	if (eth_ip_has_buf)
	{
		free (eth_ip_buf);
		eth_ip_has_buf = 0;
	}
}
