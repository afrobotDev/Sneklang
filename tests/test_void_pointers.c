#include <stdio.h>
#include <string.h>

#include "munit.h"

#include "AdvancedPointers/void_pointers.h"

static MunitResult test_zero_out(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    snek_int_t i = {"answer", 42};
    snek_float_t f = {"pi", 0, 3.5f};
    snek_bool_t b = {"flag", 0, 1};
    float before = f.value;

    snek_zero_out(&i, INTEGER);
    fprintf(stderr, "snek_zero_out(&{\"answer\", 42}, INTEGER) -> value = %d\n", i.value);
    snek_zero_out(&f, FLOAT);
    fprintf(stderr, "snek_zero_out(&{\"pi\", %.1f}, FLOAT) -> value = %g\n", before, f.value);
    snek_zero_out(&b, BOOL);
    fprintf(stderr, "snek_zero_out(&{\"flag\", 1}, BOOL) -> value = %u\n", b.value);

    munit_assert_int(i.value, ==, 0);
    munit_assert_double(f.value, ==, 0.0);
    munit_assert_uint(b.value, ==, 0);
    /* the cast must hit `value`, leaving the name pointer alone */
    munit_assert_string_equal(i.name, "answer");
    munit_assert_string_equal(f.name, "pi");
    munit_assert_string_equal(b.name, "flag");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/zero_out", test_zero_out, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/void_pointers", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
