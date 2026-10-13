#include <limits.h>
#include <stdio.h>

#include "munit.h"

#include "../Pointers/memory.h"

static MunitResult test_pointer_size(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    fprintf(stderr, "size_of_addr(0) = %lu, sizeof(long long *) = %zu, sizeof(void *) = %zu\n",
            size_of_addr(0), sizeof(long long *), sizeof(void *));
    munit_assert_size(size_of_addr(0), ==, sizeof(long long *));
    munit_assert_size(size_of_addr(0), ==, sizeof(void *));
    return MUNIT_OK;
}

static MunitResult test_ignores_value(MUNIT_UNUSED const MunitParameter params[],
                                      MUNIT_UNUSED void *fixture) {
    fprintf(stderr, "size_of_addr(0) = %lu\n", size_of_addr(0));
    fprintf(stderr, "size_of_addr(1) = %lu\n", size_of_addr(1));
    fprintf(stderr, "size_of_addr(-1) = %lu\n", size_of_addr(-1));
    fprintf(stderr, "size_of_addr(LLONG_MAX) = %lu\n", size_of_addr(LLONG_MAX));
    fprintf(stderr, "size_of_addr(42) = %lu\n", size_of_addr(42));
    fprintf(stderr, "size_of_addr(-42) = %lu\n", size_of_addr(-42));
    munit_assert_size(size_of_addr(0), ==, size_of_addr(1));
    munit_assert_size(size_of_addr(-1), ==, size_of_addr(LLONG_MAX));
    munit_assert_size(size_of_addr(42), ==, size_of_addr(-42));
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/pointer_size", test_pointer_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/ignores_value", test_ignores_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/memory", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
