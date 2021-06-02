#include <unistd.h>
#include <pthread.h>
#include "State.h"
#include "munit.h"

MunitResult gc_initial_state_test(const MunitParameter params[],
                                  void *user_data_or_fixture) {
    munit_assert_size(next_avail_state_idx, ==, 0);
    return MUNIT_OK;
}

MunitResult gc_init_state_test(const MunitParameter params[],
                                  void *user_data_or_fixture) {
    /* zero-out isolate GC states array */
    memset(isolate_states, 0, MAXNUM_ISOLATES * sizeof(GC_state_t));

    /* initialise GC state index */
    btree_init(&state_index);

    munit_assert_size(next_avail_state_idx, ==, 0);

    /* create a GC state for the current PID and add to index */
    btree_insert(&state_index, pthread_self(), next_avail_state_idx++);

    /* index should find the correct position */
    size_t pos = -1;
    munit_assert_int(btree_search(&state_index, pthread_self(), &pos), ==, 0);
    munit_assert_size(pos, ==, 0);

    /* get_state should return the correct position address */
    munit_assert_ptr(get_state(), ==, &isolate_states[pos]);
    munit_assert_size(next_avail_state_idx, ==, 1);

    return MUNIT_OK;
}

static MunitTest gcTests[] = {
    {
        "/gc-initial-state-test",             /* name */
        gc_initial_state_test,  /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/gc-init-state-test",             /* name */
        gc_init_state_test,  /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

const MunitSuite gcSuite = {
    "/gc-tests",            /* name */
    gcTests,                /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
