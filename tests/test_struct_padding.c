#include <stddef.h>

#include "munit.h"

#include "../Structs/struct_padding.h"

static MunitResult test_field_assignment(MUNIT_UNUSED const MunitParameter params[],
                                         MUNIT_UNUSED void *fixture) {
    char name[] = "sneklang";
    sneklang_var_t v;
    v.weight = 3.5;
    v.name = name;
    v.value = 42;
    v.scope_level = 2;
    v.type = 'i';
    v.is_constant = 1;

    munit_assert_double(v.weight, ==, 3.5);
    munit_assert_ptr_equal(v.name, name);
    munit_assert_string_equal(v.name, "sneklang");
    munit_assert_int(v.value, ==, 42);
    munit_assert_int(v.scope_level, ==, 2);
    munit_assert_char(v.type, ==, 'i');
    munit_assert_char(v.is_constant, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_member_order(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    munit_assert_size(offsetof(sneklang_var_t, weight), ==, 0);
    munit_assert_size(offsetof(sneklang_var_t, name), >=,
                      offsetof(sneklang_var_t, weight) + sizeof(double));
    munit_assert_size(offsetof(sneklang_var_t, value), >=,
                      offsetof(sneklang_var_t, name) + sizeof(char *));
    munit_assert_size(offsetof(sneklang_var_t, scope_level), >=,
                      offsetof(sneklang_var_t, value) + sizeof(int));
    munit_assert_size(offsetof(sneklang_var_t, type), >=,
                      offsetof(sneklang_var_t, scope_level) + sizeof(int));
    munit_assert_size(offsetof(sneklang_var_t, is_constant), >=,
                      offsetof(sneklang_var_t, type) + sizeof(char));
    return MUNIT_OK;
}

static MunitResult test_members_are_aligned(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    munit_assert_size(offsetof(sneklang_var_t, name) % _Alignof(char *), ==, 0);
    munit_assert_size(offsetof(sneklang_var_t, value) % _Alignof(int), ==, 0);
    munit_assert_size(offsetof(sneklang_var_t, scope_level) % _Alignof(int), ==, 0);
    return MUNIT_OK;
}

static MunitResult test_padding_exists(MUNIT_UNUSED const MunitParameter params[],
                                       MUNIT_UNUSED void *fixture) {
    size_t members = sizeof(double) + sizeof(char *) + 2 * sizeof(int) + 2 * sizeof(char);
    munit_assert_size(sizeof(sneklang_var_t), >=, members);
    munit_assert_size(sizeof(sneklang_var_t) % _Alignof(sneklang_var_t), ==, 0);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/field_assignment", test_field_assignment, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/member_order", test_member_order, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/members_are_aligned", test_members_are_aligned, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {(char *)"/padding_exists", test_padding_exists, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/struct_padding", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
