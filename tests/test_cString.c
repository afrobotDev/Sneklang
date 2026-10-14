#include <stdio.h>
#include <string.h>

#include "munit.h"

#include "../Pointers/cString.h"

static MunitResult test_basic_concat(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    char str1[64] = "Hello";
    concat_strings(str1, " World");
    munit_assert_string_equal(str1, "Hello World");
    fprintf(stderr, "test_basic_concat: Hello World\n");
    return MUNIT_OK;
}

static MunitResult test_empty_dest(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    char str1[64] = "";
    concat_strings(str1, "Hello");
    munit_assert_string_equal(str1, "Hello");
    fprintf(stderr, "test_empty_dest: Hello\n");
    return MUNIT_OK;
}

static MunitResult test_empty_src(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    char str1[64] = "Hi";
    concat_strings(str1, "");
    munit_assert_string_equal(str1, "Hi");
    fprintf(stderr, "test_empty_src: Hi\n");
    return MUNIT_OK;
}

static MunitResult test_both_empty(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    char str1[64] = "";
    concat_strings(str1, "");
    munit_assert_string_equal(str1, "");
    fprintf(stderr, "test_both_empty: \"\"\n");
    return MUNIT_OK;
}

static MunitResult test_overwrite_terminal_null(MUNIT_UNUSED const MunitParameter params[],
                                                MUNIT_UNUSED void *fixture) {
    char str1[8] = "X"; // exactly 2 chars + null = 3 bytes, but we concat 3-char string
    /* str1 has room for at most 8 chars; we concat "abc" (3 chars) + null = 4 bytes */
    concat_strings(str1, "abc");
    munit_assert_string_equal(str1, "Xabc");
    fprintf(stderr, "test_overwrite_terminal_null: Xabc\n");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/basic_concat", test_basic_concat, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/empty_dest", test_empty_dest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/empty_src", test_empty_src, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/both_empty", test_both_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/overwrite_terminal_null", test_overwrite_terminal_null, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/cString", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
