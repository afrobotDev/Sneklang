#include "munit.h"

#include "cBasics/mathops.h"

static MunitResult test_score_basic(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(snek_score(1, 1, 1, 1.0f), 2.0, 5);
    munit_assert_double_equal(snek_score(2, 3, 4, 0.5f), 5.5, 5);
    munit_assert_double_equal(snek_score(1, 2, 3, 1.5f), 7.5, 5);
    return MUNIT_OK;
}

static MunitResult test_score_zero(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(snek_score(0, 0, 0, 5.0f), 0.0, 5);
    munit_assert_double_equal(snek_score(0, 7, 9, 3.0f), 21.0, 5);
    return MUNIT_OK;
}

static MunitResult test_score_fractional(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_double_equal(snek_score(10, 0, 10, 0.1f), 10.0, 5);
    munit_assert_double_equal(snek_score(3, 1, 3, 0.25f), 2.5, 5);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { (char*) "/score_basic", test_score_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/score_zero", test_score_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/score_fractional", test_score_fractional, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    (char*) "/mathops", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
