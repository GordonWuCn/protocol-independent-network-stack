#include "loopback_ip_udp_quic_header_t.h"
#include "buf.h"
#include "time.h"
#include "tommyds/tommy.h"
#include "timer.h"
#include "extern_ref.h"
#include "extract_field.h"
#include "avlmini.h"
struct loopback_ip_udp_quic_header_instance_t
	*loopback_ip_udp_quic_header_instance;
struct loopback_ip_udp_quic_header_instance_t
	*loopback_ip_udp_quic_header_instance_reverse;
struct loopback_ip_udp_quic_header_select_t *loopback_ip_udp_quic_header_select;
struct loopback_ip_udp_quic_header_select_t
	*loopback_ip_udp_quic_header_select_reverse;
struct loopback_ip_udp_quic_header_instance_t
	*loopback_ip_udp_quic_header_fake_instance;
struct loopback_ip_udp_quic_header_instance_t
	*loopback_ip_udp_quic_header_fake_instance_reverse;
tommy_hashdyn loopback_ip_udp_quic_header_hashtable;
struct timer loopback_ip_udp_quic_header_list;
struct timeval loopback_ip_udp_quic_header_gap;
struct loopback_ip_udp_quic_header_QUICHeaderFormPacketType_t
	*loopback_ip_udp_quic_header_QUICHeaderFormPacketType;
struct loopback_ip_udp_quic_header_QUICLongHeaderPart1_t
	*loopback_ip_udp_quic_header_QUICLongHeaderPart1;
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0_t
	*loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0;
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0_t
	*loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0;
struct loopback_ip_udp_quic_header_QUICLongHeaderPart2_t
	*loopback_ip_udp_quic_header_QUICLongHeaderPart2;
struct loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0_t
	*loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0;
struct loopback_ip_udp_quic_header_QUICLongHeaderPart3_t
	*loopback_ip_udp_quic_header_QUICLongHeaderPart3;
struct loopback_ip_udp_quic_header_QUICShortHeader_0_t
	*loopback_ip_udp_quic_header_QUICShortHeader_0;
struct loopback_ip_udp_quic_header_QUICShortHeader_1_t
	*loopback_ip_udp_quic_header_QUICShortHeader_1;
char loopback_ip_udp_quic_header_has_buf = 0;
u_char *loopback_ip_udp_quic_header_buf;
int loopback_ip_udp_quic_header_buf_length;
u_char *loopback_ip_udp_quic_header_payload;
int loopback_ip_udp_quic_header_payload_length;
struct loopback_ip_udp_quic_header_rubik_bitmap_t
	*loopback_ip_udp_quic_header_rubik_bitmap;
struct loopback_ip_udp_quic_header_transition_bitmap_t
	*loopback_ip_udp_quic_header_transition_bitmap;
struct buf_queue *loopback_ip_udp_quic_header_bufs;
void loopback_ip_udp_quic_header_init ()
{
	tommy_hashdyn_init (&loopback_ip_udp_quic_header_hashtable);
	loopback_ip_udp_quic_header_gap.tv_sec = 10;
	loopback_ip_udp_quic_header_gap.tv_usec = 0;
	loopback_ip_udp_quic_header_list.head = NULL;
	loopback_ip_udp_quic_header_list.tail = NULL;
	loopback_ip_udp_quic_header_instance = NULL;
	loopback_ip_udp_quic_header_fake_instance =
		malloc (sizeof (struct loopback_ip_udp_quic_header_instance_t));
	loopback_ip_udp_quic_header_fake_instance->is_active_part =
		malloc (sizeof (char));
	*(loopback_ip_udp_quic_header_fake_instance->is_active_part) = 1;
	loopback_ip_udp_quic_header_fake_instance->stand = 0;
	loopback_ip_udp_quic_header_fake_instance_reverse =
		malloc (sizeof (struct loopback_ip_udp_quic_header_instance_t));
	loopback_ip_udp_quic_header_fake_instance_reverse->is_active_part =
		loopback_ip_udp_quic_header_fake_instance->is_active_part;
	loopback_ip_udp_quic_header_fake_instance_reverse->stand = 1;
	loopback_ip_udp_quic_header_select =
		malloc (sizeof (struct loopback_ip_udp_quic_header_select_t));
	loopback_ip_udp_quic_header_select_reverse =
		malloc (sizeof (struct loopback_ip_udp_quic_header_select_t));
	memset (loopback_ip_udp_quic_header_select, 0,
		sizeof (struct loopback_ip_udp_quic_header_select_t));
	memset (loopback_ip_udp_quic_header_select_reverse, 0,
		sizeof (struct loopback_ip_udp_quic_header_select_t));
	loopback_ip_udp_quic_header_rubik_bitmap =
		malloc (sizeof (struct loopback_ip_udp_quic_header_rubik_bitmap_t));
	loopback_ip_udp_quic_header_transition_bitmap =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_transition_bitmap_t));
	memset (loopback_ip_udp_quic_header_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_rubik_bitmap_t));
	memset (loopback_ip_udp_quic_header_transition_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_transition_bitmap_t));
	loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0_t));
	loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0_t));
	loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0_t));
	loopback_ip_udp_quic_header_QUICShortHeader_0 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_QUICShortHeader_0_t));
	loopback_ip_udp_quic_header_QUICShortHeader_1 =
		malloc (sizeof (struct
			loopback_ip_udp_quic_header_QUICShortHeader_1_t));
}

