#include <stdlib.h>
#include <stdio.h>

#include "munit.h"

#include "StackAndDataStruct/lowlevel.h"

static MunitResult test_pop_lifo(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    int vals[] = {10, 20, 30};
    stack_t *s = stack_new(4);
    for (int i = 0; i < 3; i++) {
        stack_push(s, &vals[i]);
    }
    fprintf(stderr, "pushed 10, 20, 30 -> count=%zu\n", s->count);

    for (int i = 2; i >= 0; i--) {
        void *got = stack_pop(s);
        fprintf(stderr, "stack_pop(s) -> %d (count=%zu)\n", *(int *)got, s->count);
        munit_assert_ptr_equal(got, &vals[i]); /* last in, first out */
    }
    munit_assert_size(s->count, ==, 0);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitResult test_pop_empty(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    stack_t *s = stack_new(2);

    void *got = stack_pop(s);
    fprintf(stderr, "stack_pop(empty) -> %s (count=%zu)\n",
            got == NULL ? "NULL" : "non-NULL", s->count);

    munit_assert_null(got); /* popping an empty stack is a no-op */
    munit_assert_size(s->count, ==, 0);

    /* the stack still works after the empty pop */
    int val = 7;
    stack_push(s, &val);
    fprintf(stderr, "stack_push(s, 7) -> count=%zu\n", s->count);
    munit_assert_size(s->count, ==, 1);
    munit_assert_ptr_equal(stack_pop(s), &val);

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/pop_lifo", test_pop_lifo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/pop_empty", test_pop_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/stack_pop", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
