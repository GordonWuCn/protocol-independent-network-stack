#include "eth_ip_gre_ppp_ip_tcp_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
#define eth_ip_gre_ppp_ip_tcp_THRESHOLD 10
struct eth_ip_gre_ppp_ip_tcp_instance_t *eth_ip_gre_ppp_ip_tcp_instance;
struct eth_ip_gre_ppp_ip_tcp_instance_t *eth_ip_gre_ppp_ip_tcp_instance_reverse;
struct eth_ip_gre_ppp_ip_tcp_select_t *eth_ip_gre_ppp_ip_tcp_select;
struct eth_ip_gre_ppp_ip_tcp_select_t *eth_ip_gre_ppp_ip_tcp_select_reverse;
struct eth_ip_gre_ppp_ip_tcp_instance_t *eth_ip_gre_ppp_ip_tcp_fake_instance;
struct eth_ip_gre_ppp_ip_tcp_instance_t
	*eth_ip_gre_ppp_ip_tcp_fake_instance_reverse;
tommy_hashdyn eth_ip_gre_ppp_ip_tcp_hashtable;
struct timer eth_ip_gre_ppp_ip_tcp_list;
struct timeval eth_ip_gre_ppp_ip_tcp_gap;
struct eth_ip_gre_ppp_ip_tcp_tcp_hdr_t *eth_ip_gre_ppp_ip_tcp_tcp_hdr;
struct eth_ip_gre_ppp_ip_tcp_tcp_eol_t *eth_ip_gre_ppp_ip_tcp_tcp_eol;
struct eth_ip_gre_ppp_ip_tcp_tcp_nop_t *eth_ip_gre_ppp_ip_tcp_tcp_nop;
struct eth_ip_gre_ppp_ip_tcp_tcp_mss_t *eth_ip_gre_ppp_ip_tcp_tcp_mss;
struct eth_ip_gre_ppp_ip_tcp_tcp_ws_t *eth_ip_gre_ppp_ip_tcp_tcp_ws;
struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted_t
	*eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted;
struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_0_t *eth_ip_gre_ppp_ip_tcp_tcp_SACK_0;
struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_1_t *eth_ip_gre_ppp_ip_tcp_tcp_SACK_1;
struct eth_ip_gre_ppp_ip_tcp_tcp_TS_t *eth_ip_gre_ppp_ip_tcp_tcp_TS;
struct eth_ip_gre_ppp_ip_tcp_tcp_cc_new_t *eth_ip_gre_ppp_ip_tcp_tcp_cc_new;
struct eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0_t *eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0;
struct eth_ip_gre_ppp_ip_tcp_tcp_mptcp_1_t *eth_ip_gre_ppp_ip_tcp_tcp_mptcp_1;
struct eth_ip_gre_ppp_ip_tcp_tcp_unknown_0_t
	*eth_ip_gre_ppp_ip_tcp_tcp_unknown_0;
struct eth_ip_gre_ppp_ip_tcp_tcp_unknown_1_t
	*eth_ip_gre_ppp_ip_tcp_tcp_unknown_1;
struct eth_ip_gre_ppp_ip_tcp_tcp_blank_t *eth_ip_gre_ppp_ip_tcp_tcp_blank;
eth_ip_gre_ppp_ip_tcp_data_t *eth_ip_gre_ppp_ip_tcp_data;
char eth_ip_gre_ppp_ip_tcp_has_buf = 0;
u_char *eth_ip_gre_ppp_ip_tcp_buf;
int eth_ip_gre_ppp_ip_tcp_buf_length;
u_char *eth_ip_gre_ppp_ip_tcp_payload;
int eth_ip_gre_ppp_ip_tcp_payload_length;
struct eth_ip_gre_ppp_ip_tcp_rubik_bitmap_t *eth_ip_gre_ppp_ip_tcp_rubik_bitmap;
struct eth_ip_gre_ppp_ip_tcp_transition_bitmap_t
	*eth_ip_gre_ppp_ip_tcp_transition_bitmap;
struct buf_queue *eth_ip_gre_ppp_ip_tcp_bufs;
void eth_ip_gre_ppp_ip_tcp_init ()
{
	tommy_hashdyn_init (&eth_ip_gre_ppp_ip_tcp_hashtable);
	eth_ip_gre_ppp_ip_tcp_gap.tv_sec = 10;
	eth_ip_gre_ppp_ip_tcp_gap.tv_usec = 0;
	eth_ip_gre_ppp_ip_tcp_list.head = NULL;
	eth_ip_gre_ppp_ip_tcp_list.tail = NULL;
	eth_ip_gre_ppp_ip_tcp_instance = NULL;
	eth_ip_gre_ppp_ip_tcp_fake_instance =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_instance_t));
	eth_ip_gre_ppp_ip_tcp_fake_instance->is_active_part =
		malloc (sizeof (char));
	*(eth_ip_gre_ppp_ip_tcp_fake_instance->is_active_part) = 1;
	eth_ip_gre_ppp_ip_tcp_fake_instance->stand = 0;
	eth_ip_gre_ppp_ip_tcp_fake_instance_reverse =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_instance_t));
	eth_ip_gre_ppp_ip_tcp_fake_instance_reverse->is_active_part =
		eth_ip_gre_ppp_ip_tcp_fake_instance->is_active_part;
	eth_ip_gre_ppp_ip_tcp_fake_instance_reverse->stand = 1;
	eth_ip_gre_ppp_ip_tcp_select =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
	eth_ip_gre_ppp_ip_tcp_select_reverse =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
	memset (eth_ip_gre_ppp_ip_tcp_select, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
	memset (eth_ip_gre_ppp_ip_tcp_select_reverse, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
	eth_ip_gre_ppp_ip_tcp_rubik_bitmap =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_rubik_bitmap_t));
	eth_ip_gre_ppp_ip_tcp_transition_bitmap =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_transition_bitmap_t));
	memset (eth_ip_gre_ppp_ip_tcp_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_rubik_bitmap_t));
	memset (eth_ip_gre_ppp_ip_tcp_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_transition_bitmap_t));
	eth_ip_gre_ppp_ip_tcp_tcp_SACK_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_1_t));
	eth_ip_gre_ppp_ip_tcp_tcp_mptcp_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_tcp_mptcp_1_t));
	eth_ip_gre_ppp_ip_tcp_tcp_unknown_1 =
		malloc (sizeof (struct eth_ip_gre_ppp_ip_tcp_tcp_unknown_1_t));
}

