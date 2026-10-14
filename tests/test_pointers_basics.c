#include <stdio.h>

#include "munit.h"

#include "Pointers/pointers_basics.h"

static MunitResult test_change_filetype(MUNIT_UNUSED const MunitParameter params[],
                                        MUNIT_UNUSED void *fixture) {
    codefile_t f = {100, 1};
    codefile_t r = change_filetype(f, 2);
    fprintf(stderr, "change_filetype({100, 1}, 2) -> {%d, %d}\n", r.lines, r.filetype);
    munit_assert_int(r.lines, ==, 100);
    munit_assert_int(r.filetype, ==, 2);
    return MUNIT_OK;
}

static MunitResult test_preserves_lines(MUNIT_UNUSED const MunitParameter params[],
                                        MUNIT_UNUSED void *fixture) {
    codefile_t f = {42, 7};
    codefile_t r = change_filetype(f, 99);
    fprintf(stderr, "change_filetype({42, 7}, 99) -> {%d, %d}\n", r.lines, r.filetype);
    munit_assert_int(r.lines, ==, 42);
    munit_assert_int(r.filetype, ==, 99);
    return MUNIT_OK;
}

static MunitResult test_same_value(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    codefile_t f = {10, 5};
    codefile_t r = change_filetype(f, 5);
    fprintf(stderr, "change_filetype({10, 5}, 5) -> {%d, %d}\n", r.lines, r.filetype);
    munit_assert_int(r.lines, ==, 10);
    munit_assert_int(r.filetype, ==, 5);
    return MUNIT_OK;
}

static MunitResult test_input_not_mutated(MUNIT_UNUSED const MunitParameter params[],
                                          MUNIT_UNUSED void *fixture) {
    codefile_t f = {100, 1};
    codefile_t r = change_filetype(f, 2);
    fprintf(stderr, "caller f after call -> {%d, %d}\n", f.lines, f.filetype);
    munit_assert_int(f.filetype, ==, 1);
    munit_assert_int(r.filetype, ==, 2);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/change_filetype", test_change_filetype, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/preserves_lines", test_preserves_lines, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/same_value", test_same_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/input_not_mutated", test_input_not_mutated, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/pointers_basics", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
