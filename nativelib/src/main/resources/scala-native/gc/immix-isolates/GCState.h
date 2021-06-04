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

#define HEAP() (heap)
#define STACK() (stack)
#define ALLOCATOR() (allocator)
#define LARGE_ALLOCATOR() (largeAllocator)
#define BLOCK_ALLOCATOR() (blockAllocator)

#else

typedef struct {
    Heap heap;
    Stack stack;
    Allocator allocator;
    LargeAllocator largeAllocator;
    BlockAllocator blockAllocator;
} GC_state_t;

extern GC_state_t isolate_states[];
extern btree_t state_index;

void GC_init_state();
void GC_new_instance(pthread_t tid);

GC_state_t *GC_get_state();

#define HEAP() (GC_get_state()->heap)
#define STACK() (GC_get_state()->stack)
#define ALLOCATOR() (GC_get_state()->allocator)
#define LARGE_ALLOCATOR() (GC_get_state()->largeAllocator)
#define BLOCK_ALLOCATOR() (GC_get_state()->blockAllocator)

#endif

#endif // IMMIX_STATE_H
