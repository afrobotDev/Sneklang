#include "munit.h"

#include "../cBasics/welcome_to_mem.h"

static MunitResult test_welcome(MUNIT_UNUSED const MunitParameter params[],
                                MUNIT_UNUSED void *fixture) {
    munit_assert_string_equal(sneklang_welcome(), "Starting the Sneklang interpreter...");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/welcome", test_welcome, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/cbasics", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