char eth_ip_gre_ppp_ip_tcp_has_hole (uint64_t meta, int length,
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

uint32_t eth_ip_gre_ppp_ip_tcp_hash (void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int eth_ip_gre_ppp_ip_tcp_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t);
	return memcmp (arg, obj, size);
}

void eth_ip_gre_ppp_ip_tcp_destroy (void)
{
	free_buf_list (eth_ip_gre_ppp_ip_tcp_instance->bufs);
	free_buf_list (eth_ip_gre_ppp_ip_tcp_instance_reverse->bufs);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_ip_tcp_hashtable,
		&eth_ip_gre_ppp_ip_tcp_instance->node);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_ip_tcp_hashtable,
		&eth_ip_gre_ppp_ip_tcp_instance_reverse->node);
	if (eth_ip_gre_ppp_ip_tcp_instance->time_record_leader)
		deregister_timer (&eth_ip_gre_ppp_ip_tcp_list,
			eth_ip_gre_ppp_ip_tcp_instance->rec_ptr);
	else
		deregister_timer (&eth_ip_gre_ppp_ip_tcp_list,
			eth_ip_gre_ppp_ip_tcp_instance_reverse->rec_ptr);
	free (eth_ip_gre_ppp_ip_tcp_instance->eth_ip_gre_ppp_ip_tcp_data);
	free (eth_ip_gre_ppp_ip_tcp_instance->is_active_part);
	free (eth_ip_gre_ppp_ip_tcp_instance);
	free (eth_ip_gre_ppp_ip_tcp_instance_reverse);
}

void eth_ip_gre_ppp_ip_tcp_free (void *inst)
{
	struct eth_ip_gre_ppp_ip_tcp_instance_t *reverse =
		((struct eth_ip_gre_ppp_ip_tcp_instance_t *) inst)->pair_instance;
	free_buf_list (reverse->bufs);
	free (reverse->eth_ip_gre_ppp_ip_tcp_data);
	free (reverse->is_active_part);
	tommy_hashdyn_remove_existing (&eth_ip_gre_ppp_ip_tcp_hashtable,
		&reverse->node);
	free (reverse);
	free_buf_list (((struct eth_ip_gre_ppp_ip_tcp_instance_t *) inst)->bufs);
}

