#include "loopback_ip_udp_quic_header_quic_frame_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
#define loopback_ip_udp_quic_header_quic_frame_THRESHOLD 10
struct loopback_ip_udp_quic_header_quic_frame_instance_t
	*loopback_ip_udp_quic_header_quic_frame_instance;
struct loopback_ip_udp_quic_header_quic_frame_select_t
	*loopback_ip_udp_quic_header_quic_frame_select;
struct loopback_ip_udp_quic_header_quic_frame_instance_t
	*loopback_ip_udp_quic_header_quic_frame_fake_instance;
tommy_hashdyn loopback_ip_udp_quic_header_quic_frame_hashtable;
struct timer loopback_ip_udp_quic_header_quic_frame_list;
struct timeval loopback_ip_udp_quic_header_quic_frame_gap;
struct loopback_ip_udp_quic_header_quic_frame_QUICFrame_t
	*loopback_ip_udp_quic_header_quic_frame_QUICFrame;
struct loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0;
struct loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1_t
	*loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_0;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_1_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_1;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_2_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_2;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_3_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_3;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_4_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_4;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_5_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_5;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_6_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_6;
struct loopback_ip_udp_quic_header_quic_frame_QUICACK_7_t
	*loopback_ip_udp_quic_header_quic_frame_QUICACK_7;
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxData_t
	*loopback_ip_udp_quic_header_quic_frame_QUICMaxData;
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0;
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1_t
	*loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1;
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2_t
	*loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2;
struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3_t
	*loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength;
struct loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0_t
	*loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0;
loopback_ip_udp_quic_header_quic_frame_data_t
	*loopback_ip_udp_quic_header_quic_frame_data;
char loopback_ip_udp_quic_header_quic_frame_has_buf = 0;
u_char *loopback_ip_udp_quic_header_quic_frame_buf;
int loopback_ip_udp_quic_header_quic_frame_buf_length;
u_char *loopback_ip_udp_quic_header_quic_frame_payload;
int loopback_ip_udp_quic_header_quic_frame_payload_length;
struct loopback_ip_udp_quic_header_quic_frame_rubik_bitmap_t
	*loopback_ip_udp_quic_header_quic_frame_rubik_bitmap;
struct loopback_ip_udp_quic_header_quic_frame_transition_bitmap_t
	*loopback_ip_udp_quic_header_quic_frame_transition_bitmap;
struct buf_queue *loopback_ip_udp_quic_header_quic_frame_bufs;
void loopback_ip_udp_quic_header_quic_frame_init ()
{
	tommy_hashdyn_init (&loopback_ip_udp_quic_header_quic_frame_hashtable);
	loopback_ip_udp_quic_header_quic_frame_gap.tv_sec = 10;
	loopback_ip_udp_quic_header_quic_frame_gap.tv_usec = 0;
	loopback_ip_udp_quic_header_quic_frame_list.head = NULL;
	loopback_ip_udp_quic_header_quic_frame_list.tail = NULL;
	loopback_ip_udp_quic_header_quic_frame_instance = NULL;
	loopback_ip_udp_quic_header_quic_frame_fake_instance =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_instance_t));
	loopback_ip_udp_quic_header_quic_frame_select =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_select_t));
	memset (loopback_ip_udp_quic_header_quic_frame_select, 0,
		sizeof (struct loopback_ip_udp_quic_header_quic_frame_select_t));
	loopback_ip_udp_quic_header_quic_frame_rubik_bitmap =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_rubik_bitmap_t));
	loopback_ip_udp_quic_header_quic_frame_transition_bitmap =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_transition_bitmap_t));
	memset (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_quic_frame_rubik_bitmap_t));
	memset (loopback_ip_udp_quic_header_quic_frame_transition_bitmap, 0,
		sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_transition_bitmap_t));
	loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0_t));
	loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_0_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_1 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_1_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_2 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_2_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_3 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_3_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_4 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_4_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_5 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_5_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_6 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_6_t));
	loopback_ip_udp_quic_header_quic_frame_QUICACK_7 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICACK_7_t));
	loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0_t));
	loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1_t));
	loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2_t));
	loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3_t));
	loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0_t));
	loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0_t));
	loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0_t));
}

char loopback_ip_udp_quic_header_quic_frame_has_hole (uint64_t meta, int length,
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

uint32_t loopback_ip_udp_quic_header_quic_frame_hash (void *obj)
{
	int select_offset =
		offsetof (struct loopback_ip_udp_quic_header_quic_frame_select_t,
		src_stream_id_tail);
	int offset = 0;
	char hash_str[select_offset +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail];
	memcpy (hash_str, obj, select_offset);
	offset += select_offset;
	memcpy (hash_str + offset,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail);
	offset +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail;
	memcpy (hash_str + offset,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail);
	offset +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail;
	return tommy_hash_u32 (0, hash_str, offset);
}

int loopback_ip_udp_quic_header_quic_frame_compare (const void *arg,
	const void *obj)
{
	int offset_arg =
		offsetof (struct loopback_ip_udp_quic_header_quic_frame_select_t,
		src_stream_id_tail) +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		src_length_stream_id_tail +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		dst_length_stream_id_tail;
	int offset_obj =
		offsetof (struct loopback_ip_udp_quic_header_quic_frame_select_t,
		src_stream_id_tail) +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail +
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail;
	if (offset_arg != offset_obj)
		return -1;
	char arg_str[offset_arg];
	char obj_str[offset_obj];
	offset_arg =
		offsetof (struct loopback_ip_udp_quic_header_quic_frame_select_t,
		src_stream_id_tail);
	offset_obj =
		offsetof (struct loopback_ip_udp_quic_header_quic_frame_select_t,
		src_stream_id_tail);
	memcpy (arg_str, arg, offset_arg);
	memcpy (obj_str, obj, offset_obj);
	memcpy (arg_str + offset_arg,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		src_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		src_length_stream_id_tail);
	offset_arg +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		src_length_stream_id_tail;
	memcpy (arg_str + offset_arg,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		dst_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		dst_length_stream_id_tail);
	offset_arg +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) arg)->
		dst_length_stream_id_tail;
	memcpy (obj_str + offset_obj,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail);
	offset_obj +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		src_length_stream_id_tail;
	memcpy (obj_str + offset_obj,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_stream_id_tail,
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail);
	offset_obj +=
		((struct loopback_ip_udp_quic_header_quic_frame_select_t *) obj)->
		dst_length_stream_id_tail;
	return memcmp (arg, obj, offset_arg);
}

