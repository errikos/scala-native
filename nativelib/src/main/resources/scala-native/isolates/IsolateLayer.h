#ifndef SCALA_NATIVE_ISOLATELAYER_H
#define SCALA_NATIVE_ISOLATELAYER_H

#ifndef MAXNUM_ISOLATES
#define MAXNUM_ISOLATES 64
#endif

typedef struct {
    pthread_t tids[MAXNUM_ISOLATES];
    size_t num_isolates;
} isolates_state_t;

extern isolates_state_t isolates_state;

void isolates_init();

int new_isolate(pthread_t *tid, void *(*f)(void *), void *f_arg);

#endif // SCALA_NATIVE_ISOLATELAYER_H
