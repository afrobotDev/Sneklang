#include "munit.h"

#include "../Structs/structs_intro.h"

static MunitResult test_new_coord(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    struct Coordinate c = new_coord(4, 5, 6);
    munit_assert_int(c.x, ==, 4);
    munit_assert_int(c.y, ==, 5);
    munit_assert_int(c.z, ==, 6);

    struct Coordinate zero = new_coord(0, 0, 0);
    munit_assert_int(zero.x, ==, 0);
    munit_assert_int(zero.y, ==, 0);
    munit_assert_int(zero.z, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_aggregate_init(MUNIT_UNUSED const MunitParameter params[],
                                       MUNIT_UNUSED void *fixture) {
    struct Coordinate c = {1, 2, 3};
    munit_assert_int(c.x, ==, 1);
    munit_assert_int(c.y, ==, 2);
    munit_assert_int(c.z, ==, 3);
    return MUNIT_OK;
}

static MunitResult test_field_assignment(MUNIT_UNUSED const MunitParameter params[],
                                         MUNIT_UNUSED void *fixture) {
    struct Coordinate c;
    c.x = 10;
    c.y = -20;
    c.z = 0;
    munit_assert_int(c.x, ==, 10);
    munit_assert_int(c.y, ==, -20);
    munit_assert_int(c.z, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_copy_is_independent(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    struct Coordinate original = {1, 2, 3};
    struct Coordinate copy = original;
    copy.x = 99;
    munit_assert_int(original.x, ==, 1);
    munit_assert_int(copy.x, ==, 99);
    munit_assert_int(copy.y, ==, 2);
    munit_assert_int(copy.z, ==, 3);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/new_coord", test_new_coord, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/aggregate_init", test_aggregate_init, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/field_assignment", test_field_assignment, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/copy_is_independent", test_copy_is_independent, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/structs_intro", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
