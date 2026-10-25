#include <stdio.h>

#include "munit.h"

#include "AdvancedPointers/pointer_pointers.h"

static MunitResult test_basic_allocation(MUNIT_UNUSED const MunitParameter params[],
                                         MUNIT_UNUSED void *fixture) {
    int *p = NULL;
    allocate_int(&p, 42);
    fprintf(stderr, "allocate_int(&p, 42) -> p = %p, *p = %d\n", (void *)p, *p);
    munit_assert_not_null(p);
    munit_assert_int(*p, ==, 42);
    free(p);
    return MUNIT_OK;
}

static MunitResult test_reallocates_overwrites(MUNIT_UNUSED const MunitParameter params[],
                                               MUNIT_UNUSED void *fixture) {
    int *p = NULL;
    allocate_int(&p, 7);
    int *first = p;
    allocate_int(&p, 13);
    fprintf(stderr, "first *p = %d, after reallocation *p = %d\n", *first, *p);
    munit_assert_not_null(p);
    munit_assert_int(*p, ==, 13);
    munit_assert_int(*first, ==, 7);   /* untouched original allocation */
    free(first);
    free(p);
    return MUNIT_OK;
}

static MunitResult test_null_start_value(MUNIT_UNUSED const MunitParameter params[],
                                         MUNIT_UNUSED void *fixture) {
    int *p = (int *)0xdeadbeef;        /* function must overwrite garbage */
    allocate_int(&p, -5);
    fprintf(stderr, "in *p = 0xdeadbeef (garbage), out *p = %d\n", *p);
    munit_assert_not_null(p);
    munit_assert_int(*p, ==, -5);
    free(p);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/basic_allocation", test_basic_allocation, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/reallocates_overwrites", test_reallocates_overwrites, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/null_start_value", test_null_start_value, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/pointer_pointers", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