void loopback_ip_udp_quic_header_quic_frame_destroy ()
{
	free (loopback_ip_udp_quic_header_quic_frame_instance->
		loopback_ip_udp_quic_header_quic_frame_data);
	free_buf_list (loopback_ip_udp_quic_header_quic_frame_instance->bufs);
	tommy_hashdyn_remove_existing
		(&loopback_ip_udp_quic_header_quic_frame_hashtable,
		&loopback_ip_udp_quic_header_quic_frame_instance->node);
	deregister_timer (&loopback_ip_udp_quic_header_quic_frame_list,
		loopback_ip_udp_quic_header_quic_frame_instance->rec_ptr);
	free (loopback_ip_udp_quic_header_quic_frame_instance);
}

void loopback_ip_udp_quic_header_quic_frame_free (void *inst)
{
	free (((struct loopback_ip_udp_quic_header_quic_frame_instance_t *) inst)->
		loopback_ip_udp_quic_header_quic_frame_data);
	free_buf_list (((struct loopback_ip_udp_quic_header_quic_frame_instance_t *)
			inst)->bufs);
}

static void loopback_ip_udp_quic_header_quic_frame_dump (void);
static void loopback_ip_udp_quic_header_quic_frame_frag (void);
void loopback_ip_udp_quic_header_quic_frame_dump ()
{
	if (!loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID)
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->other_frame =
			1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_dump;
		return;
	}
	if ((loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID
			&& ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 1) == 0)))
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->more_frag = 1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_frag;
		loopback_ip_udp_quic_header_quic_frame_data->expect_length = 0;
		loopback_ip_udp_quic_header_quic_frame_payload_length =
			QUICFrameTempData->payload_len;
		loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
			|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
			loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf =
				malloc (loopback_ip_udp_quic_header_quic_frame_payload_length);
			memcpy (node->buf.buf,
				loopback_ip_udp_quic_header_quic_frame_payload,
				loopback_ip_udp_quic_header_quic_frame_payload_length);
			node->buf.len =
				loopback_ip_udp_quic_header_quic_frame_payload_length;
			node->buf.meta = QUICFrameTempData->offset;	// meta assignment
			struct avl_node **link =
				&(loopback_ip_udp_quic_header_quic_frame_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_udp_quic_header_quic_frame_buf_length =
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

				if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->node)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head) == 1)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_udp_quic_header_quic_frame_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
					loopback_ip_udp_quic_header_quic_frame_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->head->next == NULL)
			{

				loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.meta = QUICFrameTempData->offset;	//meta_data_assignment here
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					buf =
					malloc
					(loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->next =
					NULL;
				memcpy (loopback_ip_udp_quic_header_quic_frame_bufs->head->
					next->buf.buf,
					loopback_ip_udp_quic_header_quic_frame_payload,
					loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					len = loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len =
					loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >=
					loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_udp_quic_header_quic_frame_bufs->
							root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_udp_quic_header_quic_frame_buf_length =
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
							if (!loopback_ip_udp_quic_header_quic_frame_bufs->
								root->node)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head) == 1)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf =
						malloc
						(loopback_ip_udp_quic_header_quic_frame_payload_length);
					memcpy (node->buf.buf,
						loopback_ip_udp_quic_header_quic_frame_payload,
						loopback_ip_udp_quic_header_quic_frame_payload_length);
					node->buf.len =
						loopback_ip_udp_quic_header_quic_frame_payload_length;
					node->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
					struct avl_node **link =
						&(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_udp_quic_header_quic_frame_buf_length =
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

						if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->
							node)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root->head) == 1)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_udp_quic_header_quic_frame_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							QUICFrameTempData->offset);
						loopback_ip_udp_quic_header_quic_frame_buf_length =
							cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc
								(loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.len =
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							memcpy (pre_buf->next->buf.buf,
								loopback_ip_udp_quic_header_quic_frame_payload,
								loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								buf_len +=
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								packet_count++;
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
							malloc
							(loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->buf.len =
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						memcpy (pre_buf->next->buf.buf,
							loopback_ip_udp_quic_header_quic_frame_payload,
							loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
					}
				}
			}
		} loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		while (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count > 0)
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
				|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
				loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
			{
				uint64_t meta =
					((struct buffer_node *)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head)->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;
					struct avl_node *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->root->head;
					avl_node_erase
						(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head,
						loopback_ip_udp_quic_header_quic_frame_bufs->root);
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			else
			{
				uint64_t meta =
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;
					struct buf_list *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			free (loopback_ip_udp_quic_header_quic_frame_buf);
		}
		if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count == 0)
			loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 0;
		return;
	}
	if ((loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID
			&& ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 1) != 0)))
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->first_is_fin =
			1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_frag;
		loopback_ip_udp_quic_header_quic_frame_payload_length =
			QUICFrameTempData->payload_len;
		loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
			|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
			loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf =
				malloc (loopback_ip_udp_quic_header_quic_frame_payload_length);
			memcpy (node->buf.buf,
				loopback_ip_udp_quic_header_quic_frame_payload,
				loopback_ip_udp_quic_header_quic_frame_payload_length);
			node->buf.len =
				loopback_ip_udp_quic_header_quic_frame_payload_length;
			node->buf.meta = QUICFrameTempData->offset;	// meta assignment
			struct avl_node **link =
				&(loopback_ip_udp_quic_header_quic_frame_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_udp_quic_header_quic_frame_buf_length =
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

				if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->node)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head) == 1)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_udp_quic_header_quic_frame_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
					loopback_ip_udp_quic_header_quic_frame_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->head->next == NULL)
			{

				loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.meta = QUICFrameTempData->offset;	//meta_data_assignment here
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					buf =
					malloc
					(loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->next =
					NULL;
				memcpy (loopback_ip_udp_quic_header_quic_frame_bufs->head->
					next->buf.buf,
					loopback_ip_udp_quic_header_quic_frame_payload,
					loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					len = loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len =
					loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >=
					loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_udp_quic_header_quic_frame_bufs->
							root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_udp_quic_header_quic_frame_buf_length =
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
							if (!loopback_ip_udp_quic_header_quic_frame_bufs->
								root->node)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head) == 1)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf =
						malloc
						(loopback_ip_udp_quic_header_quic_frame_payload_length);
					memcpy (node->buf.buf,
						loopback_ip_udp_quic_header_quic_frame_payload,
						loopback_ip_udp_quic_header_quic_frame_payload_length);
					node->buf.len =
						loopback_ip_udp_quic_header_quic_frame_payload_length;
					node->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
					struct avl_node **link =
						&(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_udp_quic_header_quic_frame_buf_length =
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

						if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->
							node)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root->head) == 1)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_udp_quic_header_quic_frame_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							QUICFrameTempData->offset);
						loopback_ip_udp_quic_header_quic_frame_buf_length =
							cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc
								(loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.len =
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							memcpy (pre_buf->next->buf.buf,
								loopback_ip_udp_quic_header_quic_frame_payload,
								loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								buf_len +=
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								packet_count++;
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
							malloc
							(loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->buf.len =
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						memcpy (pre_buf->next->buf.buf,
							loopback_ip_udp_quic_header_quic_frame_payload,
							loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
					}
				}
			}
		} loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		while (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count > 0)
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
				|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
				loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
			{
				uint64_t meta =
					((struct buffer_node *)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head)->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;
					struct avl_node *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->root->head;
					avl_node_erase
						(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head,
						loopback_ip_udp_quic_header_quic_frame_bufs->root);
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			else
			{
				uint64_t meta =
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;
					struct buf_list *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			free (loopback_ip_udp_quic_header_quic_frame_buf);
		}
		if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count == 0)
			loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 0;
		return;
	}
	return;
}

