#include <stdio.h>

#include "munit.h"

#include "../Structs/scale_coord.h"

static MunitResult test_positive(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    struct Coordinate c = scale_coord((struct Coordinate){.x = 1, .y = 2, .z = 3}, 2);
    fprintf(stderr, "scale_coord(1, 2, 3, factor=2) -> (%d, %d, %d)\n", c.x, c.y, c.z);
    munit_assert_int(c.x, ==, 2);
    munit_assert_int(c.y, ==, 4);
    munit_assert_int(c.z, ==, 6);
    return MUNIT_OK;
}

static MunitResult test_zero(MUNIT_UNUSED const MunitParameter params[],
                             MUNIT_UNUSED void *fixture) {
    struct Coordinate c = scale_coord((struct Coordinate){.x = 5, .y = -7, .z = 9}, 0);
    fprintf(stderr, "scale_coord(5, -7, 9, factor=0) -> (%d, %d, %d)\n", c.x, c.y, c.z);
    munit_assert_int(c.x, ==, 0);
    munit_assert_int(c.y, ==, 0);
    munit_assert_int(c.z, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_negative_factor(MUNIT_UNUSED const MunitParameter params[],
                                        MUNIT_UNUSED void *fixture) {
    struct Coordinate c = scale_coord((struct Coordinate){.x = 1, .y = -2, .z = 3}, -1);
    fprintf(stderr, "scale_coord(1, -2, 3, factor=-1) -> (%d, %d, %d)\n", c.x, c.y, c.z);
    munit_assert_int(c.x, ==, -1);
    munit_assert_int(c.y, ==, 2);
    munit_assert_int(c.z, ==, -3);
    return MUNIT_OK;
}

static MunitResult test_identity(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    struct Coordinate c = scale_coord((struct Coordinate){.x = 10, .y = 20, .z = 30}, 1);
    fprintf(stderr, "scale_coord(10, 20, 30, factor=1) -> (%d, %d, %d)\n", c.x, c.y, c.z);
    munit_assert_int(c.x, ==, 10);
    munit_assert_int(c.y, ==, 20);
    munit_assert_int(c.z, ==, 30);
    return MUNIT_OK;
}

static MunitResult test_input_not_mutated(MUNIT_UNUSED const MunitParameter params[],
                                          MUNIT_UNUSED void *fixture) {
    struct Coordinate input = {.x = 3, .y = 4, .z = 5};
    struct Coordinate c = scale_coord(input, 3);
    fprintf(stderr, "scale_coord(3, 4, 5, factor=3) -> (%d, %d, %d)\n", c.x, c.y, c.z);
    munit_assert_int(c.x, ==, 9);
    munit_assert_int(c.y, ==, 12);
    munit_assert_int(c.z, ==, 15);
    munit_assert_int(input.x, ==, 3);
    munit_assert_int(input.y, ==, 4);
    munit_assert_int(input.z, ==, 5);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/negative_factor", test_negative_factor, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/identity", test_identity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/input_not_mutated", test_input_not_mutated, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/scale_coord", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}