#include "munit.h"

MunitResult sample_test(const MunitParameter params[], void *user_data_or_fixture) {
  munit_assert_true(1);
  return MUNIT_OK;
}

static MunitTest sampleTests[] = {{
                                      "/sample-test",         /* name */
                                      sample_test,            /* test */
                                      NULL,                   /* setup */
                                      NULL,                   /* tear_down */
                                      MUNIT_TEST_OPTION_NONE, /* options */
                                      NULL                    /* parameters */
                                  },
                                  /* Mark the end of the array with an entry where the test
                                   * function is NULL */
                                  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

const MunitSuite sampleSuite = {
    "/sample-tests",        /* name */
    sampleTests,            /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
