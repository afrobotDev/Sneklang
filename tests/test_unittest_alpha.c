#include "munit.h"

#include "cBasics/unittest_alpha.h"

static MunitResult test_average_exact(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(get_average(1, 2, 3), 2.0, 5);
    munit_assert_double_equal(get_average(0, 0, 0), 0.0, 5);
    munit_assert_double_equal(get_average(10, 20, 30), 20.0, 5);
    return MUNIT_OK;
}

static MunitResult test_average_fraction(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(get_average(1, 2, 4), 7.0 / 3.0, 5);
    munit_assert_double_equal(get_average(1, 1, 2), 4.0 / 3.0, 5);
    return MUNIT_OK;
}

static MunitResult test_average_negative(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(get_average(-3, -2, -1), -2.0, 5);
    munit_assert_double_equal(get_average(-6, 0, 6), 0.0, 5);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { (char*) "/average_exact", test_average_exact, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/average_fraction", test_average_fraction, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/average_negative", test_average_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    (char*) "/unittest_alpha", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
