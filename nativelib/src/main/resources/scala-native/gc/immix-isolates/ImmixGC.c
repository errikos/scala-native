#include <stdlib.h>
#include <pthread.h>
#include "GCTypes.h"
#include "Heap.h"
#include "datastructures/Stack.h"
#include "State.h"
#include "utils/MathUtils.h"
#include "Constants.h"
#include "Settings.h"

void scalanative_afterexit() {
    Stats_OnExit(get_state()->heap.stats);
}

NOINLINE void scalanative_init() {
    /* zero-out isolate GC states array */
    memset(isolate_states, 0, MAXNUM_ISOLATES * sizeof(GC_state_t));

    /* initialise GC state index */
    btree_init(&state_index);

    btree_insert(&state_index, pthread_self(), next_avail_state_idx++);

    Heap_Init(&get_state()->heap, Settings_MinHeapSize(), Settings_MaxHeapSize());
    Stack_Init(&get_state()->stack, INITIAL_STACK_SIZE);
    atexit(scalanative_afterexit);
}

INLINE void *scalanative_alloc(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_Alloc(&get_state()->heap, size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_small(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_AllocSmall(&get_state()->heap, size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_large(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_AllocLarge(&get_state()->heap, size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_atomic(void *info, size_t size) {
    return scalanative_alloc(info, size);
}

INLINE void scalanative_collect() { Heap_Collect(&get_state()->heap, &get_state()->stack); }