void loopback_ip_udp_quic_header_quic_frame_frag ()
{
	if ((loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID
			&& ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 1) != 0)))
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->
			receiving_fin = 1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_frag;
		loopback_ip_udp_quic_header_quic_frame_data->expect_length =
			(QUICFrameTempData->offset + QUICFrameTempData->length);
		loopback_ip_udp_quic_header_quic_frame_payload_length =
			QUICFrameTempData->payload_len;
		loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
			|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
			loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf =
				malloc (loopback_ip_udp_quic_header_quic_frame_payload_length);
			memcpy (node->buf.buf,
				loopback_ip_udp_quic_header_quic_frame_payload,
				loopback_ip_udp_quic_header_quic_frame_payload_length);
			node->buf.len =
				loopback_ip_udp_quic_header_quic_frame_payload_length;
			node->buf.meta = QUICFrameTempData->offset;	// meta assignment
			struct avl_node **link =
				&(loopback_ip_udp_quic_header_quic_frame_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_udp_quic_header_quic_frame_buf_length =
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

				if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->node)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head) == 1)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_udp_quic_header_quic_frame_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
					loopback_ip_udp_quic_header_quic_frame_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->head->next == NULL)
			{

				loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.meta = QUICFrameTempData->offset;	//meta_data_assignment here
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					buf =
					malloc
					(loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->next =
					NULL;
				memcpy (loopback_ip_udp_quic_header_quic_frame_bufs->head->
					next->buf.buf,
					loopback_ip_udp_quic_header_quic_frame_payload,
					loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					len = loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len =
					loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >=
					loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_udp_quic_header_quic_frame_bufs->
							root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_udp_quic_header_quic_frame_buf_length =
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
							if (!loopback_ip_udp_quic_header_quic_frame_bufs->
								root->node)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head) == 1)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf =
						malloc
						(loopback_ip_udp_quic_header_quic_frame_payload_length);
					memcpy (node->buf.buf,
						loopback_ip_udp_quic_header_quic_frame_payload,
						loopback_ip_udp_quic_header_quic_frame_payload_length);
					node->buf.len =
						loopback_ip_udp_quic_header_quic_frame_payload_length;
					node->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
					struct avl_node **link =
						&(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_udp_quic_header_quic_frame_buf_length =
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

						if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->
							node)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root->head) == 1)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_udp_quic_header_quic_frame_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							QUICFrameTempData->offset);
						loopback_ip_udp_quic_header_quic_frame_buf_length =
							cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc
								(loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.len =
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							memcpy (pre_buf->next->buf.buf,
								loopback_ip_udp_quic_header_quic_frame_payload,
								loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								buf_len +=
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								packet_count++;
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
							malloc
							(loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->buf.len =
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						memcpy (pre_buf->next->buf.buf,
							loopback_ip_udp_quic_header_quic_frame_payload,
							loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
					}
				}
			}
		} loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		while (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count > 0)
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
				|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
				loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
			{
				uint64_t meta =
					((struct buffer_node *)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head)->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;
					struct avl_node *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->root->head;
					avl_node_erase
						(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head,
						loopback_ip_udp_quic_header_quic_frame_bufs->root);
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			else
			{
				uint64_t meta =
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;
					struct buf_list *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			free (loopback_ip_udp_quic_header_quic_frame_buf);
		}
		if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count == 0)
			loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 0;
		return;
	}
	if ((loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID
			&& ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 1) == 0)))
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->
			receiving_normal_frag = 1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_frag;
		loopback_ip_udp_quic_header_quic_frame_payload_length =
			QUICFrameTempData->payload_len;
		loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
			|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
			loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf =
				malloc (loopback_ip_udp_quic_header_quic_frame_payload_length);
			memcpy (node->buf.buf,
				loopback_ip_udp_quic_header_quic_frame_payload,
				loopback_ip_udp_quic_header_quic_frame_payload_length);
			node->buf.len =
				loopback_ip_udp_quic_header_quic_frame_payload_length;
			node->buf.meta = QUICFrameTempData->offset;	// meta assignment
			struct avl_node **link =
				&(loopback_ip_udp_quic_header_quic_frame_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_udp_quic_header_quic_frame_buf_length =
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

				if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->node)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head) == 1)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_udp_quic_header_quic_frame_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
					loopback_ip_udp_quic_header_quic_frame_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->head->next == NULL)
			{

				loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.meta = QUICFrameTempData->offset;	//meta_data_assignment here
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					buf =
					malloc
					(loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->next =
					NULL;
				memcpy (loopback_ip_udp_quic_header_quic_frame_bufs->head->
					next->buf.buf,
					loopback_ip_udp_quic_header_quic_frame_payload,
					loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					len = loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len =
					loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >=
					loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_udp_quic_header_quic_frame_bufs->
							root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_udp_quic_header_quic_frame_buf_length =
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
							if (!loopback_ip_udp_quic_header_quic_frame_bufs->
								root->node)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head) == 1)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf =
						malloc
						(loopback_ip_udp_quic_header_quic_frame_payload_length);
					memcpy (node->buf.buf,
						loopback_ip_udp_quic_header_quic_frame_payload,
						loopback_ip_udp_quic_header_quic_frame_payload_length);
					node->buf.len =
						loopback_ip_udp_quic_header_quic_frame_payload_length;
					node->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
					struct avl_node **link =
						&(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_udp_quic_header_quic_frame_buf_length =
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

						if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->
							node)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root->head) == 1)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_udp_quic_header_quic_frame_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							QUICFrameTempData->offset);
						loopback_ip_udp_quic_header_quic_frame_buf_length =
							cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc
								(loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.len =
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							memcpy (pre_buf->next->buf.buf,
								loopback_ip_udp_quic_header_quic_frame_payload,
								loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								buf_len +=
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								packet_count++;
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
							malloc
							(loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->buf.len =
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						memcpy (pre_buf->next->buf.buf,
							loopback_ip_udp_quic_header_quic_frame_payload,
							loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
					}
				}
			}
		} loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		while (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count > 0)
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
				|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
				loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
			{
				uint64_t meta =
					((struct buffer_node *)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head)->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;
					struct avl_node *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->root->head;
					avl_node_erase
						(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head,
						loopback_ip_udp_quic_header_quic_frame_bufs->root);
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			else
			{
				uint64_t meta =
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;
					struct buf_list *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			free (loopback_ip_udp_quic_header_quic_frame_buf);
		}
		if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count == 0)
			loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 0;
		return;
	}
	if ((loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID
			&& (!(loopback_ip_udp_quic_header_quic_frame_data->expect_length ==
					0)
				|| ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
						frame_type & 1) != 0))
			&&
			!loopback_ip_udp_quic_header_quic_frame_has_hole
			(QUICFrameTempData->offset, QUICFrameTempData->payload_len,
				loopback_ip_udp_quic_header_quic_frame_instance->bufs)))
	{
		loopback_ip_udp_quic_header_quic_frame_transition_bitmap->
			receiving_all = 1;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_dump;
		loopback_ip_udp_quic_header_quic_frame_payload_length =
			QUICFrameTempData->payload_len;
		loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
			|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
			loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
		{
			struct buffer_node *node;
			struct avl_node *dup = NULL;
			node = malloc (sizeof (struct buffer_node));
			node->buf.buf =
				malloc (loopback_ip_udp_quic_header_quic_frame_payload_length);
			memcpy (node->buf.buf,
				loopback_ip_udp_quic_header_quic_frame_payload,
				loopback_ip_udp_quic_header_quic_frame_payload_length);
			node->buf.len =
				loopback_ip_udp_quic_header_quic_frame_payload_length;
			node->buf.meta = QUICFrameTempData->offset;	// meta assignment
			struct avl_node **link =
				&(loopback_ip_udp_quic_header_quic_frame_bufs->root->node);
			struct avl_node *parent = NULL;
			int hr = 1;
			while (link[0])
			{
				parent = link[0];
				loopback_ip_udp_quic_header_quic_frame_buf_length =
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

				if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->node)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				else if (COMPARE_ASC ((struct avl_node *) node,
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head) == 1)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head =
						(struct avl_node *) node;
				avl_node_link ((struct avl_node *) node, parent, link);
				avl_node_post_insert ((struct avl_node *) node,
					loopback_ip_udp_quic_header_quic_frame_bufs->root);
			}
			if (!dup)
			{
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
					loopback_ip_udp_quic_header_quic_frame_payload_length;

			}
			else
			{
				free (node->buf.buf);
				free (node);
			}
		}
		else
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->head->next == NULL)
			{

				loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
					malloc (sizeof (struct buf_list));
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.meta = QUICFrameTempData->offset;	//meta_data_assignment here
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					buf =
					malloc
					(loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->next =
					NULL;
				memcpy (loopback_ip_udp_quic_header_quic_frame_bufs->head->
					next->buf.buf,
					loopback_ip_udp_quic_header_quic_frame_payload,
					loopback_ip_udp_quic_header_quic_frame_payload_length);
				loopback_ip_udp_quic_header_quic_frame_bufs->head->next->buf.
					len = loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->buf_len =
					loopback_ip_udp_quic_header_quic_frame_payload_length;
				loopback_ip_udp_quic_header_quic_frame_bufs->packet_count++;
			}
			else
			{
				if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >=
					loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
				{
					struct buf_list *pre_buf;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					struct buffer_node *node;
					struct avl_node *dup = NULL;
					while (cur_buf != NULL)
					{
						dup = NULL;
						node = malloc (sizeof (struct buffer_node));
						node->buf = cur_buf->buf;
						struct avl_node **link =
							&(loopback_ip_udp_quic_header_quic_frame_bufs->
							root->node);
						struct avl_node *parent = NULL;
						int hr = 1;
						while (link[0])
						{
							parent = link[0];
							loopback_ip_udp_quic_header_quic_frame_buf_length =
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
							if (!loopback_ip_udp_quic_header_quic_frame_bufs->
								root->node)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							else if (COMPARE_ASC ((struct avl_node *) node,
									loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head) == 1)
								loopback_ip_udp_quic_header_quic_frame_bufs->
									root->head = (struct avl_node *) node;
							avl_node_link ((struct avl_node *) node, parent,
								link);
							avl_node_post_insert ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root);
						}
						pre_buf = cur_buf;
						cur_buf = cur_buf->next;
						free (pre_buf);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						NULL;
					node = malloc (sizeof (struct buffer_node));
					node->buf.buf =
						malloc
						(loopback_ip_udp_quic_header_quic_frame_payload_length);
					memcpy (node->buf.buf,
						loopback_ip_udp_quic_header_quic_frame_payload,
						loopback_ip_udp_quic_header_quic_frame_payload_length);
					node->buf.len =
						loopback_ip_udp_quic_header_quic_frame_payload_length;
					node->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
					struct avl_node **link =
						&(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						node);
					struct avl_node *parent = NULL;
					int hr = 1;
					dup = NULL;
					while (link[0])
					{
						parent = link[0];
						loopback_ip_udp_quic_header_quic_frame_buf_length =
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

						if (!loopback_ip_udp_quic_header_quic_frame_bufs->root->
							node)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						else if (COMPARE_ASC ((struct avl_node *) node,
								loopback_ip_udp_quic_header_quic_frame_bufs->
								root->head) == 1)
							loopback_ip_udp_quic_header_quic_frame_bufs->root->
								head = (struct avl_node *) node;
						avl_node_link ((struct avl_node *) node, parent, link);
						avl_node_post_insert ((struct avl_node *) node,
							loopback_ip_udp_quic_header_quic_frame_bufs->root);
					}
					if (!dup)
					{
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;

					}
					else
					{
						free (node);
					}
					loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 1;
				}
				else
				{
					struct buf_list *pre_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head;
					struct buf_list *cur_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					char inserted = 0;
					while (cur_buf != NULL)
					{
						int hr =
							LIST_COMPARE_ASC (cur_buf->buf.meta,
							QUICFrameTempData->offset);
						loopback_ip_udp_quic_header_quic_frame_buf_length =
							cur_buf->buf.len;
						uint64_t meta = cur_buf->buf.meta;
						if (hr == 1)
						{

							pre_buf->next = malloc (sizeof (struct buf_list));
							pre_buf->next->buf.buf =
								malloc
								(loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.len =
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							memcpy (pre_buf->next->buf.buf,
								loopback_ip_udp_quic_header_quic_frame_payload,
								loopback_ip_udp_quic_header_quic_frame_payload_length);
							pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
							pre_buf->next->next = cur_buf;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								buf_len +=
								loopback_ip_udp_quic_header_quic_frame_payload_length;
							loopback_ip_udp_quic_header_quic_frame_bufs->
								packet_count++;
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
							malloc
							(loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->buf.len =
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						memcpy (pre_buf->next->buf.buf,
							loopback_ip_udp_quic_header_quic_frame_payload,
							loopback_ip_udp_quic_header_quic_frame_payload_length);
						pre_buf->next->next = NULL;
						pre_buf->next->buf.meta = QUICFrameTempData->offset;	//meta_data assignment here
						loopback_ip_udp_quic_header_quic_frame_bufs->buf_len +=
							loopback_ip_udp_quic_header_quic_frame_payload_length;
						loopback_ip_udp_quic_header_quic_frame_bufs->
							packet_count++;
					}
				}
			}
		} loopback_ip_udp_quic_header_quic_frame_bufs =
			loopback_ip_udp_quic_header_quic_frame_instance->bufs;
		while (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count > 0)
		{
			if (loopback_ip_udp_quic_header_quic_frame_bufs->is_tree
				|| loopback_ip_udp_quic_header_quic_frame_bufs->packet_count >
				loopback_ip_udp_quic_header_quic_frame_THRESHOLD)
			{
				uint64_t meta =
					((struct buffer_node *)
					loopback_ip_udp_quic_header_quic_frame_bufs->root->head)->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						((struct buffer_node *)
						loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head)->buf.len;
					struct avl_node *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->root->head;
					avl_node_erase
						(loopback_ip_udp_quic_header_quic_frame_bufs->root->
						head,
						loopback_ip_udp_quic_header_quic_frame_bufs->root);
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			else
			{
				uint64_t meta =
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next->
					buf.meta;
				if ((meta ==
						loopback_ip_udp_quic_header_quic_frame_data->
						accept_length))
				{
					loopback_ip_udp_quic_header_quic_frame_buf =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.buf;
					loopback_ip_udp_quic_header_quic_frame_buf_length =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;

					loopback_ip_udp_quic_header_quic_frame_bufs->buf_len -=
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->buf.len;
					struct buf_list *head =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->head->next =
						loopback_ip_udp_quic_header_quic_frame_bufs->head->
						next->next;
					loopback_ip_udp_quic_header_quic_frame_bufs->packet_count--;
					free (head);
					loopback_ip_udp_quic_header_quic_frame_data->accept_length =
						(loopback_ip_udp_quic_header_quic_frame_data->
						accept_length +
						loopback_ip_udp_quic_header_quic_frame_buf_length);
				}
				else
				{
					break;
				}
			}
			free (loopback_ip_udp_quic_header_quic_frame_buf);
		}
		if (loopback_ip_udp_quic_header_quic_frame_bufs->packet_count == 0)
			loopback_ip_udp_quic_header_quic_frame_bufs->is_tree = 0;
		return;
	}
	return;
}

void loopback_ip_udp_quic_header_quic_frame_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
		loopback_ip_udp_quic_header_quic_frame_QUICFrame = 1;
	loopback_ip_udp_quic_header_quic_frame_QUICFrame =
		(struct loopback_ip_udp_quic_header_quic_frame_QUICFrame_t *) (payload +
		cur_pos);
	cur_pos += 1;
	if ((((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) == 0)
			&& (loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				2)))
	{
		loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose = 1;
		loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0 =
			(struct
			loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0_t
			*) (payload + cur_pos);
		cur_pos += 3;
		loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_1->
			reason_phrase = payload + cur_pos;
		cur_pos +=
			loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0->
			reason_phrase_length;
	}
	if ((((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) == 0)
			&& (loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				13)))
	{
		loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICACK = 1;
		loopback_ip_udp_quic_header_quic_frame_QUICACK_0 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICACK_0_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICACK_1->last_ack_extra =
			payload + cur_pos;
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->
					last_ack_upper + 0)) - 1);
		loopback_ip_udp_quic_header_quic_frame_QUICACK_2 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICACK_2_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICACK_3->ack_delay_extra =
			payload + cur_pos;
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->
					ack_delay_upper + 0)) - 1);
		loopback_ip_udp_quic_header_quic_frame_QUICACK_4 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICACK_4_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICACK_5->
			ack_block_count_extra = payload + cur_pos;
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
					ack_block_count_upper + 0)) - 1);
		loopback_ip_udp_quic_header_quic_frame_QUICACK_6 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICACK_6_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICACK_7->ack_block_extra =
			payload + cur_pos;
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->
					ack_block_upper + 0)) - 1);
	}
	if ((((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) == 0)
			&& (loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				4)))
	{
		loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICMaxData = 1;
		loopback_ip_udp_quic_header_quic_frame_QUICMaxData =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICMaxData_t
			*) (payload + cur_pos);
		cur_pos += 1;
	}
	if ((((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) == 0)
			&& (loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				5)))
	{
		loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData = 1;
		loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_1->
			max_data_stream_id_extra =
			extract_field (payload, cur_pos,
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0->
						max_data_stream_id_upper + 0)) - 1));
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0->
					max_data_stream_id_upper + 0)) - 1);
		loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2 =
			(struct loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2_t
			*) (payload + cur_pos);
		cur_pos += 1;
		loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_3->
			max_stream_data_extra = payload + cur_pos;
		cur_pos +=
			((1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2->
					max_stream_data_upper + 0)) - 1);
	}
	if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type & 248) ==
			16))
	{
		loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID = 1;
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID =
			(struct
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID_t
			*) (payload + cur_pos);
		cur_pos += 1;
		if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->
					stream_id & 192) != 0))
		{
			loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail
				= 1;
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0->
				stream_id_tail = payload + cur_pos;
			cur_pos +=
				((1 <<
					((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6)) - 1);
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 4) != 0))
		{
			loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset =
				1;
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset =
				(struct
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset_t
				*) (payload + cur_pos);
			cur_pos += 1;
			if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->
						frame_offset & 192) != 0))
			{
				loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail
					= 1;
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->
					frame_offset_tail =
					extract_field (payload, cur_pos,
					((1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6)) - 1));
				cur_pos +=
					((1 <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6)) - 1);
			}
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 2) != 0))
		{
			loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength =
				1;
			loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength =
				(struct
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength_t
				*) (payload + cur_pos);
			cur_pos += 1;
			if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
						frame_length & 192) != 0))
			{
				loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail
					= 1;
				loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->
					frame_length_tail =
					extract_field (payload, cur_pos,
					((1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6)) - 1));
				cur_pos +=
					((1 <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6)) - 1);
			}
		}
	}
	loopback_ip_udp_quic_header_quic_frame_payload_length -= cur_pos;
	loopback_ip_udp_quic_header_quic_frame_payload += cur_pos;
	loopback_ip_udp_quic_header_quic_frame_select->src_src_addr =
		loopback_ip_ip_hdr->src_addr;
	loopback_ip_udp_quic_header_quic_frame_select->src_src_port =
		loopback_ip_udp_udp_hdr->src_port;
	loopback_ip_udp_quic_header_quic_frame_select->src_stream_id =
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->
		stream_id;
	loopback_ip_udp_quic_header_quic_frame_select->src_stream_id_tail =
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0->
		stream_id_tail;
	loopback_ip_udp_quic_header_quic_frame_select->src_length_stream_id_tail =
		((1 <<
			((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->
					stream_id & 192) >> 6)) - 1);
	loopback_ip_udp_quic_header_quic_frame_select->dst_dst_addr =
		loopback_ip_ip_hdr->dst_addr;
	loopback_ip_udp_quic_header_quic_frame_select->dst_dst_port =
		loopback_ip_udp_udp_hdr->dst_port;
	loopback_ip_udp_quic_header_quic_frame_select->dst_stream_id =
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->
		stream_id;
	loopback_ip_udp_quic_header_quic_frame_select->dst_stream_id_tail =
		loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamIDTail_0->
		stream_id_tail;
	loopback_ip_udp_quic_header_quic_frame_select->dst_length_stream_id_tail =
		((1 <<
			((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->
					stream_id & 192) >> 6)) - 1);
}