char loopback_ip_udp_quic_header_has_hole (uint64_t meta, int length,
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

uint32_t loopback_ip_udp_quic_header_hash (void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_udp_quic_header_select_t);
	return tommy_hash_u32 (0, obj, size);
}

int loopback_ip_udp_quic_header_compare (const void *arg, const void *obj)
{
	uint64_t size = sizeof (struct loopback_ip_udp_quic_header_select_t);
	return memcmp (arg, obj, size);
}

void loopback_ip_udp_quic_header_destroy (void)
{
	free_buf_list (loopback_ip_udp_quic_header_instance->bufs);
	free_buf_list (loopback_ip_udp_quic_header_instance_reverse->bufs);
	tommy_hashdyn_remove_existing (&loopback_ip_udp_quic_header_hashtable,
		&loopback_ip_udp_quic_header_instance->node);
	tommy_hashdyn_remove_existing (&loopback_ip_udp_quic_header_hashtable,
		&loopback_ip_udp_quic_header_instance_reverse->node);
	if (loopback_ip_udp_quic_header_instance->time_record_leader)
		deregister_timer (&loopback_ip_udp_quic_header_list,
			loopback_ip_udp_quic_header_instance->rec_ptr);
	else
		deregister_timer (&loopback_ip_udp_quic_header_list,
			loopback_ip_udp_quic_header_instance_reverse->rec_ptr);
	free (loopback_ip_udp_quic_header_instance->is_active_part);
	free (loopback_ip_udp_quic_header_instance);
	free (loopback_ip_udp_quic_header_instance_reverse);
}

void loopback_ip_udp_quic_header_free (void *inst)
{
	struct loopback_ip_udp_quic_header_instance_t *reverse =
		((struct loopback_ip_udp_quic_header_instance_t *) inst)->pair_instance;
	free_buf_list (reverse->bufs);
	free (reverse->is_active_part);
	tommy_hashdyn_remove_existing (&loopback_ip_udp_quic_header_hashtable,
		&reverse->node);
	free (reverse);
	free_buf_list (((struct loopback_ip_udp_quic_header_instance_t *) inst)->
		bufs);
}

static void loopback_ip_udp_quic_header_start (void);
void loopback_ip_udp_quic_header_start ()
{
	if (*(loopback_ip_udp_quic_header_instance->
			is_active_part) ^ loopback_ip_udp_quic_header_instance->stand)
	{
		if (1)
		{
			loopback_ip_udp_quic_header_transition_bitmap->loop = 1;
			loopback_ip_udp_quic_header_instance->state =
				loopback_ip_udp_quic_header_start;
			loopback_ip_udp_quic_header_instance_reverse->state =
				loopback_ip_udp_quic_header_instance->state;
			loopback_ip_udp_quic_header_buf =
				loopback_ip_udp_quic_header_payload;
			loopback_ip_udp_quic_header_buf_length =
				loopback_ip_udp_quic_header_payload_length;
			return;
		}
		return;
	}
	if (!(*(loopback_ip_udp_quic_header_instance->
				is_active_part) ^ loopback_ip_udp_quic_header_instance->stand))
	{
		if (1)
		{
			loopback_ip_udp_quic_header_transition_bitmap->loop = 1;
			loopback_ip_udp_quic_header_instance->state =
				loopback_ip_udp_quic_header_start;
			loopback_ip_udp_quic_header_instance_reverse->state =
				loopback_ip_udp_quic_header_instance->state;
			loopback_ip_udp_quic_header_buf =
				loopback_ip_udp_quic_header_payload;
			loopback_ip_udp_quic_header_buf_length =
				loopback_ip_udp_quic_header_payload_length;
			return;
		}
		return;
	}
}

