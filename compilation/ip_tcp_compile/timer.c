#include "timer.h"
struct time_record *timer_update (struct timer *list, void *inst_ptr,
	struct time_record *rec_ptr, struct timeval *now)
{
	//return NULL;
	if (list->head == NULL || list->tail == NULL)
	{
		list->head =
			(struct time_record *) malloc (sizeof (struct time_record));
		list->head->record.tv_sec = now->tv_sec;
		list->head->record.tv_usec = now->tv_usec;
		list->head->inst_ptr = inst_ptr;
		list->head->pre = NULL;
		list->head->next = NULL;
		list->tail = list->head;
		//printf("add to timer at %ld, %d\n", list->tail->record.tv_sec, list->tail->record.tv_usec);
		return list->tail;
	}
	if (!rec_ptr)
	{
		list->tail->next =
			(struct time_record *) malloc (sizeof (struct time_record));
		list->tail->next->pre = list->tail;
		list->tail = list->tail->next;
		list->tail->record.tv_sec = now->tv_sec;
		list->tail->record.tv_usec = now->tv_usec;
		list->tail->inst_ptr = inst_ptr;
		list->tail->next = NULL;
		//printf("add to timer at %ld, %d\n", list->tail->record.tv_sec, list->tail->record.tv_usec);
	}
	else
	{
		struct time_record *temp = rec_ptr;
		//printf("update timer from %ld, %d\n", temp->record.tv_sec, temp->record.tv_usec);
		if (temp->pre)
			temp->pre->next = temp->next;
		else
			list->head = temp->next;

		if (temp->next)
			temp->next->pre = temp->pre;
		else
			list->tail = temp->pre;

		if (list->head && list->tail)
		{
			list->tail->next = temp;
			list->tail->next->pre = list->tail;
			list->tail = list->tail->next;
		}
		else
		{
			list->head = temp;
			list->tail = temp;
			list->head->pre = NULL;
		}
		list->tail->record.tv_sec = now->tv_sec;
		list->tail->record.tv_usec = now->tv_usec;
		list->tail->inst_ptr = inst_ptr;
		list->tail->next = NULL;
		//printf("to %ld, %d\n", list->tail->record.tv_sec, list->tail->record.tv_usec);
	}
	return list->tail;
}

int is_overtime (struct timeval *t1, struct timeval *t2, struct timeval *gap)
{
	long sec_gap = t2->tv_sec - t1->tv_sec;
	int usec_gap = t2->tv_usec - t1->tv_usec;
	/* t2 < t1 */
	if (sec_gap < 0 || (sec_gap == 0 && usec_gap < 0))
		return -1;
	/* t2 - t1 < gap */
	if (sec_gap < gap->tv_sec || (sec_gap == gap->tv_sec
			&& usec_gap < gap->tv_usec))
		return 0;
	/* t2 - t1 >= gap */
	return 1;
}

void check_and_drop_overtime_packet (struct timer *list, struct timeval *gap,
	tommy_hashdyn * hashtable, int node_offset, buffer_free_func buffer_free,
	struct timeval *now)
{
	//return;
	while (list->head && is_overtime (&list->head->record, now, gap) == 1)
	{
		void *inst = list->head->inst_ptr;
		if (inst)
		{
			//printf("Packet: \nResource address is: %u\nDestination address is: %u\nID is %hu\nhas been kicked\n", ip_inst->selector.srcAddr, ip_inst->selector.dstAddr, ip_inst->selector.id);
			//printf("receiving time is %ld, %d\n", list->head->record.tv_sec, list->head->record.tv_usec);
			//printf("kicking time is %ld, %d\n\n", now->tv_sec, now->tv_usec);
			buffer_free (inst);
			tommy_hashdyn_remove_existing (hashtable, inst + node_offset);
			free (inst);
		}
		if (list->head->next)
		{
			list->head = list->head->next;
			free (list->head->pre);
			list->head->pre = NULL;
		}
		else
		{
			free (list->head);
			list->head = NULL;
			list->tail = NULL;
		}
	}
}

void deregister_timer (struct timer *list, struct time_record *rec_ptr)
{
	//return;
	struct time_record *temp = rec_ptr;
	if (temp->pre)
		temp->pre->next = temp->next;
	else
	{
		list->head = temp->next;
		if (temp->next)
			temp->next->pre = NULL;
	}
	if (temp->next)
		temp->next->pre = temp->pre;
	else
	{
		list->tail = temp->pre;
		if (temp->pre)
			temp->pre->next = NULL;
	}
	//printf("deregister a record\n");
	free (temp);
}
