#include <stdlib.h>
#include <stdio.h>

#include "munit.h"

#include "StackAndDataStruct/lowlevel.h"

static void print_stack(const char *label, const stack_t *s) {
    fprintf(stderr, "%s: count=%zu, capacity=%zu, data=[", label, s->count, s->capacity);
    for (size_t i = 0; i < s->count; i++) {
        fprintf(stderr, "%s%d", i ? ", " : "", *(int *)s->data[i]);
    }
    fprintf(stderr, "]\n");
}

static MunitResult test_push_within_capacity(MUNIT_UNUSED const MunitParameter params[],
                                             MUNIT_UNUSED void *fixture) {
    int vals[] = {10, 20, 30};
    stack_t *s = stack_new(4);

    for (int i = 0; i < 3; i++) {
        stack_push(s, &vals[i]);
        fprintf(stderr, "stack_push(s, %d) -> count=%zu, data[%d] = %d\n",
                vals[i], s->count, i, *(int *)s->data[i]);
    }
    print_stack("stack_new(4) + 3 pushes", s);

    munit_assert_size(s->count, ==, 3);
    munit_assert_size(s->capacity, ==, 4); /* no growth needed */
    for (int i = 0; i < 3; i++) {
        munit_assert_ptr_equal(s->data[i], &vals[i]);
    }

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitResult test_push_grows(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    int vals[] = {1, 2, 3};
    stack_t *s = stack_new(1);
    size_t seen_capacity[3];

    for (int i = 0; i < 3; i++) {
        stack_push(s, &vals[i]);
        seen_capacity[i] = s->capacity;
        print_stack("after push", s);
    }

    fprintf(stderr, "capacity after each push: %zu -> %zu -> %zu\n",
            seen_capacity[0], seen_capacity[1], seen_capacity[2]);

    munit_assert_size(s->count, ==, 3);
    munit_assert_size(seen_capacity[0], ==, 1); /* growth is lazy: checked before insert */
    munit_assert_size(seen_capacity[1], ==, 2); /* 1 -> 2 */
    munit_assert_size(seen_capacity[2], ==, 4); /* 2 -> 4 */
    for (int i = 0; i < 3; i++) {
        munit_assert_int(*(int *)s->data[i], ==, vals[i]); /* realloc preserved entries */
    }

    free(s->data);
    free(s);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/push_within_capacity", test_push_within_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/push_grows", test_push_grows, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/stack_push", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
