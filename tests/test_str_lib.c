#include <stdio.h>
#include <string.h>

#include "munit.h"

#include "Pointers/str_lib.h"

static MunitResult test_basic_append(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    TextBuffer buf;
    buf.length = 0;
    // Append "Hello " (6 chars) into buffer of size 64
    munit_assert_int(smart_append(&buf, "Hello "), ==, 0);
    munit_assert_string_equal(buf.buffer, "Hello ");
    munit_assert_int(buf.length, ==, 6);
    return MUNIT_OK;
}

static MunitResult test_overflow(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    TextBuffer buf;
    buf.length = 0;
    // Append a string longer than 63 characters (buffer size - 1)
    munit_assert_int(smart_append(&buf, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), ==, 1);
    // The length should be capped at 63 (the buffer size minus null terminator)
    munit_assert_int(buf.length, ==, 63);
    return MUNIT_OK;
}

static MunitResult test_null_dest(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    munit_assert_int(smart_append(NULL, "test"), ==, 1);
    return MUNIT_OK;
}

static MunitResult test_null_src(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    TextBuffer buf;
    buf.length = 0;
    munit_assert_int(smart_append(&buf, NULL), ==, 1);
    return MUNIT_OK;
}

static MunitResult test_append_empty_src(MUNIT_UNUSED const MunitParameter params[],
                                         MUNIT_UNUSED void *fixture) {
    TextBuffer buf;
    buf.length = 0;
    munit_assert_int(smart_append(&buf, ""), ==, 0);
    munit_assert_string_equal(buf.buffer, "");
    munit_assert_int(buf.length, ==, 0);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/basic_append", test_basic_append, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/null_dest", test_null_dest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/null_src", test_null_src, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/empty_src", test_append_empty_src, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    (char *)"/str_lib", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}