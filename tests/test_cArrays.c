#include <stdio.h>

#include "munit.h"

#include "Pointers/cArrays.h"

static void fill(int *arr, int n, int value) {
    for (int i = 0; i < n; i++) {
        arr[i] = value;
    }
}

static MunitResult test_sets_fields(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    int filedata[200];
    fill(filedata, 200, -1);
    update_file(filedata, 7, 42);
    fprintf(stderr, "after update_file(..., new_filetype=7, new_num_lines=42): [1]=%d [2]=%d [199]=%d\n",
            filedata[1], filedata[2], filedata[199]);
    munit_assert_int(filedata[1], ==, 42);
    munit_assert_int(filedata[2], ==, 7);
    munit_assert_int(filedata[199], ==, 0);
    return MUNIT_OK;
}

static MunitResult test_mutates_caller(MUNIT_UNUSED const MunitParameter params[],
                                       MUNIT_UNUSED void *fixture) {
    int filedata[200];
    fill(filedata, 200, 0);
    update_file(filedata, 3, 5);
    fprintf(stderr, "caller filedata: [1]=%d [2]=%d\n", filedata[1], filedata[2]);
    munit_assert_int(filedata[1], ==, 5);
    munit_assert_int(filedata[2], ==, 3);
    return MUNIT_OK;
}

static MunitResult test_other_indices_untouched(MUNIT_UNUSED const MunitParameter params[],
                                                MUNIT_UNUSED void *fixture) {
    int filedata[200];
    fill(filedata, 200, 99);
    update_file(filedata, 7, 42);
    munit_assert_int(filedata[0], ==, 99);
    munit_assert_int(filedata[3], ==, 99);
    munit_assert_int(filedata[100], ==, 99);
    munit_assert_int(filedata[198], ==, 99);
    return MUNIT_OK;
}

static MunitResult test_boundary_last_index(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    int filedata[200];
    fill(filedata, 200, 1);
    update_file(filedata, 0, 0);
    munit_assert_int(filedata[199], ==, 0);
    munit_assert_int(filedata[198], ==, 1);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/sets_fields", test_sets_fields, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/mutates_caller", test_mutates_caller, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/other_indices_untouched", test_other_indices_untouched, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/boundary_last_index", test_boundary_last_index, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/cArrays", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