static void eth_ip_gre_ppp_ip_tcp_CLOSED (void);
static void eth_ip_gre_ppp_ip_tcp_SYN_SENT (void);
static void eth_ip_gre_ppp_ip_tcp_TERMINATE (void);
static void eth_ip_gre_ppp_ip_tcp_SYN_RECEIVED (void);
static void eth_ip_gre_ppp_ip_tcp_ESTABLISHED (void);
static void eth_ip_gre_ppp_ip_tcp_FIN_WAIT_1 (void);
static void eth_ip_gre_ppp_ip_tcp_CLOSE_WAIT (void);
static void eth_ip_gre_ppp_ip_tcp_LAST_ACK (void);
void eth_ip_gre_ppp_ip_tcp_CLOSED ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->syn))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->first_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_SYN_SENT;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->active_seq =
				(eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num + 1);
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_2 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_1 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_SYN_SENT ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_4 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_3 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->syn
				&& eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num ==
					eth_ip_gre_ppp_ip_tcp_data->active_seq)))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->second_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_SYN_RECEIVED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->passive_seq =
				(eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num + 1);
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_SYN_RECEIVED ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_6 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num ==
					eth_ip_gre_ppp_ip_tcp_data->passive_seq)))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->third_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_5 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_ESTABLISHED ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_8 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->active_seq <
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->passive_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->passive_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							passive_window) << eth_ip_gre_ppp_ip_tcp_data->
						passive_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->buffering_passive = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			temp->cur_seq = eth_ip_gre_ppp_ip_tcp_data->active_seq;
			temp->window = eth_ip_gre_ppp_ip_tcp_data->passive_ack;
			eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
				|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
				eth_ip_gre_ppp_ip_tcp_THRESHOLD)
			{
				struct buffer_node *node;
				struct avl_node *dup = NULL;
				node = malloc (sizeof (struct buffer_node));
				node->buf.buf = malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
				memcpy (node->buf.buf, eth_ip_gre_ppp_ip_tcp_payload,
					eth_ip_gre_ppp_ip_tcp_payload_length);
				node->buf.len = eth_ip_gre_ppp_ip_tcp_payload_length;
				node->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	// meta assignment
				struct avl_node **link =
					&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
				struct avl_node *parent = NULL;
				int hr = 1;
				while (link[0])
				{
					parent = link[0];
					eth_ip_gre_ppp_ip_tcp_buf_length =
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

					if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
						eth_ip_gre_ppp_ip_tcp_bufs->root->head =
							(struct avl_node *) node;
					else if (COMPARE_ASC ((struct avl_node *) node,
							eth_ip_gre_ppp_ip_tcp_bufs->root->head) == 1)
						eth_ip_gre_ppp_ip_tcp_bufs->root->head =
							(struct avl_node *) node;
					avl_node_link ((struct avl_node *) node, parent, link);
					avl_node_post_insert ((struct avl_node *) node,
						eth_ip_gre_ppp_ip_tcp_bufs->root);
				}
				if (!dup)
				{
					eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
					eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
						eth_ip_gre_ppp_ip_tcp_payload_length;

				}
				else
				{
					free (node->buf.buf);
					free (node);
				}
			}
			else
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->head->next == NULL)
				{

					eth_ip_gre_ppp_ip_tcp_bufs->head->next =
						malloc (sizeof (struct buf_list));
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data_assignment here
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf =
						malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->next = NULL;
					memcpy (eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf,
						eth_ip_gre_ppp_ip_tcp_payload,
						eth_ip_gre_ppp_ip_tcp_payload_length);
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len =
						eth_ip_gre_ppp_ip_tcp_payload_length;
					eth_ip_gre_ppp_ip_tcp_bufs->buf_len =
						eth_ip_gre_ppp_ip_tcp_payload_length;
					eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
				}
				else
				{
					if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count >=
						eth_ip_gre_ppp_ip_tcp_THRESHOLD)
					{
						struct buf_list *pre_buf;
						struct buf_list *cur_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						struct buffer_node *node;
						struct avl_node *dup = NULL;
						while (cur_buf != NULL)
						{
							dup = NULL;
							node = malloc (sizeof (struct buffer_node));
							node->buf = cur_buf->buf;
							struct avl_node **link =
								&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
							struct avl_node *parent = NULL;
							int hr = 1;
							while (link[0])
							{
								parent = link[0];
								eth_ip_gre_ppp_ip_tcp_buf_length =
									((struct buffer_node *) parent)->buf.len;
								uint64_t meta =
									((struct buffer_node *) parent)->buf.meta;
								hr = COMPARE_ASC ((struct avl_node *) node,
									parent);

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
								if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
									eth_ip_gre_ppp_ip_tcp_bufs->root->head =
										(struct avl_node *) node;
								else if (COMPARE_ASC ((struct avl_node *) node,
										eth_ip_gre_ppp_ip_tcp_bufs->root->
										head) == 1)
									eth_ip_gre_ppp_ip_tcp_bufs->root->head =
										(struct avl_node *) node;
								avl_node_link ((struct avl_node *) node, parent,
									link);
								avl_node_post_insert ((struct avl_node *) node,
									eth_ip_gre_ppp_ip_tcp_bufs->root);
							}
							pre_buf = cur_buf;
							cur_buf = cur_buf->next;
							free (pre_buf);
						}
						eth_ip_gre_ppp_ip_tcp_bufs->head->next = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf.buf =
							malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
						memcpy (node->buf.buf, eth_ip_gre_ppp_ip_tcp_payload,
							eth_ip_gre_ppp_ip_tcp_payload_length);
						node->buf.len = eth_ip_gre_ppp_ip_tcp_payload_length;
						node->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
						struct avl_node **link =
							&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						dup = NULL;
						while (link[0])
						{
							parent = link[0];
							eth_ip_gre_ppp_ip_tcp_buf_length =
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

							if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
								eth_ip_gre_ppp_ip_tcp_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									eth_ip_gre_ppp_ip_tcp_bufs->root->head) ==
								1)
								eth_ip_gre_ppp_ip_tcp_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								eth_ip_gre_ppp_ip_tcp_bufs->root);
						}
						if (!dup)
						{
							eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
							eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
								eth_ip_gre_ppp_ip_tcp_payload_length;

						}
						else
						{
							free (node);
						}
						eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 1;
					}
					else
					{
						struct buf_list *pre_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head;
						struct buf_list *cur_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						char inserted = 0;
						while (cur_buf != NULL)
						{
							int hr =
								LIST_COMPARE_ASC (cur_buf->buf.meta,
								eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num);
							eth_ip_gre_ppp_ip_tcp_buf_length = cur_buf->buf.len;
							uint64_t meta = cur_buf->buf.meta;
							if (hr == 1)
							{

								pre_buf->next =
									malloc (sizeof (struct buf_list));
								pre_buf->next->buf.buf =
									malloc
									(eth_ip_gre_ppp_ip_tcp_payload_length);
								pre_buf->next->buf.len =
									eth_ip_gre_ppp_ip_tcp_payload_length;
								memcpy (pre_buf->next->buf.buf,
									eth_ip_gre_ppp_ip_tcp_payload,
									eth_ip_gre_ppp_ip_tcp_payload_length);
								pre_buf->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
								pre_buf->next->next = cur_buf;
								eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
									eth_ip_gre_ppp_ip_tcp_payload_length;
								eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
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
								malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
							pre_buf->next->buf.len =
								eth_ip_gre_ppp_ip_tcp_payload_length;
							memcpy (pre_buf->next->buf.buf,
								eth_ip_gre_ppp_ip_tcp_payload,
								eth_ip_gre_ppp_ip_tcp_payload_length);
							pre_buf->next->next = NULL;
							pre_buf->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
							eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
								eth_ip_gre_ppp_ip_tcp_payload_length;
							eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
						}
					}
				}
			} eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			while (eth_ip_gre_ppp_ip_tcp_bufs->packet_count > 0)
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
					|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
					eth_ip_gre_ppp_ip_tcp_THRESHOLD)
				{
					uint64_t meta =
						((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
						root->head)->buf.meta;
					if (((temp->cur_seq == meta)
							|| eth_ip_gre_ppp_ip_tcp_tcp_hdr->psh))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;
						struct avl_node *head =
							eth_ip_gre_ppp_ip_tcp_bufs->root->head;
						avl_node_erase (eth_ip_gre_ppp_ip_tcp_bufs->root->head,
							eth_ip_gre_ppp_ip_tcp_bufs->root);
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				else
				{
					uint64_t meta =
						eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta;
					if (((temp->cur_seq == meta)
							|| eth_ip_gre_ppp_ip_tcp_tcp_hdr->psh))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;
						struct buf_list *head =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						eth_ip_gre_ppp_ip_tcp_bufs->head->next =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->next;
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				free (eth_ip_gre_ppp_ip_tcp_buf);
			}
			if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count == 0)
				eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 0;
			eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			while (eth_ip_gre_ppp_ip_tcp_bufs->packet_count > 0)
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
					|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
					eth_ip_gre_ppp_ip_tcp_THRESHOLD)
				{
					uint64_t meta =
						((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
						root->head)->buf.meta;
					if ((temp->window > meta))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;
						struct avl_node *head =
							eth_ip_gre_ppp_ip_tcp_bufs->root->head;
						avl_node_erase (eth_ip_gre_ppp_ip_tcp_bufs->root->head,
							eth_ip_gre_ppp_ip_tcp_bufs->root);
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				else
				{
					uint64_t meta =
						eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta;
					if ((temp->window > meta))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;
						struct buf_list *head =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						eth_ip_gre_ppp_ip_tcp_bufs->head->next =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->next;
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				free (eth_ip_gre_ppp_ip_tcp_buf);
			}
			if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count == 0)
				eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 0;
			eth_ip_gre_ppp_ip_tcp_data->active_seq = temp->cur_seq;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->active_seq ==
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->passive_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->passive_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							passive_window) << eth_ip_gre_ppp_ip_tcp_data->
						passive_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->ff_passive = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->active_seq =
				(eth_ip_gre_ppp_ip_tcp_data->active_seq +
				eth_ip_gre_ppp_ip_tcp_payload_length);
			eth_ip_gre_ppp_ip_tcp_buf = eth_ip_gre_ppp_ip_tcp_payload;
			eth_ip_gre_ppp_ip_tcp_buf_length =
				eth_ip_gre_ppp_ip_tcp_payload_length;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->active_seq >
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->passive_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->passive_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							passive_window) << eth_ip_gre_ppp_ip_tcp_data->
						passive_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->retrx_passive = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (((eth_ip_gre_ppp_ip_tcp_data->active_seq >
							eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
						&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
							eth_ip_gre_ppp_ip_tcp_data->passive_ack))
					|| ((eth_ip_gre_ppp_ip_tcp_data->active_seq <
							eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
						&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
							((eth_ip_gre_ppp_ip_tcp_data->passive_ack +
									eth_ip_gre_ppp_ip_tcp_data->
									passive_window) <<
								eth_ip_gre_ppp_ip_tcp_data->passive_ws))))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->out_of_window_passive = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_7 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->passive_seq <
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->active_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->active_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							active_window) << eth_ip_gre_ppp_ip_tcp_data->
						active_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->buffering_active = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			temp->cur_seq = eth_ip_gre_ppp_ip_tcp_data->passive_seq;
			temp->window = eth_ip_gre_ppp_ip_tcp_data->active_ack;
			eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
				|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
				eth_ip_gre_ppp_ip_tcp_THRESHOLD)
			{
				struct buffer_node *node;
				struct avl_node *dup = NULL;
				node = malloc (sizeof (struct buffer_node));
				node->buf.buf = malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
				memcpy (node->buf.buf, eth_ip_gre_ppp_ip_tcp_payload,
					eth_ip_gre_ppp_ip_tcp_payload_length);
				node->buf.len = eth_ip_gre_ppp_ip_tcp_payload_length;
				node->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	// meta assignment
				struct avl_node **link =
					&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
				struct avl_node *parent = NULL;
				int hr = 1;
				while (link[0])
				{
					parent = link[0];
					eth_ip_gre_ppp_ip_tcp_buf_length =
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

					if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
						eth_ip_gre_ppp_ip_tcp_bufs->root->head =
							(struct avl_node *) node;
					else if (COMPARE_ASC ((struct avl_node *) node,
							eth_ip_gre_ppp_ip_tcp_bufs->root->head) == 1)
						eth_ip_gre_ppp_ip_tcp_bufs->root->head =
							(struct avl_node *) node;
					avl_node_link ((struct avl_node *) node, parent, link);
					avl_node_post_insert ((struct avl_node *) node,
						eth_ip_gre_ppp_ip_tcp_bufs->root);
				}
				if (!dup)
				{
					eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
					eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
						eth_ip_gre_ppp_ip_tcp_payload_length;

				}
				else
				{
					free (node->buf.buf);
					free (node);
				}
			}
			else
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->head->next == NULL)
				{

					eth_ip_gre_ppp_ip_tcp_bufs->head->next =
						malloc (sizeof (struct buf_list));
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data_assignment here
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf =
						malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->next = NULL;
					memcpy (eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf,
						eth_ip_gre_ppp_ip_tcp_payload,
						eth_ip_gre_ppp_ip_tcp_payload_length);
					eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len =
						eth_ip_gre_ppp_ip_tcp_payload_length;
					eth_ip_gre_ppp_ip_tcp_bufs->buf_len =
						eth_ip_gre_ppp_ip_tcp_payload_length;
					eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
				}
				else
				{
					if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count >=
						eth_ip_gre_ppp_ip_tcp_THRESHOLD)
					{
						struct buf_list *pre_buf;
						struct buf_list *cur_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						struct buffer_node *node;
						struct avl_node *dup = NULL;
						while (cur_buf != NULL)
						{
							dup = NULL;
							node = malloc (sizeof (struct buffer_node));
							node->buf = cur_buf->buf;
							struct avl_node **link =
								&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
							struct avl_node *parent = NULL;
							int hr = 1;
							while (link[0])
							{
								parent = link[0];
								eth_ip_gre_ppp_ip_tcp_buf_length =
									((struct buffer_node *) parent)->buf.len;
								uint64_t meta =
									((struct buffer_node *) parent)->buf.meta;
								hr = COMPARE_ASC ((struct avl_node *) node,
									parent);

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
								if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
									eth_ip_gre_ppp_ip_tcp_bufs->root->head =
										(struct avl_node *) node;
								else if (COMPARE_ASC ((struct avl_node *) node,
										eth_ip_gre_ppp_ip_tcp_bufs->root->
										head) == 1)
									eth_ip_gre_ppp_ip_tcp_bufs->root->head =
										(struct avl_node *) node;
								avl_node_link ((struct avl_node *) node, parent,
									link);
								avl_node_post_insert ((struct avl_node *) node,
									eth_ip_gre_ppp_ip_tcp_bufs->root);
							}
							pre_buf = cur_buf;
							cur_buf = cur_buf->next;
							free (pre_buf);
						}
						eth_ip_gre_ppp_ip_tcp_bufs->head->next = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf.buf =
							malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
						memcpy (node->buf.buf, eth_ip_gre_ppp_ip_tcp_payload,
							eth_ip_gre_ppp_ip_tcp_payload_length);
						node->buf.len = eth_ip_gre_ppp_ip_tcp_payload_length;
						node->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
						struct avl_node **link =
							&(eth_ip_gre_ppp_ip_tcp_bufs->root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						dup = NULL;
						while (link[0])
						{
							parent = link[0];
							eth_ip_gre_ppp_ip_tcp_buf_length =
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

							if (!eth_ip_gre_ppp_ip_tcp_bufs->root->node)
								eth_ip_gre_ppp_ip_tcp_bufs->root->head =
									(struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									eth_ip_gre_ppp_ip_tcp_bufs->root->head) ==
								1)
								eth_ip_gre_ppp_ip_tcp_bufs->root->head =
									(struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								eth_ip_gre_ppp_ip_tcp_bufs->root);
						}
						if (!dup)
						{
							eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
							eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
								eth_ip_gre_ppp_ip_tcp_payload_length;

						}
						else
						{
							free (node);
						}
						eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 1;
					}
					else
					{
						struct buf_list *pre_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head;
						struct buf_list *cur_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						char inserted = 0;
						while (cur_buf != NULL)
						{
							int hr =
								LIST_COMPARE_ASC (cur_buf->buf.meta,
								eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num);
							eth_ip_gre_ppp_ip_tcp_buf_length = cur_buf->buf.len;
							uint64_t meta = cur_buf->buf.meta;
							if (hr == 1)
							{

								pre_buf->next =
									malloc (sizeof (struct buf_list));
								pre_buf->next->buf.buf =
									malloc
									(eth_ip_gre_ppp_ip_tcp_payload_length);
								pre_buf->next->buf.len =
									eth_ip_gre_ppp_ip_tcp_payload_length;
								memcpy (pre_buf->next->buf.buf,
									eth_ip_gre_ppp_ip_tcp_payload,
									eth_ip_gre_ppp_ip_tcp_payload_length);
								pre_buf->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
								pre_buf->next->next = cur_buf;
								eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
									eth_ip_gre_ppp_ip_tcp_payload_length;
								eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
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
								malloc (eth_ip_gre_ppp_ip_tcp_payload_length);
							pre_buf->next->buf.len =
								eth_ip_gre_ppp_ip_tcp_payload_length;
							memcpy (pre_buf->next->buf.buf,
								eth_ip_gre_ppp_ip_tcp_payload,
								eth_ip_gre_ppp_ip_tcp_payload_length);
							pre_buf->next->next = NULL;
							pre_buf->next->buf.meta = eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num;	//meta_data assignment here
							eth_ip_gre_ppp_ip_tcp_bufs->buf_len +=
								eth_ip_gre_ppp_ip_tcp_payload_length;
							eth_ip_gre_ppp_ip_tcp_bufs->packet_count++;
						}
					}
				}
			} eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			while (eth_ip_gre_ppp_ip_tcp_bufs->packet_count > 0)
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
					|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
					eth_ip_gre_ppp_ip_tcp_THRESHOLD)
				{
					uint64_t meta =
						((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
						root->head)->buf.meta;
					if (((temp->cur_seq == meta)
							|| eth_ip_gre_ppp_ip_tcp_tcp_hdr->psh))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;
						struct avl_node *head =
							eth_ip_gre_ppp_ip_tcp_bufs->root->head;
						avl_node_erase (eth_ip_gre_ppp_ip_tcp_bufs->root->head,
							eth_ip_gre_ppp_ip_tcp_bufs->root);
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				else
				{
					uint64_t meta =
						eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta;
					if (((temp->cur_seq == meta)
							|| eth_ip_gre_ppp_ip_tcp_tcp_hdr->psh))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;
						struct buf_list *head =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						eth_ip_gre_ppp_ip_tcp_bufs->head->next =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->next;
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				free (eth_ip_gre_ppp_ip_tcp_buf);
			}
			if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count == 0)
				eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 0;
			eth_ip_gre_ppp_ip_tcp_bufs = eth_ip_gre_ppp_ip_tcp_instance->bufs;
			while (eth_ip_gre_ppp_ip_tcp_bufs->packet_count > 0)
			{
				if (eth_ip_gre_ppp_ip_tcp_bufs->is_tree
					|| eth_ip_gre_ppp_ip_tcp_bufs->packet_count >
					eth_ip_gre_ppp_ip_tcp_THRESHOLD)
				{
					uint64_t meta =
						((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
						root->head)->buf.meta;
					if ((temp->window > meta))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							((struct buffer_node *) eth_ip_gre_ppp_ip_tcp_bufs->
							root->head)->buf.len;
						struct avl_node *head =
							eth_ip_gre_ppp_ip_tcp_bufs->root->head;
						avl_node_erase (eth_ip_gre_ppp_ip_tcp_bufs->root->head,
							eth_ip_gre_ppp_ip_tcp_bufs->root);
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				else
				{
					uint64_t meta =
						eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.meta;
					if ((temp->window > meta))
					{
						eth_ip_gre_ppp_ip_tcp_buf =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.buf;
						eth_ip_gre_ppp_ip_tcp_buf_length =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;

						eth_ip_gre_ppp_ip_tcp_bufs->buf_len -=
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->buf.len;
						struct buf_list *head =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next;
						eth_ip_gre_ppp_ip_tcp_bufs->head->next =
							eth_ip_gre_ppp_ip_tcp_bufs->head->next->next;
						eth_ip_gre_ppp_ip_tcp_bufs->packet_count--;
						free (head);
						temp->cur_seq =
							(meta + eth_ip_gre_ppp_ip_tcp_payload_length);
					}
					else
					{
						break;
					}
				}
				free (eth_ip_gre_ppp_ip_tcp_buf);
			}
			if (eth_ip_gre_ppp_ip_tcp_bufs->packet_count == 0)
				eth_ip_gre_ppp_ip_tcp_bufs->is_tree = 0;
			eth_ip_gre_ppp_ip_tcp_data->passive_seq = temp->cur_seq;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->passive_seq ==
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->active_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->active_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							active_window) << eth_ip_gre_ppp_ip_tcp_data->
						active_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->ff_active = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->passive_seq =
				(eth_ip_gre_ppp_ip_tcp_data->passive_seq +
				eth_ip_gre_ppp_ip_tcp_payload_length);
			eth_ip_gre_ppp_ip_tcp_buf = eth_ip_gre_ppp_ip_tcp_payload;
			eth_ip_gre_ppp_ip_tcp_buf_length =
				eth_ip_gre_ppp_ip_tcp_payload_length;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (eth_ip_gre_ppp_ip_tcp_data->passive_seq >
					eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num >=
					eth_ip_gre_ppp_ip_tcp_data->active_ack)
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
					((eth_ip_gre_ppp_ip_tcp_data->active_ack +
							eth_ip_gre_ppp_ip_tcp_data->
							active_window) << eth_ip_gre_ppp_ip_tcp_data->
						active_ws))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->retrx_active = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		if ((1 && (eth_ip_gre_ppp_ip_tcp_payload_length > 0)
				&& (((eth_ip_gre_ppp_ip_tcp_data->passive_seq >
							eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
						&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
							eth_ip_gre_ppp_ip_tcp_data->active_ack))
					|| ((eth_ip_gre_ppp_ip_tcp_data->passive_seq <
							eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num)
						&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num <
							((eth_ip_gre_ppp_ip_tcp_data->active_ack +
									eth_ip_gre_ppp_ip_tcp_data->
									active_window) <<
								eth_ip_gre_ppp_ip_tcp_data->active_ws))))))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->out_of_window_active = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_ESTABLISHED;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->fin))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->disconnected_1st_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_FIN_WAIT_1;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->active_seq =
				(eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num + 1);
			*(eth_ip_gre_ppp_ip_tcp_instance->is_active_part) =
				eth_ip_gre_ppp_ip_tcp_instance->stand ^ 1;
			;
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_FIN_WAIT_1 ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_10 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_9 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
				&& !eth_ip_gre_ppp_ip_tcp_tcp_hdr->fin
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num ==
					eth_ip_gre_ppp_ip_tcp_data->active_seq)))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->disconnected_2nd_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_CLOSE_WAIT;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
				&& eth_ip_gre_ppp_ip_tcp_tcp_hdr->fin
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num ==
					eth_ip_gre_ppp_ip_tcp_data->active_seq)))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->disconnected_2nd_hs_fast =
				1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_LAST_ACK;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->passive_seq =
				(eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num + 1);
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_CLOSE_WAIT ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_12 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_11 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->fin
				&& !eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->disconnected_3rd_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_LAST_ACK;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_data->passive_seq =
				(eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num + 1);
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_LAST_ACK ()
{
	if (*(eth_ip_gre_ppp_ip_tcp_instance->
			is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_14 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
				&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num ==
					eth_ip_gre_ppp_ip_tcp_data->passive_seq)))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->disconnected_4th_hs = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
	if (!(*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		if ((1 && eth_ip_gre_ppp_ip_tcp_tcp_hdr->rst))
		{
			eth_ip_gre_ppp_ip_tcp_transition_bitmap->rst_13 = 1;
			eth_ip_gre_ppp_ip_tcp_instance->state =
				eth_ip_gre_ppp_ip_tcp_TERMINATE;
			eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
				eth_ip_gre_ppp_ip_tcp_instance->state;
			eth_ip_gre_ppp_ip_tcp_destroy ();
			return;
		}
		return;
	}
}

