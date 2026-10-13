#include <stdio.h>

#include "munit.h"

#include "../Pointers/coordinate.h"

static MunitResult test_update_x_mutates_caller(MUNIT_UNUSED const MunitParameter params[],
                                                MUNIT_UNUSED void *fixture) {
    coordinate_t c = {1, 2, 3};
    coordinate_update_x(&c, 99);
    fprintf(stderr, "after coordinate_update_x(&(1,2,3), 99): caller c = (%d, %d, %d)\n", c.x, c.y,
            c.z);
    munit_assert_int(c.x, ==, 99);
    munit_assert_int(c.y, ==, 2);
    munit_assert_int(c.z, ==, 3);
    return MUNIT_OK;
}

static MunitResult test_update_and_return_x(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    coordinate_t c = {1, 2, 3};
    coordinate_t r = coordinate_update_and_return_x(c, 42);
    fprintf(stderr, "coordinate_update_and_return_x((1,2,3), 42) -> (%d, %d, %d)\n", r.x, r.y, r.z);
    munit_assert_int(r.x, ==, 42);
    munit_assert_int(r.y, ==, 2);
    munit_assert_int(r.z, ==, 3);
    munit_assert_int(c.x, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_update_and_return_edge_values(MUNIT_UNUSED const MunitParameter params[],
                                                      MUNIT_UNUSED void *fixture) {
    coordinate_t c = {-5, 0, 5};
    coordinate_t r = coordinate_update_and_return_x(c, 0);
    fprintf(stderr, "coordinate_update_and_return_x((-5,0,5), 0) -> (%d, %d, %d)\n", r.x, r.y, r.z);
    munit_assert_int(r.x, ==, 0);
    munit_assert_int(r.y, ==, 0);
    munit_assert_int(r.z, ==, 5);
    munit_assert_int(c.x, ==, -5);
    return MUNIT_OK;
}

static MunitTest tests[] = {{(char *)"/update_x_mutates_caller", test_update_x_mutates_caller, NULL,
                             NULL, MUNIT_TEST_OPTION_NONE, NULL},
                            {(char *)"/update_and_return_x", test_update_and_return_x, NULL, NULL,
                             MUNIT_TEST_OPTION_NONE, NULL},
                            {(char *)"/update_and_return_edge_values",
                             test_update_and_return_edge_values, NULL, NULL, MUNIT_TEST_OPTION_NONE,
                             NULL},
                            {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/coordinate", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
