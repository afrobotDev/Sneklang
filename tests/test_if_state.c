#include "munit.h"

#include "cBasics/if_state.h"

static MunitResult test_too_cold(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_string_equal(get_temperature_status(69), "too cold");
    munit_assert_string_equal(get_temperature_status(0), "too cold");
    munit_assert_string_equal(get_temperature_status(-10), "too cold");
    return MUNIT_OK;
}

static MunitResult test_just_right(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_string_equal(get_temperature_status(70), "just right");
    munit_assert_string_equal(get_temperature_status(89), "just right");
    munit_assert_string_equal(get_temperature_status(90), "just right");
    return MUNIT_OK;
}

static MunitResult test_too_hot(MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void* fixture) {
    munit_assert_string_equal(get_temperature_status(91), "too hot");
    munit_assert_string_equal(get_temperature_status(100), "too hot");
    munit_assert_string_equal(get_temperature_status(200), "too hot");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { (char*) "/too_cold", test_too_cold, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/just_right", test_just_right, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/too_hot", test_too_hot, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    (char*) "/if_state", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}