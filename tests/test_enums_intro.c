#include "munit.h"

#include "../Enums/enums_intro.h"

/* Enumerators can be given explicit integer values. */
static MunitResult test_explicit_values(MUNIT_UNUSED const MunitParameter params[],
                                       MUNIT_UNUSED void *fixture) {
    munit_assert_int(RED, ==, 55);
    munit_assert_int(GREEN, ==, 176);
    munit_assert_int(BLUE, ==, 38);
    return MUNIT_OK;
}

/* Enumerators are plain ints usable in expressions. */
static MunitResult test_usable_as_int(MUNIT_UNUSED const MunitParameter params[],
                                      MUNIT_UNUSED void *fixture) {
    munit_assert_int(BLUE - GREEN, ==, -138);
    munit_assert_int(GREEN - RED, ==, 121);
    munit_assert_int(RED < GREEN && GREEN < BLUE, ==, 0);
    return MUNIT_OK;
}

/* Variables can be declared with the typedef'd enum type. */
static MunitResult test_enum_type(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    color_t paint = BLUE;
    munit_assert_int(paint, ==, 38);

    paint = RED;
    munit_assert_int(paint, ==, 55);
    return MUNIT_OK;
}

/* Comparisons work directly on enum constants. */
static MunitResult test_comparison(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    color_t a = GREEN, b = GREEN, c = RED;
    munit_assert_int(a, ==, b);
    munit_assert_int(c, !=, a);
    return MUNIT_OK;
}

/* sizeof(color_t) is at least int-sized (C11 6.7.2.2p5: compiler-chosen). */
static MunitResult test_storage_size(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    munit_assert_size(sizeof(color_t) >= sizeof(int), ==, 1);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/explicit_values", test_explicit_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/usable_as_int", test_usable_as_int, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/enum_type", test_enum_type, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/comparison", test_comparison, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/storage_size", test_storage_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/enums_intro", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