void loopback_ip_udp_quic_header_data_assignment (u_char * payload)
{
	int cur_pos = 0;
	char any_parse = 1;
	loopback_ip_udp_quic_header_rubik_bitmap->
		loopback_ip_udp_quic_header_QUICHeaderFormPacketType = 1;
	loopback_ip_udp_quic_header_QUICHeaderFormPacketType =
		(struct loopback_ip_udp_quic_header_QUICHeaderFormPacketType_t
		*) (payload + cur_pos);
	cur_pos += 1;
	if (((loopback_ip_udp_quic_header_QUICHeaderFormPacketType->
				header_form_packet_type & 128) != 0))
	{
		loopback_ip_udp_quic_header_rubik_bitmap->
			loopback_ip_udp_quic_header_QUICLongHeaderPart1 = 1;
		loopback_ip_udp_quic_header_QUICLongHeaderPart1 =
			(struct loopback_ip_udp_quic_header_QUICLongHeaderPart1_t
			*) (payload + cur_pos);
		cur_pos += 5;
		loopback_ip_udp_quic_header_QUICLongHeaderPart1->version =
			ntohl (loopback_ip_udp_quic_header_QUICLongHeaderPart1->version);
		if (((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
					dst_src_conn_id_len & 240) != 0))
		{
			loopback_ip_udp_quic_header_rubik_bitmap->
				loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID = 1;
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalDstConnID_0->
				dst_conn_id =
				extract_field (payload, cur_pos,
				(((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
							dst_src_conn_id_len & 240) >> 4) + 3));
			cur_pos +=
				(((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
						dst_src_conn_id_len & 240) >> 4) + 3);
		}
		if (((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
					dst_src_conn_id_len & 15) != 0))
		{
			loopback_ip_udp_quic_header_rubik_bitmap->
				loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID = 1;
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalSrcConnID_0->
				src_conn_id =
				extract_field (payload, cur_pos,
				((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
						dst_src_conn_id_len & 15) + 3));
			cur_pos +=
				((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
					dst_src_conn_id_len & 15) + 3);
		}
		loopback_ip_udp_quic_header_rubik_bitmap->
			loopback_ip_udp_quic_header_QUICLongHeaderPart2 = 1;
		loopback_ip_udp_quic_header_QUICLongHeaderPart2 =
			(struct loopback_ip_udp_quic_header_QUICLongHeaderPart2_t
			*) (payload + cur_pos);
		cur_pos += 1;
		if (((loopback_ip_udp_quic_header_QUICLongHeaderPart2->
					payload_length_first_byte & 192) != 0))
		{
			loopback_ip_udp_quic_header_rubik_bitmap->
				loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail
				= 1;
			loopback_ip_udp_quic_header_QUICLongHeaderOptionalPayloadLengthTail_0->
				payload_length_tail =
				extract_field (payload, cur_pos,
				((1 << ((loopback_ip_udp_quic_header_QUICLongHeaderPart2->
								payload_length_first_byte & 192) >> 6)) - 1));
			cur_pos +=
				((1 << ((loopback_ip_udp_quic_header_QUICLongHeaderPart2->
							payload_length_first_byte & 192) >> 6)) - 1);
		}
		loopback_ip_udp_quic_header_rubik_bitmap->
			loopback_ip_udp_quic_header_QUICLongHeaderPart3 = 1;
		loopback_ip_udp_quic_header_QUICLongHeaderPart3 =
			(struct loopback_ip_udp_quic_header_QUICLongHeaderPart3_t
			*) (payload + cur_pos);
		cur_pos += 4;
		loopback_ip_udp_quic_header_QUICLongHeaderPart3->packet_number =
			ntohl (loopback_ip_udp_quic_header_QUICLongHeaderPart3->
			packet_number);
	}
	if (((loopback_ip_udp_quic_header_QUICHeaderFormPacketType->
				header_form_packet_type & 128) == 0))
	{
		loopback_ip_udp_quic_header_rubik_bitmap->
			loopback_ip_udp_quic_header_QUICShortHeader = 1;
		loopback_ip_udp_quic_header_QUICShortHeader_0->dst_conn_id =
			extract_field (payload, cur_pos,
			loopback_ip_udp_data->dst_conn_id_len);
		cur_pos += loopback_ip_udp_data->dst_conn_id_len;
		loopback_ip_udp_quic_header_QUICShortHeader_1 =
			(struct loopback_ip_udp_quic_header_QUICShortHeader_1_t *) (payload
			+ cur_pos);
		cur_pos += 1;
	}
	loopback_ip_udp_quic_header_payload_length -= cur_pos;
	loopback_ip_udp_quic_header_payload += cur_pos;
	loopback_ip_udp_quic_header_select->src_src_addr =
		loopback_ip_ip_hdr->src_addr;
	loopback_ip_udp_quic_header_select->src_src_port =
		loopback_ip_udp_udp_hdr->src_port;
	loopback_ip_udp_quic_header_select->dst_dst_addr =
		loopback_ip_ip_hdr->dst_addr;
	loopback_ip_udp_quic_header_select->dst_dst_port =
		loopback_ip_udp_udp_hdr->dst_port;
	loopback_ip_udp_quic_header_select_reverse->src_src_addr =
		loopback_ip_ip_hdr->dst_addr;
	loopback_ip_udp_quic_header_select_reverse->src_src_port =
		loopback_ip_udp_udp_hdr->dst_port;
	loopback_ip_udp_quic_header_select_reverse->dst_dst_addr =
		loopback_ip_ip_hdr->src_addr;
	loopback_ip_udp_quic_header_select_reverse->dst_dst_port =
		loopback_ip_udp_udp_hdr->src_port;
}

