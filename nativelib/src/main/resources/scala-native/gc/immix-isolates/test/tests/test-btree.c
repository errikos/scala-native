#include "datastructures/BinaryTree.h"
#include "munit.h"
#include <stdio.h>

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

    btree_insert(&btree, 5, 5);
    btree_insert(&btree, 6, 6);
    btree_insert(&btree, 7, 7);
    btree_insert(&btree, 8, 8);
    btree_insert(&btree, 9, 9);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 5);
    munit_assert_size(btree_height(&btree), ==, 4);

    btree_insert(&btree, 4, 2);
    btree_insert(&btree, 3, 3);
    btree_insert(&btree, 2, 4);
    btree_insert(&btree, 1, 5);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 9);
    munit_assert_size(btree_height(&btree), ==, 4);

    return MUNIT_OK;
}

MunitResult test_non_skewed_1(const MunitParameter params[],
                              void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    btree_insert(&btree, 100, 5);
    btree_insert(&btree, 150, 6);
    btree_insert(&btree, 200, 0);
    btree_insert(&btree, 175, 1);
    btree_insert(&btree, 90, 2);
    btree_insert(&btree, 95, 3);
    btree_insert(&btree, 50, 4);

    munit_assert_ptr(btree.root, !=, NULL);
    munit_assert_size(btree.size, ==, 7);
    munit_assert_size(btree_height(&btree), ==, 3);

    return MUNIT_OK;
}

MunitResult test_search(const MunitParameter params[],
                        void *user_data_or_fixture) {
    btree_t btree;
    btree_init(&btree);

    btree_insert(&btree, 100, 5);
    btree_insert(&btree, 200, 0);
    btree_insert(&btree, 190, 1);
    btree_insert(&btree, 90, 2);
    btree_insert(&btree, 95, 3);
    btree_insert(&btree, 50, 4);

    size_t value;

    munit_assert_int(btree_search(&btree, 200, &value), ==, 0);
    munit_assert_size(value, ==, 0);

    munit_assert_int(btree_search(&btree, 190, &value), ==, 0);
    munit_assert_size(value, ==, 1);

    munit_assert_int(btree_search(&btree, 90, &value), ==, 0);
    munit_assert_size(value, ==, 2);

    munit_assert_int(btree_search(&btree, 95, &value), ==, 0);
    munit_assert_size(value, ==, 3);

    munit_assert_int(btree_search(&btree, 50, &value), ==, 0);
    munit_assert_size(value, ==, 4);

    munit_assert_int(btree_search(&btree, 100, &value), ==, 0);
    munit_assert_size(value, ==, 5);

    munit_assert_int(btree_search(&btree, 1000, &value), ==, 1);

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
