#include "datastructures/BinaryTree.h"
#include "munit.h"

size_t Settings_parseSizeStr(const char *str);

MunitResult test_empty(const MunitParameter *params,
                       void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    munit_assert_ptr_equal(btree.root, NULL);
    munit_assert_size(btree.size, ==, 0u);

    return MUNIT_OK;
}

MunitResult test_skewed(const MunitParameter params[],
                        void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    btree_insert(&btree, (pthread_t) 5, 5);
    btree_insert(&btree, (pthread_t) 6, 6);
    btree_insert(&btree, (pthread_t) 7, 7);
    btree_insert(&btree, (pthread_t) 8, 8);
    btree_insert(&btree, (pthread_t) 9, 9);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 5);
    munit_assert_size(btree_height(&btree), ==, 4);

    btree_insert(&btree, (pthread_t) 4, 2);
    btree_insert(&btree, (pthread_t) 3, 3);
    btree_insert(&btree, (pthread_t) 2, 4);
    btree_insert(&btree, (pthread_t) 1, 5);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 9);
    munit_assert_size(btree_height(&btree), ==, 4);

    return MUNIT_OK;
}

MunitResult test_non_skewed_1(const MunitParameter params[],
                              void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    btree_insert(&btree, (pthread_t) 100, 5);
    btree_insert(&btree, (pthread_t) 150, 6);
    btree_insert(&btree, (pthread_t) 200, 0);
    btree_insert(&btree, (pthread_t) 175, 1);
    btree_insert(&btree, (pthread_t) 90, 2);
    btree_insert(&btree, (pthread_t) 95, 3);
    btree_insert(&btree, (pthread_t) 50, 4);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 7);
    munit_assert_size(btree_height(&btree), ==, 3);

    return MUNIT_OK;
}

MunitResult test_search(const MunitParameter params[],
                        void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    btree_insert(&btree, (pthread_t) 100, 5);
    btree_insert(&btree, (pthread_t) 200, 0);
    btree_insert(&btree, (pthread_t) 190, 1);
    btree_insert(&btree, (pthread_t) 90, 2);
    btree_insert(&btree, (pthread_t) 95, 3);
    btree_insert(&btree, (pthread_t) 50, 4);

    size_t value;

    munit_assert_int(btree_search(&btree, (pthread_t) 200, &value), ==, 0);
    munit_assert_size(value, ==, 0);

    munit_assert_int(btree_search(&btree, (pthread_t) 190, &value), ==, 0);
    munit_assert_size(value, ==, 1);

    munit_assert_int(btree_search(&btree, (pthread_t) 90, &value), ==, 0);
    munit_assert_size(value, ==, 2);

    munit_assert_int(btree_search(&btree, (pthread_t) 95, &value), ==, 0);
    munit_assert_size(value, ==, 3);

    munit_assert_int(btree_search(&btree, (pthread_t) 50, &value), ==, 0);
    munit_assert_size(value, ==, 4);

    munit_assert_int(btree_search(&btree, (pthread_t) 100, &value), ==, 0);
    munit_assert_size(value, ==, 5);

    munit_assert_int(btree_search(&btree, (pthread_t) 1000, &value), ==, 1);

    return MUNIT_OK;
}

static MunitTest btreeTests[] = {
    {
        "/insert-test",
        test_empty,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/skewed-test",
        test_skewed,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/non-skewed-test-1",
        test_non_skewed_1,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/search-test",
        test_search,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

const MunitSuite btreeSuite = {
    "/btree-tests",         /* name */
    btreeTests,             /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