void eth_ip_gre_ppp_ip_tcp_TERMINATE ()
{
	return;
}

void eth_ip_gre_ppp_ip_tcp_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_hdr = 1;
	eth_ip_gre_ppp_ip_tcp_tcp_hdr =
		(struct eth_ip_gre_ppp_ip_tcp_tcp_hdr_t *) (payload + cur_pos);
	cur_pos += 20;
	eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num =
		ntohl (eth_ip_gre_ppp_ip_tcp_tcp_hdr->seq_num);
	eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num =
		ntohl (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num);
	while (((cur_pos < (eth_ip_gre_ppp_ip_tcp_tcp_hdr->hdr_len * 4))
			&& (eth_ip_gre_ppp_ip_tcp_payload_length > 0)))
	{
		any_parse = 1;
		any_parse = 0;
		if (((struct eth_ip_gre_ppp_ip_tcp_tcp_eol_t *) (payload +
					cur_pos))->eol_type == 0)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_eol =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_eol =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_eol_t *) (payload + cur_pos);
			cur_pos += 1;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_nop_t *) (payload +
					cur_pos))->nop_type == 1)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_nop =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_nop =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_nop_t *) (payload + cur_pos);
			cur_pos += 1;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_mss_t *) (payload +
					cur_pos))->mss_type == 2)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_mss =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_mss =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_mss_t *) (payload + cur_pos);
			cur_pos += 4;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_ws_t *) (payload +
					cur_pos))->ws_type == 3)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_ws =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_ws =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_ws_t *) (payload + cur_pos);
			cur_pos += 3;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted_t *) (payload
					+ cur_pos))->SCAK_permitted_type == 4)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->
				eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted = 1;
			eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_permitted_t *) (payload +
				cur_pos);
			cur_pos += 2;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_0_t *) (payload +
					cur_pos))->SACK_type == 5)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_SACK =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_SACK_0 =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_SACK_0_t *) (payload +
				cur_pos);
			cur_pos += 2;
			eth_ip_gre_ppp_ip_tcp_tcp_SACK_1->SACK_value = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_ip_tcp_tcp_SACK_0->SACK_len - 2);
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_TS_t *) (payload +
					cur_pos))->TS_type == 8)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_TS =
				1;
			eth_ip_gre_ppp_ip_tcp_tcp_TS =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_TS_t *) (payload + cur_pos);
			cur_pos += 10;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_cc_new_t *) (payload +
					cur_pos))->cc_new_type == 12)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->
				eth_ip_gre_ppp_ip_tcp_tcp_cc_new = 1;
			eth_ip_gre_ppp_ip_tcp_tcp_cc_new =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_cc_new_t *) (payload +
				cur_pos);
			cur_pos += 6;
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0_t *) (payload +
					cur_pos))->mptcp_type == 30)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->
				eth_ip_gre_ppp_ip_tcp_tcp_mptcp = 1;
			eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0 =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0_t *) (payload +
				cur_pos);
			cur_pos += 2;
			eth_ip_gre_ppp_ip_tcp_tcp_mptcp_1->mptcp_value = payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_ip_tcp_tcp_mptcp_0->mptcp_len - 2);
		}
		else if (((struct eth_ip_gre_ppp_ip_tcp_tcp_unknown_0_t *) (payload +
					cur_pos))->unknown_type == 251)
		{
			any_parse = 1;
			eth_ip_gre_ppp_ip_tcp_rubik_bitmap->
				eth_ip_gre_ppp_ip_tcp_tcp_unknown = 1;
			eth_ip_gre_ppp_ip_tcp_tcp_unknown_0 =
				(struct eth_ip_gre_ppp_ip_tcp_tcp_unknown_0_t *) (payload +
				cur_pos);
			cur_pos += 2;
			eth_ip_gre_ppp_ip_tcp_tcp_unknown_1->unknown_value =
				payload + cur_pos;
			cur_pos += (eth_ip_gre_ppp_ip_tcp_tcp_unknown_0->unknown_len - 2);
		}
		if (!any_parse)
		{
			break;
		}
	}
	while (((cur_pos < (eth_ip_gre_ppp_ip_tcp_tcp_hdr->hdr_len * 4))
			&& (eth_ip_gre_ppp_ip_tcp_payload_length > 0)))
	{
		any_parse = 1;
		eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_blank = 1;
		eth_ip_gre_ppp_ip_tcp_tcp_blank =
			(struct eth_ip_gre_ppp_ip_tcp_tcp_blank_t *) (payload + cur_pos);
		cur_pos += 4;
		if (!any_parse)
		{
			break;
		}
	}
	eth_ip_gre_ppp_ip_tcp_payload_length -= cur_pos;
	eth_ip_gre_ppp_ip_tcp_payload += cur_pos;
	eth_ip_gre_ppp_ip_tcp_select->src_src_addr =
		eth_ip_gre_ppp_ip_ip_hdr->src_addr;
	eth_ip_gre_ppp_ip_tcp_select->src_srcport =
		eth_ip_gre_ppp_ip_tcp_tcp_hdr->srcport;
	eth_ip_gre_ppp_ip_tcp_select->dst_dst_addr =
		eth_ip_gre_ppp_ip_ip_hdr->dst_addr;
	eth_ip_gre_ppp_ip_tcp_select->dst_dstport =
		eth_ip_gre_ppp_ip_tcp_tcp_hdr->dstport;
	eth_ip_gre_ppp_ip_tcp_select_reverse->src_src_addr =
		eth_ip_gre_ppp_ip_ip_hdr->dst_addr;
	eth_ip_gre_ppp_ip_tcp_select_reverse->src_srcport =
		eth_ip_gre_ppp_ip_tcp_tcp_hdr->dstport;
	eth_ip_gre_ppp_ip_tcp_select_reverse->dst_dst_addr =
		eth_ip_gre_ppp_ip_ip_hdr->src_addr;
	eth_ip_gre_ppp_ip_tcp_select_reverse->dst_dstport =
		eth_ip_gre_ppp_ip_tcp_tcp_hdr->srcport;
}

