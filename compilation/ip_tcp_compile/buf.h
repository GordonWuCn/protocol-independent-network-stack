#ifndef _BUF_T_
#define _BUF_T_
#include "avlmini.h"
#include <stdint.h>

struct avl_root;
struct avl_node;

struct buffer {
	uint64_t meta;
	unsigned char * buf;
	int len;
};

struct buffer_node {
	struct avl_node node;
	struct buffer buf;
};

struct buf_list {
	struct buf_list* next;
	struct buffer buf;
};

struct buf_queue{
	struct avl_root * root;
	struct buf_list * head;
	int packet_count;
	int buf_len;
	int is_tree;
};


#define COMPARE_ASC(p1, p2) ((struct buffer_node*)p1)->buf.meta != \
	((struct buffer_node*)p2)->buf.meta ? \
	((struct buffer_node*)p1)->buf.meta < \
	((struct buffer_node*)p2)->buf.meta : -1

#define COMPARE_DESC(p1, p2) ((struct buffer_node*)p1)->buf.meta != \
	((struct buffer_node*)p2)->buf.meta ? \
	((struct buffer_node*)p1)->buf.meta > \
	((struct buffer_node*)p2)->buf.meta : -1

#define LIST_COMPARE_ASC(p1, p2) p1 != p2 ? p1 > p2 : -1
#define LIST_COMPARE_DESC(p1, p2) p1 != p2 ? p1 < p2 : -1

void free_buf_list(struct buf_queue *);
void init_buf_list(struct buf_queue **);

#endif
// -----buffer assemble

// {0}_bufs = {0}_instance->bufs;
// if({1}){
// 	if({0}_bufs->is_tree || {0}_bufs->packet_count > {0}_THRESHOLD){
// 		{0}_buf = malloc({0}_bufs->buf_len);
// 		{0}_buf_length = {0}_bufs->buf_len;
// 		int offset = 0;
// 		struct avl_node * stack[{0}_bufs->packet_count];
// 		int stack_ptr = 0;
// 		struct avl_node * cur_ptr = {0}_bufs->root->node
// 		while({0}_bufs->packet_count > 0) {
// 			if(cur_ptr) {
// 				stack[stack_ptr++] = cur_ptr;
// 				cur_ptr = cur_ptr->left;
// 			}
// 			else{
// 				cur_ptr = stack[--stack_ptr];
// 				memcpy({0}_buf + offset, ((struct buffer_node*)cur_buf)->buf.buf,
// 		 								((struct buffer_node*)cur_buf)->buf.len)
// 		 		offset += ((struct buffer_node*)cur_buf)->buf.len;
// 				free(((struct buffer_node*)tmp)->buf.buf);
// 				free(tmp);
// 				buf->packet_count--;
// 				cur_ptr = cur_ptr->right;
// 			}
// 		}
// 		{0}_bufs->buf_len = 0;
// 		{0}_bufs->is_tree = 0;
// 	}
// 	else{
// 		{0}_buf = malloc({0}_bufs->buf_len);
// 		{0}_buf_length = {0}_bufs->buf_len;
// 		int offset = 0;
// 		struct buf_list* cur_buf;
// 		struct buf_list* pre_buf;
// 		for(cur_buf = {0}_bufs->head->next; cur_buf != NULL;) {
// 			memcpy({0}_buf + offset, cur_buf->buf.buf, cur_buf->buf.len);
// 			offset += cur_buf->len;
// 			pre_buf = cur_buf;
// 			cur_buf = cur_buf->next;
// 			free(pre_buf->buf.buf);
// 			free(pre_buf);
// 		}
// 		{0}_bufs->buf_len = 0;
// 		{0}_bufs->packet_count = 0;
// 		{0}_bufs->head->next = NULL;
// 	}
// }


//-----buffer eject
// 0 for protocol
// 1 for meta condition

// {0}_bufs = {0}_instance->bufs;
// while({0}_bufs->packet_count > 0){
// 	if({0}_bufs->is_tree || {0}_bufs->packet_count > {0}_THRESHOLD){
// 		uint64_t meta = {0}_bufs->root->head->buf.meta;
// 		if({1}) {
// 			{0}_buf = {0}_bufs->root->head->buf.buf;
// 			{0}_buf_length = {0}_bufs->root->head->buf.len;
// 			{0}_bufs->buf_len -= {0}_bufs->root->head->buf.len;
// 			struct buffer_node * head = {0}_bufs->root->head;
// 			avl_node_erase({0}_bufs->root->head, root);
// 			{0}_bufs->packet_count--;
// 			free(head);
// 		}
// 		else{
// 			break;
// 		}
// 	}
// 	else{
// 		uint64_t meta = {0}_bufs->head->next.buf.meta;
// 		if({1}) {
// 			{0}_bufs->buf_len -= {0}_bufs->head->next.buf.len;
// 			{0}_buf = {0}_bufs->head->next->buf.buf;
// 			{0}_buf_length = {0}_bufs->head->next->buf.len;
// 			struct buffer_node * head = {0}_bufs->head->next;
// 			{0}_bufs->head->next = {0}_bufs->head->next->next;
// 			{0}->bufs->packet_count--;
// 			free(head);
// 		}
// 		else {
// 			break;
// 		}
// 	}
// 	free({0}_buf);
// }
// if({0}_bufs->packet_count == 0) {0}_bufs->is_tree = 0;

