#include "munit.h"

#include "../cBasics/functions.h"

static MunitResult test_max_memory(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    munit_assert_int(max_sneklang_memory(4, 512), ==, 2048);
    munit_assert_int(max_sneklang_memory(8, 1024), ==, 8192);
    munit_assert_int(max_sneklang_memory(0, 512), ==, 0);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/max_memory", test_max_memory, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/functions", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
