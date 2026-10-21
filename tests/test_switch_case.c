#include "munit.h"

#include "../Enums/switch_case.h"

/* Enumerators of an annotated enum use their explicit values. */
static MunitResult test_enum_values(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    munit_assert_int(HTTP_BAD_REQUEST, ==, 400);
    munit_assert_int(HTTP_UNAUTHORIZED, ==, 401);
    munit_assert_int(HTTP_NOT_FOUND, ==, 404);
    munit_assert_int(HTTP_TEAPOT, ==, 418);
    munit_assert_int(HTTP_INTERNAL_SERVER_ERROR, ==, 500);
    return MUNIT_OK;
}

/* Each known code maps to its canonical status string. */
static MunitResult test_http_to_str_known_codes(MUNIT_UNUSED const MunitParameter params[],
                                                MUNIT_UNUSED void *fixture) {
    munit_assert_string_equal(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request");
    munit_assert_string_equal(http_to_str(HTTP_UNAUTHORIZED), "401 Unauthorized");
    munit_assert_string_equal(http_to_str(HTTP_NOT_FOUND), "404 Not Found");
    munit_assert_string_equal(http_to_str(HTTP_TEAPOT), "418 I AM A TEAPOT!");
    munit_assert_string_equal(http_to_str(HTTP_INTERNAL_SERVER_ERROR), "500 Internal Server Error");
    return MUNIT_OK;
}

/* A code with no case hits the default branch. */
static MunitResult test_http_to_str_unknown_code(MUNIT_UNUSED const MunitParameter params[],
                                                 MUNIT_UNUSED void *fixture) {
    http_error_code_t unknown = (http_error_code_t)999;
    munit_assert_string_equal(http_to_str(unknown), "Unknown HTTP status code");
    return MUNIT_OK;
}

/* The function must never return NULL. */
static MunitResult test_never_null(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    http_error_code_t codes[] = {HTTP_BAD_REQUEST, HTTP_UNAUTHORIZED, HTTP_NOT_FOUND,
                                 HTTP_TEAPOT, HTTP_INTERNAL_SERVER_ERROR, (http_error_code_t)999};
    for (size_t i = 0; i < sizeof(codes) / sizeof(codes[0]); i++) {
        munit_assert_not_null(http_to_str(codes[i]));
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/enum_values", test_enum_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/http_to_str_known_codes", test_http_to_str_known_codes, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/http_to_str_unknown_code", test_http_to_str_unknown_code, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/never_null", test_never_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/switch_case", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