void loopback_ip_udp_quic_header_selector (struct timeval *now)
{
	if (!(1))
	{
		loopback_ip_udp_quic_header_instance =
			loopback_ip_udp_quic_header_fake_instance;
		loopback_ip_udp_quic_header_instance_reverse =
			loopback_ip_udp_quic_header_fake_instance_reverse;
		loopback_ip_udp_quic_header_instance->state =
			loopback_ip_udp_quic_header_start;
		loopback_ip_udp_quic_header_instance_reverse->state =
			loopback_ip_udp_quic_header_start;
		loopback_ip_udp_quic_header_instance->bufs = NULL;
		loopback_ip_udp_quic_header_instance_reverse->bufs = NULL;
		if (loopback_ip_udp_quic_header_rubik_bitmap->
			loopback_ip_udp_quic_header_QUICLongHeaderPart1)
		{
			loopback_ip_udp_data->dst_conn_id_len =
				(((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
						dst_src_conn_id_len & 240) >> 4) + 3);
		}
		return;
	}
	uint32_t hash =
		loopback_ip_udp_quic_header_hash (loopback_ip_udp_quic_header_select);
	loopback_ip_udp_quic_header_instance =
		tommy_hashdyn_search (&loopback_ip_udp_quic_header_hashtable,
		loopback_ip_udp_quic_header_compare, loopback_ip_udp_quic_header_select,
		hash);
	if (!loopback_ip_udp_quic_header_instance)
	{
		loopback_ip_udp_quic_header_instance =
			(struct loopback_ip_udp_quic_header_instance_t *)
			malloc (sizeof (struct loopback_ip_udp_quic_header_instance_t));
		memset (loopback_ip_udp_quic_header_instance, 0,
			sizeof (struct loopback_ip_udp_quic_header_select_t));
		loopback_ip_udp_quic_header_instance_reverse =
			(struct loopback_ip_udp_quic_header_instance_t *)
			malloc (sizeof (struct loopback_ip_udp_quic_header_instance_t));
		memset (loopback_ip_udp_quic_header_instance_reverse, 0,
			sizeof (struct loopback_ip_udp_quic_header_select_t));
		loopback_ip_udp_quic_header_instance->
			loopback_ip_udp_quic_header_select =
			*loopback_ip_udp_quic_header_select;
		loopback_ip_udp_quic_header_instance->time_record_leader = 1;
		loopback_ip_udp_quic_header_instance->is_active_part =
			malloc (sizeof (char));
		loopback_ip_udp_quic_header_instance->stand = 0;
		*(loopback_ip_udp_quic_header_instance->is_active_part) = 1;
		loopback_ip_udp_quic_header_instance->state =
			loopback_ip_udp_quic_header_start;
		loopback_ip_udp_quic_header_instance->rec_ptr =
			timer_update (&loopback_ip_udp_quic_header_list,
			loopback_ip_udp_quic_header_instance, NULL, now);
		loopback_ip_udp_quic_header_instance->pair_instance =
			loopback_ip_udp_quic_header_instance_reverse;
		init_buf_list (&loopback_ip_udp_quic_header_instance->bufs);
		hash =
			loopback_ip_udp_quic_header_hash
			(loopback_ip_udp_quic_header_select);
		tommy_hashdyn_insert (&loopback_ip_udp_quic_header_hashtable,
			&loopback_ip_udp_quic_header_instance->node,
			loopback_ip_udp_quic_header_instance, hash);
		loopback_ip_udp_quic_header_instance_reverse->
			loopback_ip_udp_quic_header_select =
			*loopback_ip_udp_quic_header_select_reverse;
		loopback_ip_udp_quic_header_instance_reverse->time_record_leader = 0;
		loopback_ip_udp_quic_header_instance_reverse->is_active_part =
			loopback_ip_udp_quic_header_instance->is_active_part;
		loopback_ip_udp_quic_header_instance_reverse->stand = 1;
		loopback_ip_udp_quic_header_instance_reverse->state =
			loopback_ip_udp_quic_header_start;
		loopback_ip_udp_quic_header_instance_reverse->pair_instance =
			loopback_ip_udp_quic_header_instance;
		init_buf_list (&loopback_ip_udp_quic_header_instance_reverse->bufs);
		hash =
			loopback_ip_udp_quic_header_hash
			(loopback_ip_udp_quic_header_select_reverse);
		tommy_hashdyn_insert (&loopback_ip_udp_quic_header_hashtable,
			&loopback_ip_udp_quic_header_instance_reverse->node,
			loopback_ip_udp_quic_header_instance_reverse, hash);
	}
	else
	{
		loopback_ip_udp_quic_header_instance_reverse =
			loopback_ip_udp_quic_header_instance->pair_instance;
		if (loopback_ip_udp_quic_header_instance->time_record_leader)
			loopback_ip_udp_quic_header_instance->rec_ptr =
				timer_update (&loopback_ip_udp_quic_header_list,
				loopback_ip_udp_quic_header_instance,
				loopback_ip_udp_quic_header_instance->rec_ptr, now);
		else
			loopback_ip_udp_quic_header_instance_reverse->rec_ptr =
				timer_update (&loopback_ip_udp_quic_header_list,
				loopback_ip_udp_quic_header_instance_reverse,
				loopback_ip_udp_quic_header_instance_reverse->rec_ptr, now);
	}
	if (loopback_ip_udp_quic_header_rubik_bitmap->
		loopback_ip_udp_quic_header_QUICLongHeaderPart1)
	{
		loopback_ip_udp_data->dst_conn_id_len =
			(((loopback_ip_udp_quic_header_QUICLongHeaderPart1->
					dst_src_conn_id_len & 240) >> 4) + 3);
	}
}

