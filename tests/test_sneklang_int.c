#include <string.h>

#include "munit.h"

#include "Objects/sneklang_obj.h"

static MunitResult test_add_integers(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    snek_object_t *a = new_snek_integer(2);
    snek_object_t *b = new_snek_integer(40);

    snek_object_t *sum = snek_add(a, b);
    munit_assert_not_null(sum);
    munit_assert_int(sum->kind, ==, INTEGER);
    munit_assert_int(sum->data.v_int, ==, 42);

    return MUNIT_OK;
}

static MunitResult test_add_integer_and_float(MUNIT_UNUSED const MunitParameter params[],
                                              MUNIT_UNUSED void *fixture) {
    snek_object_t *i = new_snek_integer(2);
    snek_object_t *f = new_snek_float(1.5f);

    snek_object_t *sum_1 = snek_add(i, f);
    munit_assert_not_null(sum_1);
    munit_assert_int(sum_1->kind, ==, FLOAT);
    munit_assert_float(sum_1->data.v_float, ==, 3.5f);

    snek_object_t *sum_2 = snek_add(f, i);
    munit_assert_not_null(sum_2);
    munit_assert_int(sum_2->kind, ==, FLOAT);
    munit_assert_float(sum_2->data.v_float, ==, 3.5f);

    return MUNIT_OK;
}

static MunitResult test_add_strings(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    snek_object_t *a = new_snek_string("foo");
    snek_object_t *b = new_snek_string("bar");

    snek_object_t *sum = snek_add(a, b);
    munit_assert_not_null(sum);
    munit_assert_int(sum->kind, ==, STRING);
    munit_assert_string_equal(sum->data.v_string, "foobar");
    munit_assert_size(strlen(sum->data.v_string), ==, 6);

    /* the operands must come back unchanged */
    munit_assert_string_equal(a->data.v_string, "foo");
    munit_assert_string_equal(b->data.v_string, "bar");

    return MUNIT_OK;
}

static MunitResult test_add_mismatched_kinds(MUNIT_UNUSED const MunitParameter params[],
                                             MUNIT_UNUSED void *fixture) {
    snek_object_t *s = new_snek_string("foo");
    snek_object_t *i = new_snek_integer(1);
    snek_object_t *v = new_snek_vector3(new_snek_integer(1), new_snek_integer(2),
                                        new_snek_integer(3));

    munit_assert_null(snek_add(s, i));
    munit_assert_null(snek_add(i, s));
    munit_assert_null(snek_add(v, i));
    munit_assert_null(snek_add(NULL, i));
    munit_assert_null(snek_add(i, NULL));

    return MUNIT_OK;
}

static MunitResult test_add_vectors(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    snek_object_t *a = new_snek_vector3(new_snek_integer(1), new_snek_integer(2),
                                        new_snek_integer(3));
    snek_object_t *b = new_snek_vector3(new_snek_integer(10), new_snek_integer(20),
                                        new_snek_integer(30));

    snek_object_t *sum = snek_add(a, b);
    munit_assert_not_null(sum);
    munit_assert_int(sum->kind, ==, VECTOR3);
    munit_assert_int(sum->data.v_vector3.x->data.v_int, ==, 11);
    munit_assert_int(sum->data.v_vector3.y->data.v_int, ==, 22);
    munit_assert_int(sum->data.v_vector3.z->data.v_int, ==, 33);

    return MUNIT_OK;
}

static MunitResult test_add_arrays(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    snek_object_t *a = new_snek_array(2);
    munit_assert_not_null(a);
    snek_object_t *b = new_snek_array(2);
    munit_assert_not_null(b);

    munit_assert_true(snek_array_set(a, 0, new_snek_integer(1)));
    munit_assert_true(snek_array_set(a, 1, new_snek_integer(2)));
    munit_assert_true(snek_array_set(b, 0, new_snek_integer(3)));
    munit_assert_true(snek_array_set(b, 1, new_snek_integer(4)));

    snek_object_t *sum = snek_add(a, b);
    munit_assert_not_null(sum);
    munit_assert_int(sum->kind, ==, ARRAY);
    munit_assert_size(sum->data.v_array.size, ==, 4);

    int expected[] = {1, 2, 3, 4};
    for (size_t i = 0; i < 4; i++) {
        snek_object_t *element = snek_array_get(sum, i);
        munit_assert_not_null(element);
        munit_assert_int(element->data.v_int, ==, expected[i]);
    }

    return MUNIT_OK;
}

static MunitResult test_array_bounds(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    snek_object_t *array = new_snek_array(2);
    snek_object_t *value = new_snek_integer(7);

    munit_assert_true(snek_array_set(array, 0, value));
    munit_assert_ptr_equal(snek_array_get(array, 0), value);

    /* index == size is one past the end and must be rejected */
    munit_assert_null(snek_array_get(array, 2));
    munit_assert_null(snek_array_get(array, 99));
    munit_assert_false(snek_array_set(array, 2, value));
    munit_assert_false(snek_array_set(array, 99, value));

    munit_assert_null(snek_array_get(NULL, 0));
    munit_assert_false(snek_array_set(NULL, 0, value));
    munit_assert_false(snek_array_set(array, 0, NULL));
    munit_assert_null(snek_array_get(value, 0));
    munit_assert_false(snek_array_set(value, 0, value));

    return MUNIT_OK;
}

static MunitResult test_length(MUNIT_UNUSED const MunitParameter params[],
                               MUNIT_UNUSED void *fixture) {
    snek_object_t *array = new_snek_array(3);

    munit_assert_int(snek_length(new_snek_integer(1)), ==, 1);
    munit_assert_int(snek_length(new_snek_float(1.0f)), ==, 1);
    munit_assert_int(snek_length(new_snek_string("four")), ==, 4);
    munit_assert_int(snek_length(new_snek_vector3(new_snek_integer(1), new_snek_integer(2),
                                                  new_snek_integer(3))),
                     ==, 3);
    munit_assert_int(snek_length(array), ==, 3);
    munit_assert_int(snek_length(NULL), ==, -1);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/add_integers", test_add_integers, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/add_integer_and_float", test_add_integer_and_float, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/add_strings", test_add_strings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/add_mismatched_kinds", test_add_mismatched_kinds, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/add_vectors", test_add_vectors, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/add_arrays", test_add_arrays, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/array_bounds", test_array_bounds, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/length", test_length, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/sneklang_int", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
