#include <assert.h>
#include <pthread.h>
#include "GCState.h"

#ifndef REACTIVE_ISOLATES

Heap heap;
Stack stack;
Allocator allocator;
LargeAllocator largeAllocator;
BlockAllocator blockAllocator;

#else

#include "IsolateLayer.h"

GC_state_t isolate_states[MAXNUM_ISOLATES];
btree_t state_index;

static size_t next_avail_state_idx = 0;

void GC_init_state() {
    btree_init(&state_index);
}

void GC_new_instance(pthread_t tid) {
    btree_insert(&state_index, pthread_self(), next_avail_state_idx++);
}

GC_state_t *GC_get_state() {
    size_t pos = -1;
    int retval = btree_search(&state_index, pthread_self(), &pos);
    assert(retval == 0);
    return &isolate_states[pos];
}

#endif
