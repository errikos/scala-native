#include <stdlib.h>
#include <stddef.h>

// Darwin defines MAP_ANON instead of MAP_ANONYMOUS
#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#define MAP_ANONYMOUS MAP_ANON
#endif

// Dummy GC that maps chunks of 4GB and allocates but never frees.

// Map 4GB
#define CHUNK (4 * 1024 * 1024 * 1024L)
// Allow read and write
#define DUMMY_GC_PROT (PROT_READ | PROT_WRITE)
// Map private anonymous memory, and prevent from reserving swap
#define DUMMY_GC_FLAGS (MAP_NORESERVE | MAP_PRIVATE | MAP_ANONYMOUS)
// Map anonymous memory (not a file)
#define DUMMY_GC_FD -1
#define DUMMY_GC_FD_OFFSET 0

void *current = 0;
void *end = 0;

void scalanative_init() {
    current = malloc(CHUNK);
    end = (char*)current + (ptrdiff_t)CHUNK;
}

void *scalanative_alloc(void *info, size_t size) {
    size = size + (8 - size % 8);
    if ((char*)current + size < (char*)end) {
        void **alloc = current;
        *alloc = info;
        current = (char*)current + size;
        return alloc;
    } else {
        scalanative_init();
        return scalanative_alloc(info, size);
    }
}

void *scalanative_alloc_small(void *info, size_t size) {
    return scalanative_alloc(info, size);
}

void *scalanative_alloc_large(void *info, size_t size) {
    return scalanative_alloc(info, size);
}

void *scalanative_alloc_atomic(void *info, size_t size) {
    return scalanative_alloc(info, size);
}

void scalanative_collect() {}
