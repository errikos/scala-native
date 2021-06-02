#ifndef IMMIX_STATE_H
#define IMMIX_STATE_H

#include "datastructures/BinaryTree.h"
#include "Heap.h"

#ifndef REACTIVE_ISOLATES

extern Heap heap;
extern Stack stack;
extern Allocator allocator;
extern LargeAllocator largeAllocator;
extern BlockAllocator blockAllocator;

#else

#ifndef MAXNUM_ISOLATES
#define MAXNUM_ISOLATES 64
#endif

typedef struct {
    Heap heap;
    Stack stack;
    Allocator allocator;
    LargeAllocator largeAllocator;
    BlockAllocator blockAllocator;
} GC_state_t;

extern GC_state_t isolate_states[];
extern btree_t state_index;

extern size_t next_avail_state_idx;

GC_state_t *get_state();

#endif

#endif // IMMIX_STATE_H