void loopback_ip_udp_quic_header_quic_frame_selector (struct timeval *now)
{
	if (!((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
				frame_type & 240) != 0))
	{
		loopback_ip_udp_quic_header_quic_frame_instance =
			loopback_ip_udp_quic_header_quic_frame_fake_instance;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_dump;
		loopback_ip_udp_quic_header_quic_frame_instance->
			loopback_ip_udp_quic_header_quic_frame_data = NULL;
		loopback_ip_udp_quic_header_quic_frame_instance->bufs = NULL;
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) == 0))
		{
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					14))
			{
				QUICFrameTempData->length = 9;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					13))
			{
				if ((loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
						ack_block_count_lower == 0))
				{
					QUICFrameTempData->length =
						(((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1);
				}
				if ((!loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
						ack_block_count_upper
						&& (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
							ack_block_count_lower != 0)))
				{
					QUICFrameTempData->length =
						((((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1) + loopback_ip_udp_quic_header_quic_frame_payload_length);
				}
				if (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
					ack_block_count_upper)
				{
					QUICFrameTempData->length =
						((((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1) + loopback_ip_udp_quic_header_quic_frame_payload_length);
				}
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					4))
			{
				QUICFrameTempData->length =
					(1 +
					(1 << ((loopback_ip_udp_quic_header_quic_frame_QUICMaxData->
								maximum_data & 192) >> 6)));
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					15))
			{
				QUICFrameTempData->length = 9;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					0))
			{
				QUICFrameTempData->length =
					(1 + loopback_ip_udp_quic_header_quic_frame_payload_length);
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					7))
			{
				QUICFrameTempData->length = 1;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					6))
			{
				QUICFrameTempData->length = 3;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					12))
			{
				QUICFrameTempData->length = 4;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					5))
			{
				QUICFrameTempData->length =
					(((1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2->max_stream_data_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0->max_data_stream_id_upper + 0))) + 1);
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					1))
			{
				QUICFrameTempData->length = 5;
			}
			if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
					2))
			{
				QUICFrameTempData->length =
					(4 +
					loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0->
					reason_phrase_length);
			}
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 240) != 0))
		{
			if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
						frame_type & 4) == 0))
			{
				QUICFrameTempData->offset = 0;
			}
			if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
						frame_type & 4) != 0))
			{
				if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) == 0))
				{
					QUICFrameTempData->offset =
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->
						frame_offset;
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 1))
				{
					QUICFrameTempData->offset =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 2))
				{
					QUICFrameTempData->offset =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 3))
				{
					QUICFrameTempData->offset =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
				}
			}
			if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
						frame_type & 2) == 0))
			{
				QUICFrameTempData->length = 0;
			}
			if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
						frame_type & 2) != 0))
			{
				if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) == 0))
				{
					QUICFrameTempData->payload_len =
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
						frame_length;
					QUICFrameTempData->length =
						(
						(loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
							frame_length +
							(1 <<
								((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 2);
					if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
					{
						QUICFrameTempData->length =
							((QUICFrameTempData->length +
								1) <<
							((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
					}
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 1))
				{
					QUICFrameTempData->payload_len =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
					QUICFrameTempData->length =
						(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 3);
					if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
					{
						QUICFrameTempData->length =
							((QUICFrameTempData->length +
								1) <<
							((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
					}
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 2))
				{
					QUICFrameTempData->payload_len =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
					QUICFrameTempData->length =
						(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 5);
					if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
					{
						QUICFrameTempData->length =
							((QUICFrameTempData->length +
								1) <<
							((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
					}
				}
				if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 3))
				{
					QUICFrameTempData->payload_len =
						(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
					QUICFrameTempData->length =
						(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 9);
					if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
						loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
					{
						QUICFrameTempData->length =
							((QUICFrameTempData->length +
								1) <<
							((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
					}
				}
			}
		}
		return;
	}
	uint32_t hash =
		loopback_ip_udp_quic_header_quic_frame_hash
		(loopback_ip_udp_quic_header_quic_frame_select);
	loopback_ip_udp_quic_header_quic_frame_instance =
		tommy_hashdyn_search (&loopback_ip_udp_quic_header_quic_frame_hashtable,
		loopback_ip_udp_quic_header_quic_frame_compare,
		loopback_ip_udp_quic_header_quic_frame_select, hash);
	if (!loopback_ip_udp_quic_header_quic_frame_instance)
	{
		loopback_ip_udp_quic_header_quic_frame_instance =
			(struct loopback_ip_udp_quic_header_quic_frame_instance_t *)
			malloc (sizeof (struct
				loopback_ip_udp_quic_header_quic_frame_instance_t));
		memset (loopback_ip_udp_quic_header_quic_frame_instance, 0,
			sizeof (struct loopback_ip_udp_quic_header_quic_frame_select_t));
		loopback_ip_udp_quic_header_quic_frame_data =
			(loopback_ip_udp_quic_header_quic_frame_data_t *)
			malloc (sizeof (loopback_ip_udp_quic_header_quic_frame_data_t));
		loopback_ip_udp_quic_header_quic_frame_data->accept_length = 0;
		loopback_ip_udp_quic_header_quic_frame_instance->
			loopback_ip_udp_quic_header_quic_frame_select =
			*loopback_ip_udp_quic_header_quic_frame_select;
		loopback_ip_udp_quic_header_quic_frame_instance->
			loopback_ip_udp_quic_header_quic_frame_data =
			loopback_ip_udp_quic_header_quic_frame_data;
		loopback_ip_udp_quic_header_quic_frame_instance->state =
			loopback_ip_udp_quic_header_quic_frame_dump;
		loopback_ip_udp_quic_header_quic_frame_instance->rec_ptr =
			timer_update (&loopback_ip_udp_quic_header_quic_frame_list,
			loopback_ip_udp_quic_header_quic_frame_instance, NULL, now);
		init_buf_list (&loopback_ip_udp_quic_header_quic_frame_instance->bufs);
		hash =
			loopback_ip_udp_quic_header_quic_frame_hash
			(loopback_ip_udp_quic_header_quic_frame_select);
		tommy_hashdyn_insert (&loopback_ip_udp_quic_header_quic_frame_hashtable,
			&loopback_ip_udp_quic_header_quic_frame_instance->node,
			loopback_ip_udp_quic_header_quic_frame_instance, hash);
	}
	else
	{
		loopback_ip_udp_quic_header_quic_frame_data =
			loopback_ip_udp_quic_header_quic_frame_instance->
			loopback_ip_udp_quic_header_quic_frame_data;
		loopback_ip_udp_quic_header_quic_frame_instance->rec_ptr =
			timer_update (&loopback_ip_udp_quic_header_quic_frame_list,
			loopback_ip_udp_quic_header_quic_frame_instance,
			loopback_ip_udp_quic_header_quic_frame_instance->rec_ptr, now);
	}
	if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type & 240) ==
			0))
	{
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				14))
		{
			QUICFrameTempData->length = 9;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				13))
		{
			if ((loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
					ack_block_count_lower == 0))
			{
				QUICFrameTempData->length =
					(((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1);
			}
			if ((!loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
					ack_block_count_upper
					&& (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
						ack_block_count_lower != 0)))
			{
				QUICFrameTempData->length =
					((((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1) + loopback_ip_udp_quic_header_quic_frame_payload_length);
			}
			if (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->
				ack_block_count_upper)
			{
				QUICFrameTempData->length =
					((((((1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_0->last_ack_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_2->ack_delay_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_4->ack_block_count_upper + 0))) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICACK_6->ack_block_upper + 0))) + 1) + loopback_ip_udp_quic_header_quic_frame_payload_length);
			}
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 4))
		{
			QUICFrameTempData->length =
				(1 +
				(1 << ((loopback_ip_udp_quic_header_quic_frame_QUICMaxData->
							maximum_data & 192) >> 6)));
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				15))
		{
			QUICFrameTempData->length = 9;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 0))
		{
			QUICFrameTempData->length =
				(1 + loopback_ip_udp_quic_header_quic_frame_payload_length);
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 7))
		{
			QUICFrameTempData->length = 1;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 6))
		{
			QUICFrameTempData->length = 3;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type ==
				12))
		{
			QUICFrameTempData->length = 4;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 5))
		{
			QUICFrameTempData->length =
				(((1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_2->max_stream_data_upper + 0)) + (1 << (loopback_ip_udp_quic_header_quic_frame_QUICMaxStreamData_0->max_data_stream_id_upper + 0))) + 1);
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 1))
		{
			QUICFrameTempData->length = 5;
		}
		if ((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type == 2))
		{
			QUICFrameTempData->length =
				(4 +
				loopback_ip_udp_quic_header_quic_frame_QUICConnectionClose_0->
				reason_phrase_length);
		}
	}
	if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->frame_type & 240) !=
			0))
	{
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 4) == 0))
		{
			QUICFrameTempData->offset = 0;
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 4) != 0))
		{
			if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->
						frame_offset & 192) == 0))
			{
				QUICFrameTempData->offset =
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->
					frame_offset;
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 1))
			{
				QUICFrameTempData->offset =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 2))
			{
				QUICFrameTempData->offset =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6) == 3))
			{
				QUICFrameTempData->offset =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffsetTail_0->frame_offset_tail);
			}
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 2) == 0))
		{
			QUICFrameTempData->length = 0;
		}
		if (((loopback_ip_udp_quic_header_quic_frame_QUICFrame->
					frame_type & 2) != 0))
		{
			if (((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
						frame_length & 192) == 0))
			{
				QUICFrameTempData->payload_len =
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
					frame_length;
				QUICFrameTempData->length =
					(
					(loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->
						frame_length +
						(1 <<
							((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 2);
				if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
				{
					QUICFrameTempData->length =
						((QUICFrameTempData->length +
							1) <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
				}
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 1))
			{
				QUICFrameTempData->payload_len =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
				QUICFrameTempData->length =
					(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 8) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 3);
				if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
				{
					QUICFrameTempData->length =
						((QUICFrameTempData->length +
							1) <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
				}
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 2))
			{
				QUICFrameTempData->payload_len =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
				QUICFrameTempData->length =
					(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 16) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 5);
				if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
				{
					QUICFrameTempData->length =
						((QUICFrameTempData->length +
							1) <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
				}
			}
			if ((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 192) >> 6) == 3))
			{
				QUICFrameTempData->payload_len =
					(((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail);
				QUICFrameTempData->length =
					(((((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLength->frame_length & 63) << 24) + loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameLengthTail_0->frame_length_tail) + (1 << ((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameStreamID->stream_id & 192) >> 6))) + 9);
				if (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap->
					loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset)
				{
					QUICFrameTempData->length =
						((QUICFrameTempData->length +
							1) <<
						((loopback_ip_udp_quic_header_quic_frame_QUICStreamFrameOffset->frame_offset & 192) >> 6));
				}
			}
		}
	}
}

void loopback_ip_udp_quic_header_quic_frame_parse (u_char * payload,
	uint32_t length, struct timeval *now)
{
	printf ("this is quic_frame layer\n");
	printf ("packet length is %d\n", length);
	printf ("------------packet end------------\n");
	static uint64_t ts = 0;
	static uint64_t int_now;
	loopback_ip_udp_quic_header_quic_frame_payload = payload;
	loopback_ip_udp_quic_header_quic_frame_payload_length = length;
	loopback_ip_udp_quic_header_quic_frame_data_assignment (payload);
	loopback_ip_udp_quic_header_quic_frame_selector (now);
	loopback_ip_udp_quic_header_quic_frame_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet
			(&loopback_ip_udp_quic_header_quic_frame_list,
			&loopback_ip_udp_quic_header_quic_frame_gap,
			&loopback_ip_udp_quic_header_quic_frame_hashtable,
			offsetof (struct loopback_ip_udp_quic_header_quic_frame_instance_t,
				node), loopback_ip_udp_quic_header_quic_frame_free, now);
		ts = int_now;
	}
	memset (loopback_ip_udp_quic_header_quic_frame_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_quic_frame_rubik_bitmap_t));
	memset (loopback_ip_udp_quic_header_quic_frame_transition_bitmap, 0,
		sizeof (struct
			loopback_ip_udp_quic_header_quic_frame_transition_bitmap_t));
	if (loopback_ip_udp_quic_header_quic_frame_has_buf)
	{
		free (loopback_ip_udp_quic_header_quic_frame_buf);
		loopback_ip_udp_quic_header_quic_frame_has_buf = 0;
	}
}
