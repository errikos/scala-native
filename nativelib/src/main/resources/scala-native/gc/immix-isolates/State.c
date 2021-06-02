#include <assert.h>
#include <pthread.h>
#include "State.h"

#ifndef REACTIVE_ISOLATES

Heap heap;
Stack stack;
Allocator allocator;
LargeAllocator largeAllocator;
BlockAllocator blockAllocator;

#else

GC_state_t isolate_states[MAXNUM_ISOLATES];
btree_t state_index;

size_t next_avail_state_idx = 0;

GC_state_t *get_state() {
    size_t pos = -1;
    int retval = btree_search(&state_index, pthread_self(), &pos);
    assert(retval == 0);
    return &isolate_states[pos];
}

#endif
