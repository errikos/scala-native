#include <pthread.h>
#include "../gc/immix-isolates/State.h"
#include "IsolateLayer.h"

isolates_state_t isolates_state;

pthread_t new_isolate(void *(*f)(void *)) {

    pthread_t tid;
    tid = pthread_create(&tid, NULL, f, NULL);

    return tid;
}
