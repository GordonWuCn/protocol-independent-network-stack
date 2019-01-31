#include "buf.h"
#include <stdlib.h>
void init_buf_list (struct buf_queue **buf)
{
	(*buf) = (struct buf_queue *) malloc (sizeof (struct buf_queue));
	(*buf)->root = (struct avl_root *) malloc (sizeof (struct avl_root));
	(*buf)->root->node = NULL;
	(*buf)->root->head = NULL;
	(*buf)->head = malloc (sizeof (struct buf_list));
	(*buf)->head->next = NULL;
	(*buf)->packet_count = 0;
	(*buf)->buf_len = 0;
	(*buf)->is_tree = 0;
}

void free_buf_list (struct buf_queue *buf)
{
	if (buf->packet_count)
	{
		if (buf->is_tree)
		{
			struct avl_node *stack[buf->packet_count];
			int stack_ptr = 0;
			struct avl_node *cur_ptr = buf->root->node;
			struct avl_node *tmp;
			while (buf->packet_count > 0)
			{
				if (cur_ptr)
				{
					stack[stack_ptr++] = cur_ptr;
					cur_ptr = cur_ptr->left;
				}
				else
				{
					cur_ptr = stack[--stack_ptr];
					free (((struct buffer_node *) cur_ptr)->buf.buf);
					tmp = cur_ptr;
					cur_ptr = cur_ptr->right;
					free (tmp);
					buf->packet_count--;
				}
			}

			// do{
			//  if(cur_ptr->left) {
			//      stack[stack_ptr++] = cur_ptr;
			//      cur_ptr = cur_ptr->left;
			//  }
			//  else if(cur_ptr->right) {
			//      struct avl_node * tmp = cur_ptr;
			//      cur_ptr = cur_ptr->right;
			//      if(tmp->parent) {
			//          if(tmp->parent->left == tmp) tmp->parent->left = NULL;
			//          else tmp->parent->right = NULL;
			//      }
			//      free(((struct buffer_node*)tmp)->buf.buf);
			//      free(tmp);
			//      buf->packet_count--;
			//  }
			//  else{
			//      if(cur_ptr->parent) {
			//          if(cur_ptr->parent->left == cur_ptr) cur_ptr->parent->left = NULL;
			//          else cur_ptr->parent->right = NULL;
			//      }
			//      free(((struct buffer_node*)cur_ptr)->buf.buf);
			//      free(cur_ptr);
			//      cur_ptr = stack[--stack_ptr];
			//      buf->packet_count--;
			//  }
			// }while(buf->packet_count > 0);
		}
		else
		{
			struct buf_list *cur = buf->head->next;
			struct buf_list *pre;
			while (cur != NULL)
			{
				pre = cur;
				cur = cur->next;
				free (pre->buf.buf);
				free (pre);
			}
		}
	}
	free (buf->root);
	free (buf->head);
	free (buf);
}
