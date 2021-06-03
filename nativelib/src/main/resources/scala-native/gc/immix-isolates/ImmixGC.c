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
    Stats_OnExit(HEAP().stats);
}

#ifndef REACTIVE_ISOLATES

NOINLINE void scalanative_init() {
    Heap_Init(&HEAP(), Settings_MinHeapSize(), Settings_MaxHeapSize());
    Stack_Init(&STACK(), INITIAL_STACK_SIZE);
    atexit(scalanative_afterexit);
}

#else

/* This function is called once per thread. */
NOINLINE void scalanative_thread_init() {
    btree_insert(&state_index, pthread_self(), next_avail_state_idx++);

    Heap_Init(&HEAP(), Settings_MinHeapSize(), Settings_MaxHeapSize());
    Stack_Init(&STACK(), INITIAL_STACK_SIZE);

    atexit(scalanative_afterexit);
}

/* This function is called exactly once, by the generated "main" function. */
NOINLINE void scalanative_init() {
    /* zero-out isolate GC states array */
    memset(isolate_states, 0, MAXNUM_ISOLATES * sizeof(GC_state_t));

    /* initialise GC state index */
    btree_init(&state_index);

    /* initialise the GC for the main thread */
    scalanative_thread_init();
}

#endif

INLINE void *scalanative_alloc(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_Alloc(&HEAP(), size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_small(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_AllocSmall(&HEAP(), size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_large(void *info, size_t size) {
    size = MathUtils_RoundToNextMultiple(size, ALLOCATION_ALIGNMENT);

    void **alloc = (void **)Heap_AllocLarge(&HEAP(), size);
    *alloc = info;
    return (void *)alloc;
}

INLINE void *scalanative_alloc_atomic(void *info, size_t size) {
    return scalanative_alloc(info, size);
}

INLINE void scalanative_collect() { Heap_Collect(&HEAP(), &STACK()); }
