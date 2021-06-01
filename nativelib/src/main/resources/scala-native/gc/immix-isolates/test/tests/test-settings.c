#include "Constants.h"
#include "munit.h"
#include <stdio.h>

size_t Settings_parseSizeStr(const char *str);

MunitResult parse_sizeStr(const MunitParameter params[],
                          void *user_data_or_fixture) {
    char SIZE_MAX_STR[64] = {0};
    sprintf(SIZE_MAX_STR, "%zu", SIZE_MAX);
    size_t str_end = strlen(SIZE_MAX_STR);

    // Test without size indicator
    munit_assert_size(Settings_parseSizeStr("0"), ==, 0);
    munit_assert_size(Settings_parseSizeStr("1024"), ==, 1024u);
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==, SIZE_MAX);

    // Test kilobytes ("k" or "K" suffix)
    munit_assert_size(Settings_parseSizeStr("0k"), ==, 0);
    munit_assert_size(Settings_parseSizeStr("0K"), ==, 0);

    munit_assert_size(Settings_parseSizeStr("1024k"), ==, 1024u * 1024);
    munit_assert_size(Settings_parseSizeStr("1024K"), ==, 1024u * 1024);

    SIZE_MAX_STR[str_end] = 'k';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);
    SIZE_MAX_STR[str_end] = 'K';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);

    // Test megabytes ("m" or "M" suffix)
    munit_assert_size(Settings_parseSizeStr("0m"), ==, 0);
    munit_assert_size(Settings_parseSizeStr("0M"), ==, 0);

    munit_assert_size(Settings_parseSizeStr("1024m"), ==, 1024u * 1024 * 1024);
    munit_assert_size(Settings_parseSizeStr("1024M"), ==, 1024u * 1024 * 1024);

    SIZE_MAX_STR[str_end] = 'm';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);
    SIZE_MAX_STR[str_end] = 'M';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);

    // Test gigabytes ("g" or "G" suffix)
    munit_assert_size(Settings_parseSizeStr("0g"), ==, 0);
    munit_assert_size(Settings_parseSizeStr("0G"), ==, 0);

    munit_assert_size(Settings_parseSizeStr("2g"), ==, 1024u * 1024 * 1024 * 2);
    munit_assert_size(Settings_parseSizeStr("2G"), ==, 1024u * 1024 * 1024 * 2);

    SIZE_MAX_STR[str_end] = 'g';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);
    SIZE_MAX_STR[str_end] = 'G';
    munit_assert_size(Settings_parseSizeStr(SIZE_MAX_STR), ==,
                      UNLIMITED_HEAP_SIZE);

    return MUNIT_OK;
}

static MunitTest settingsTests[] = {
    {
        "/parse_sizeStr-test",
        parse_sizeStr,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

const MunitSuite settingsSuite = {
    "/settings-tests",      /* name */
    settingsTests,          /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
