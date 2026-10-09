#include "munit.h"

static int add(int a, int b) { return a + b; }

static MunitResult test_add(MUNIT_UNUSED const MunitParameter params[],
                            MUNIT_UNUSED void *fixture) {
    munit_assert_int(add(2, 3), ==, 5);
    munit_assert_int(add(-1, 1), ==, 0);
    munit_assert_int(add(0, 0), ==, 0);
    return MUNIT_OK;
}

static MunitResult test_string(MUNIT_UNUSED const MunitParameter params[],
                               MUNIT_UNUSED void *fixture) {
    const char *greeting = "Starting the Sneklang interpreter...";
    munit_assert_string_equal(greeting, "Starting the Sneklang interpreter...");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/add", test_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/string", test_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/sneklang", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