//-----buffer insert
// 0 for protocol
// 1 for meta assignment
// 2 for dir
// 3 for line compare dir

// {0}_bufs = {0}_instance->bufs;
// if({0}_bufs->is_tree || {0}_bufs->packet_count > {0}_THRESHOLD){
// 	struct buffer_node * node;
// 	struct avl_node * dup;
// 	node = malloc(sizeof(struct buffer_node));
// 	node->buf.buf = malloc(sizeof({0}_payload_length));
// 	memcpy(node->buf.buf,{0}_payload, {0}_payload_length);
// 	{0}_bufs->buf_len += {0}_payload_length;
// 	node->buf.len = {0}_payload_length;
// 	node->buf.meta = {1};// meta assignment
// 	avl_node_add({0}_bufs->root, node, dup, {2});
// 	{0}_bufs->packet_count++;
// }
// else{
// 	if({0}_bufs->head->next == NULL) {
// 		{0}_bufs->head->next = malloc(sizeof(struct buf_list));
// 		{0}_bufs->head->next->buf.meta = {1};//meta_data_assignment here
// 		{0}_bufs->head->next->buf.buf = malloc(sizeof({0}_payload_length));
// 		memcpy({0}_bufs->head->next->buf.buf, {0}_payload, {0}_payload_length);
// 		{0}_bufs->head->next->buf.len = {0}_payload_length;
// 		{0}_bufs->buf_len = {0}_payload_length;
// 		{0}_bufs->packet_count++;
// 	}
// 	else{
// 		if({0}_bufs->packet_count >= {0}_THRESHOLD) {
// 			struct buf_list * pre_buf;
// 			struct buf_list * cur_buf = {0}_bufs->head->next;
// 			struct buffer node * node;
// 			struct avl_node * dup;
// 			while(cur_buf != NULL) {
// 				node = malloc(sizeof(struct buffer_node));
// 				node->buf = cur_buf->buf;
// 				avl_node_add({0}_bufs->root, node, dup, {2});
// 				pre_buf = cur_buf;
// 				cur_buf = cur_buf->next;
// 				free(pre_buf);
// 			}
// 			{0}_bufs->head->next = NULL;
// 			node = malloc(sizeof(struct buffer_node));
// 			node->buf.buf = malloc(sizeof({0}_payload_length));
// 			memcpy(node->buf.buf,{0}_payload, {0}_payload_length);
// 			{0}_bufs->buf_len += {0}_payload_length;
// 			node->buf.len = {0}_payload_length;
// 			node->buf.meta = {1};//meta_data assignment here
// 			avl_node_add({0}_bufs->root, node, dup, {2});
// 			{0}_bufs->packet_count++;
// 		}
// 		else {
// 			struct buf_list * pre_buf = {0}_bufs->head;
// 			struct buf_list * cur_buf = {0}_bufs->head->next;
// 			char inserted = 0;
// 			while(cur_buf != NULL) {
// 				r = LIST_COMPARE_{3}(cur_buf.buf.meta, meta)
// 				if(r == 1) {
// 					pre_buf->next = malloc(sizeof(struct buf_list));
// 					pre_buf->next.buf.buf = malloc(sizeof({0}_payload_length));
// 					pre_buf->next.buf.len = {0}_payload_length;
// 					memcpy(pre_buf->next.buf.buf, {0}_payload, {0}_payload_length);
// 					pre_buf->next->buf.meta = {1};//meta_data assignment here
// 					pre_buf->next->next = cur_buf;
// 					{0}_bufs->buf_len += {0}_payload_length;
// 					{0}_bufs->packet_count++;
// 					break;
// 				}
// 				else if(r == -1) //replace or callback
// 				else{
// 					pre_buf = cur_buf;
// 					cur_buf = cur_buf->next;
// 				}
// 			}
// 			if(!inserted) {
// 				pre_buf->next = malloc(sizeof(struct buf_list));
// 				pre_buf->next->buf.buf = malloc({0}_payload_length);
// 				pre_buf->next->buf.len = {0}_payload_length;
// 				memcpy(pre_buf->next->buf.buf, {0}_payload, {0}_payload_length);
// 				pre_buf->next->next = NULL;
// 				pre_buf->next->buf.meta = {1};//meta_data assignment here
// 				{0}_bufs->buf_len += {0}_payload_length;
// 				{0}_bufs->packet_count++;
// 			}
// 		}
// 	}
// }