void loopback_ip_udp_quic_header_quic_frame_parse (u_char *, uint32_t,
	struct timeval *);
void loopback_ip_udp_quic_header_parse (u_char * payload, uint32_t length,
	struct timeval *now)
{
	printf ("this is quic_header layer\n");
	printf ("packet length is %d\n", length);
	static uint64_t ts = 0;
	static uint64_t int_now;
	loopback_ip_udp_quic_header_payload = payload;
	loopback_ip_udp_quic_header_payload_length = length;
	loopback_ip_udp_quic_header_data_assignment (payload);
	loopback_ip_udp_quic_header_selector (now);
	loopback_ip_udp_quic_header_instance->state ();
	int_now = now->tv_sec * 1000000 + now->tv_usec;
	if (int_now - ts >= 500000.0)
	{
		check_and_drop_overtime_packet (&loopback_ip_udp_quic_header_list,
			&loopback_ip_udp_quic_header_gap,
			&loopback_ip_udp_quic_header_hashtable,
			offsetof (struct loopback_ip_udp_quic_header_instance_t, node),
			loopback_ip_udp_quic_header_free, now);
		ts = int_now;
	}
	while ((loopback_ip_udp_quic_header_buf_length > 0))
	{
		loopback_ip_udp_quic_header_quic_frame_parse
			(loopback_ip_udp_quic_header_buf,
			loopback_ip_udp_quic_header_buf_length, now);
		loopback_ip_udp_quic_header_buf =
			(loopback_ip_udp_quic_header_buf + QUICFrameTempData->length);
		loopback_ip_udp_quic_header_buf_length =
			(loopback_ip_udp_quic_header_buf_length -
			QUICFrameTempData->length);
	}
	memset (loopback_ip_udp_quic_header_rubik_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_rubik_bitmap_t));
	memset (loopback_ip_udp_quic_header_transition_bitmap, 0,
		sizeof (struct loopback_ip_udp_quic_header_transition_bitmap_t));
	if (loopback_ip_udp_quic_header_has_buf)
	{
		free (loopback_ip_udp_quic_header_buf);
		loopback_ip_udp_quic_header_has_buf = 0;
	}
}
