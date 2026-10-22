#include <string.h>
#include <stdio.h>

#include "munit.h"

#include "StackAndHeap/malloc.h"

static MunitResult test_scalar_arrays(MUNIT_UNUSED const MunitParameter params[],
                                      MUNIT_UNUSED void *fixture) {
    struct { int size, multiplier; } cases[] = {
        {5, 2},
        {4, -3},
        {1, 7},
        {10, 0},
    };
    for (size_t c = 0; c < sizeof(cases) / sizeof(cases[0]); c++) {
        int size = cases[c].size, multiplier = cases[c].multiplier;
        int *arr = allocate_scalar_array(size, multiplier);
        fprintf(stderr, "allocate_scalar_array(%d, %d) -> [", size, multiplier);
        for (int i = 0; i < size; i++) {
            fprintf(stderr, "%s%d", i ? " " : "", arr[i]); /* print each example value */
            munit_assert_int(arr[i], ==, i * multiplier);  /* every element is i * multiplier */
        }
        fprintf(stderr, "]\n");
        free(arr);
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/scalar_arrays", test_scalar_arrays, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/malloc", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