void eth_ip_gre_ppp_ip_tcp_selector (struct timeval *now)
{
	uint32_t hash = eth_ip_gre_ppp_ip_tcp_hash (eth_ip_gre_ppp_ip_tcp_select);
	eth_ip_gre_ppp_ip_tcp_instance =
		tommy_hashdyn_search (&eth_ip_gre_ppp_ip_tcp_hashtable,
		eth_ip_gre_ppp_ip_tcp_compare, eth_ip_gre_ppp_ip_tcp_select, hash);
	if (!eth_ip_gre_ppp_ip_tcp_instance)
	{
		eth_ip_gre_ppp_ip_tcp_instance =
			(struct eth_ip_gre_ppp_ip_tcp_instance_t *) malloc (sizeof (struct
				eth_ip_gre_ppp_ip_tcp_instance_t));
		memset (eth_ip_gre_ppp_ip_tcp_instance, 0,
			sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
		eth_ip_gre_ppp_ip_tcp_instance_reverse =
			(struct eth_ip_gre_ppp_ip_tcp_instance_t *) malloc (sizeof (struct
				eth_ip_gre_ppp_ip_tcp_instance_t));
		memset (eth_ip_gre_ppp_ip_tcp_instance_reverse, 0,
			sizeof (struct eth_ip_gre_ppp_ip_tcp_select_t));
		eth_ip_gre_ppp_ip_tcp_data =
			(eth_ip_gre_ppp_ip_tcp_data_t *)
			malloc (sizeof (eth_ip_gre_ppp_ip_tcp_data_t));
		eth_ip_gre_ppp_ip_tcp_data->active_buf_len = 0;
		eth_ip_gre_ppp_ip_tcp_data->passive_buf_len = 0;
		eth_ip_gre_ppp_ip_tcp_data->active_ws = 1;
		eth_ip_gre_ppp_ip_tcp_data->passive_ws = 1;
		eth_ip_gre_ppp_ip_tcp_data->active_ack = 0;
		eth_ip_gre_ppp_ip_tcp_data->passive_ack = 0;
		eth_ip_gre_ppp_ip_tcp_instance->eth_ip_gre_ppp_ip_tcp_select =
			*eth_ip_gre_ppp_ip_tcp_select;
		eth_ip_gre_ppp_ip_tcp_instance->eth_ip_gre_ppp_ip_tcp_data =
			eth_ip_gre_ppp_ip_tcp_data;
		eth_ip_gre_ppp_ip_tcp_instance->time_record_leader = 1;
		eth_ip_gre_ppp_ip_tcp_instance->is_active_part = malloc (sizeof (char));
		eth_ip_gre_ppp_ip_tcp_instance->stand = 0;
		*(eth_ip_gre_ppp_ip_tcp_instance->is_active_part) = 1;
		eth_ip_gre_ppp_ip_tcp_instance->state = eth_ip_gre_ppp_ip_tcp_CLOSED;
		eth_ip_gre_ppp_ip_tcp_instance->rec_ptr =
			timer_update (&eth_ip_gre_ppp_ip_tcp_list,
			eth_ip_gre_ppp_ip_tcp_instance, NULL, now);
		eth_ip_gre_ppp_ip_tcp_instance->pair_instance =
			eth_ip_gre_ppp_ip_tcp_instance_reverse;
		init_buf_list (&eth_ip_gre_ppp_ip_tcp_instance->bufs);
		hash = eth_ip_gre_ppp_ip_tcp_hash (eth_ip_gre_ppp_ip_tcp_select);
		tommy_hashdyn_insert (&eth_ip_gre_ppp_ip_tcp_hashtable,
			&eth_ip_gre_ppp_ip_tcp_instance->node,
			eth_ip_gre_ppp_ip_tcp_instance, hash);
		eth_ip_gre_ppp_ip_tcp_instance_reverse->eth_ip_gre_ppp_ip_tcp_select =
			*eth_ip_gre_ppp_ip_tcp_select_reverse;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->eth_ip_gre_ppp_ip_tcp_data =
			eth_ip_gre_ppp_ip_tcp_data;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->time_record_leader = 0;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->is_active_part =
			eth_ip_gre_ppp_ip_tcp_instance->is_active_part;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->stand = 1;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->state =
			eth_ip_gre_ppp_ip_tcp_CLOSED;
		eth_ip_gre_ppp_ip_tcp_instance_reverse->pair_instance =
			eth_ip_gre_ppp_ip_tcp_instance;
		init_buf_list (&eth_ip_gre_ppp_ip_tcp_instance_reverse->bufs);
		hash =
			eth_ip_gre_ppp_ip_tcp_hash (eth_ip_gre_ppp_ip_tcp_select_reverse);
		tommy_hashdyn_insert (&eth_ip_gre_ppp_ip_tcp_hashtable,
			&eth_ip_gre_ppp_ip_tcp_instance_reverse->node,
			eth_ip_gre_ppp_ip_tcp_instance_reverse, hash);
	}
	else
	{
		eth_ip_gre_ppp_ip_tcp_instance_reverse =
			eth_ip_gre_ppp_ip_tcp_instance->pair_instance;
		eth_ip_gre_ppp_ip_tcp_data =
			eth_ip_gre_ppp_ip_tcp_instance->eth_ip_gre_ppp_ip_tcp_data;
		if (eth_ip_gre_ppp_ip_tcp_instance->time_record_leader)
			eth_ip_gre_ppp_ip_tcp_instance->rec_ptr =
				timer_update (&eth_ip_gre_ppp_ip_tcp_list,
				eth_ip_gre_ppp_ip_tcp_instance,
				eth_ip_gre_ppp_ip_tcp_instance->rec_ptr, now);
		else
			eth_ip_gre_ppp_ip_tcp_instance_reverse->rec_ptr =
				timer_update (&eth_ip_gre_ppp_ip_tcp_list,
				eth_ip_gre_ppp_ip_tcp_instance_reverse,
				eth_ip_gre_ppp_ip_tcp_instance_reverse->rec_ptr, now);
	}
	temp->buf_len = 0;
	if ((eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_ws
			&& (!(*(eth_ip_gre_ppp_ip_tcp_instance->
						is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->
					stand))))
	{
		eth_ip_gre_ppp_ip_tcp_data->passive_ws =
			eth_ip_gre_ppp_ip_tcp_tcp_ws->ws_value;
	}
	if ((eth_ip_gre_ppp_ip_tcp_rubik_bitmap->eth_ip_gre_ppp_ip_tcp_tcp_ws
			&& (*(eth_ip_gre_ppp_ip_tcp_instance->
					is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)))
	{
		eth_ip_gre_ppp_ip_tcp_data->active_ws =
			eth_ip_gre_ppp_ip_tcp_tcp_ws->ws_value;
	}
	if ((!(*(eth_ip_gre_ppp_ip_tcp_instance->
					is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)))
	{
		eth_ip_gre_ppp_ip_tcp_data->passive_window =
			eth_ip_gre_ppp_ip_tcp_tcp_hdr->window_size;
	}
	if ((*(eth_ip_gre_ppp_ip_tcp_instance->
				is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand))
	{
		eth_ip_gre_ppp_ip_tcp_data->active_window =
			eth_ip_gre_ppp_ip_tcp_tcp_hdr->window_size;
	}
	if (((!(*(eth_ip_gre_ppp_ip_tcp_instance->
						is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->
					stand)) && eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
			&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num >
				eth_ip_gre_ppp_ip_tcp_data->passive_ack)))
	{
		eth_ip_gre_ppp_ip_tcp_data->passive_ack =
			eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num;
	}
	if (((*(eth_ip_gre_ppp_ip_tcp_instance->
					is_active_part) ^ eth_ip_gre_ppp_ip_tcp_instance->stand)
			&& eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack
			&& (eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num >
				eth_ip_gre_ppp_ip_tcp_data->active_ack)))
	{
		eth_ip_gre_ppp_ip_tcp_data->active_ack =
			eth_ip_gre_ppp_ip_tcp_tcp_hdr->ack_num;
	}
}

void eth_ip_gre_ppp_ip_tcp_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is tcp layer\n");
	printf ("packet length is %d\n", length);
	printf ("------------packet end------------\n");
	static uint64_t ts = 0;
	static uint64_t int_now;
	eth_ip_gre_ppp_ip_tcp_payload = payload;
	eth_ip_gre_ppp_ip_tcp_payload_length = length;
	eth_ip_gre_ppp_ip_tcp_data_assignment (payload);
	eth_ip_gre_ppp_ip_tcp_selector (now);
	eth_ip_gre_ppp_ip_tcp_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&eth_ip_gre_ppp_ip_tcp_list,
			&eth_ip_gre_ppp_ip_tcp_gap, &eth_ip_gre_ppp_ip_tcp_hashtable,
			offsetof (struct eth_ip_gre_ppp_ip_tcp_instance_t, node),
			eth_ip_gre_ppp_ip_tcp_free, now);
		ts = int_now;
	}
	memset (eth_ip_gre_ppp_ip_tcp_rubik_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_rubik_bitmap_t));
	memset (eth_ip_gre_ppp_ip_tcp_transition_bitmap, 0,
		sizeof (struct eth_ip_gre_ppp_ip_tcp_transition_bitmap_t));
	if (eth_ip_gre_ppp_ip_tcp_has_buf)
	{
		free (eth_ip_gre_ppp_ip_tcp_buf);
		eth_ip_gre_ppp_ip_tcp_has_buf = 0;
	}
}
