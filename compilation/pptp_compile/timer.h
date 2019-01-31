#ifndef TIMER_MYSELF
#define TIMER_MYSELF

#include <sys/time.h>
#include "tommyds/tommy.h"
#include <stdio.h>
#include <string.h>

typedef int (*compare_func)(const void*, const void*);
typedef void (*buffer_free_func)(void*);
typedef uint32_t (*hash_func)(void*);

struct time_record {
    struct timeval record;
    struct time_record* next;
    struct time_record* pre;
    void * inst_ptr;
};
struct timer {
    struct time_record * head;
    struct time_record * tail;
};

struct time_record * timer_update(struct timer* list, void * inst_ptr, struct time_record * rec_ptr, struct timeval * now);
void check_and_drop_overtime_packet(struct timer* list, struct timeval * gap, tommy_hashdyn* hashtable, int node_offset, buffer_free_func buffer_free, struct timeval * now);
void deregister_timer(struct timer* list, struct time_record * rec_ptr);

#endif