#include <stdio.h>

#include "munit.h"

#include "Unions/unions_intro.h"

/* Constructors leave an object fully describing an int. */
static MunitResult test_new_integer(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    snek_object_t obj = new_integer(42);
    munit_assert_int(obj.kind, ==, INTEGER);
    munit_assert_int(obj.data.v_int, ==, 42);

    snek_object_t zero = new_integer(0);
    munit_assert_int(zero.data.v_int, ==, 0);
    return MUNIT_OK;
}

/* new_string keeps the pointer as-is (copying is covered in a later lesson). */
static MunitResult test_new_string(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    char *text = "snek";
    snek_object_t obj = new_string(text);
    munit_assert_int(obj.kind, ==, STRING);
    munit_assert_ptr(obj.data.v_string, ==, text);
    return MUNIT_OK;
}

/* format_object picks the union member matching `kind` and prints it. */
static MunitResult test_format_integer(MUNIT_UNUSED const MunitParameter params[],
                                       MUNIT_UNUSED void *fixture) {
    char buffer[64];
    format_object(new_integer(7), buffer);
    munit_assert_string_equal(buffer, "int:7");
    return MUNIT_OK;
}

static MunitResult test_format_string(MUNIT_UNUSED const MunitParameter params[],
                                      MUNIT_UNUSED void *fixture) {
    char buffer[64];
    format_object(new_string("hello"), buffer);
    munit_assert_string_equal(buffer, "string:hello");
    return MUNIT_OK;
}

/* Any kind other than INTEGER/STRING falls through to the default branch.
 * NB: a zero-initialized object counts as INTEGER (kind == 0), so cast a
 * value outside the enum. */
static MunitResult test_format_unknown_kind(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    char buffer[64];
    snek_object_t obj = {.kind = (snek_object_kind_t)99, .data = {.v_int = 5}};
    format_object(obj, buffer);
    munit_assert_string_equal(buffer, "unknown kind");
    return MUNIT_OK;
}

/* Test instances, printed to stdout for visual inspection. */
static MunitResult test_instance_output(MUNIT_UNUSED const MunitParameter params[],
                                        MUNIT_UNUSED void *fixture) {
    snek_object_t instances[] = {
        new_integer(42),
        new_integer(-13),
        new_integer(0),
        new_string("snek"),
        new_string("a much longer object name"),
        {.kind = (snek_object_kind_t)99, .data = {.v_int = 5}},
    };
    char buffer[64];

    printf("\n--- formatted test instances ---\n");
    for (size_t i = 0; i < sizeof(instances) / sizeof(instances[0]); i++) {
        format_object(instances[i], buffer);
        printf("instance[%zu] -> \"%s\"\n", i, buffer);
        munit_assert_not_null(buffer);
    }

    /* The same union storage, reinterpreted by changing kind. */
    snek_object_t obj = new_integer(99);
    format_object(obj, buffer);
    munit_assert_string_equal(buffer, "int:99");
    obj.kind = STRING;
    obj.data.v_string = "same bytes, now a string";
    format_object(obj, buffer);
    munit_assert_string_equal(buffer, "string:same bytes, now a string");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/new_integer", test_new_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/new_string", test_new_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/format_integer", test_format_integer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/format_string", test_format_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/format_unknown_kind", test_format_unknown_kind, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/instance_output", test_instance_output, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/unions_intro", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
