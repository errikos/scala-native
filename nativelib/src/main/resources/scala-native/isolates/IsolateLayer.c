#include <pthread.h>
#include <stdlib.h>
#include "ImmixGC.h"
#include "GCState.h"
#include "IsolateLayer.h"

typedef struct {
    void *(*f)(void *);
    void *f_arg;
} thread_function_arg_t;

isolates_state_t isolates_state;

void isolates_init() {
    memset(isolates_state.tids, 0, sizeof(isolates_state.tids));
    isolates_state.num_isolates = 0;
}

static void *thread_function(void *arg) {
    /**
     * Initialise the GC for the new isolate thread.
     * This must be done inside the thread function (routine),
     * but before the actual routine starts executing, since:
     * - the GC state uses the thread ID to associate information
     * - the state must be initialised before routine execution
     */
    scalanative_thread_init();

    thread_function_arg_t *a = (thread_function_arg_t *) arg;
    void *result = a->f(a->f_arg);

    free(arg);
    return result;
}

int new_isolate(pthread_t *tid, void *(*f)(void *), void *f_arg) {
    if (isolates_state.num_isolates == MAXNUM_ISOLATES) {
        fprintf(stderr, "error: cannot create isolate, limit reached (%d)\n", MAXNUM_ISOLATES);
        return -1;
    }

    thread_function_arg_t *arg = malloc(sizeof(thread_function_arg_t));
    *arg = (thread_function_arg_t) { .f = f, .f_arg = f_arg};

    pthread_create(tid, NULL, thread_function, arg);

    isolates_state.tids[isolates_state.num_isolates++] = *tid;

    return 0;
}
