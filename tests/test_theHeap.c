#include <string.h>
#include <stdio.h>

#include "munit.h"

#include "StackAndHeap/theHeap.h"

static MunitResult test_examples(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    struct { char *greeting, *name, *expected; int size; } cases[] = {
        {"Hello", "Alice", "Hello Alice", 100},
        {"Goodbye", "Bob", "Goodbye Bob", 100},
        {"Welcome", "", "Welcome ", 100},
        {"", "Eve", " Eve", 100},
        {"Hi", "Bob", "Hi Bob", 12},
        {"Hello", "Alice", "Hello", 6}, /* truncated to fit buffer */
    };
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *got = get_full_greeting(cases[i].greeting, cases[i].name, cases[i].size);
        fprintf(stderr, "get_full_greeting(\"%s\", \"%s\", %d) -> \"%s\"\n",
                cases[i].greeting, cases[i].name, cases[i].size, got);
        munit_assert_string_equal(got, cases[i].expected);
        free(got);
    }
    return MUNIT_OK;
}

static MunitResult test_heap_memory(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    char long_name[200];
    memset(long_name, 'n', 150);
    long_name[150] = '\0';

    char *a = get_full_greeting("Hello", "Grace", 100);
    char *b = get_full_greeting("Hello", "Grace", 100);
    char *caps = get_full_greeting("Hello", long_name, 100);

    fprintf(stderr, "a = %p \"%s\", b = %p \"%s\" (distinct allocations)\n",
            (void *)a, a, (void *)b, b);
    fprintf(stderr, "150-char name with size=100 -> len=%zu (snprintf caps output)\n",
            strlen(caps));
    b[0] = 'M'; /* heap memory is writable */
    fprintf(stderr, "after b[0] = 'M': a = \"%s\", b = \"%s\"\n", a, b);

    munit_assert_ptr_not_equal(a, b);
    munit_assert_string_equal(a, "Hello Grace");
    munit_assert_size(strlen(caps), ==, 99);

    free(a);
    free(b);
    free(caps);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/examples", test_examples, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/heap_memory", test_heap_memory, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/theHeap", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
