#ifndef IMMIX_STATE_H
#define IMMIX_STATE_H

#ifndef REACTIVE_ISOLATES

#include "Heap.h"

extern Heap heap;
extern Stack stack;
extern Allocator allocator;
extern LargeAllocator largeAllocator;
extern BlockAllocator blockAllocator;

#else

#endif

#endif // IMMIX_STATE_H
