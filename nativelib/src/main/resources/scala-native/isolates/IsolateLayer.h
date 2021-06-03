#ifndef SCALA_NATIVE_ISOLATELAYER_H
#define SCALA_NATIVE_ISOLATELAYER_H

typedef struct {
    pthread_t tids[MAXNUM_ISOLATES];
    size_t num_isolates;
} isolates_state_t;

extern isolates_state_t isolates_state;

pthread_t new_isolate(void *(*f)(void *));

#endif // SCALA_NATIVE_ISOLATELAYER_H
