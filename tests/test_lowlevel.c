#include <stdlib.h>
#include <stdio.h>

#include "munit.h"

#include "StackAndDataStruct/lowlevel.h"

static MunitResult test_stack_new(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    size_t capacities[] = {1, 4, 8};

    for (size_t c = 0; c < sizeof(capacities) / sizeof(capacities[0]); c++) {
        stack_t *s = stack_new(capacities[c]);
        munit_assert_not_null(s);

        fprintf(stderr, "stack_new(%zu) -> {count=%zu, capacity=%zu, data=%p}\n",
                capacities[c], s->count, s->capacity, (void *)s->data);

        munit_assert_size(s->count, ==, 0); /* empty on creation */
        munit_assert_size(s->capacity, ==, capacities[c]);
        munit_assert_not_null(s->data); /* backing array was allocated too */

        free(s->data);
        free(s);
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/stack_new", test_stack_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/lowlevel", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
