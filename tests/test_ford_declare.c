#include <stdio.h>
#include <string.h>

#include "munit.h"

#include "Pointers/ford_declare.h"

static MunitResult test_node_creation(MUNIT_UNUSED const MunitParameter params[],
                                     MUNIT_UNUSED void *fixture) {
    snekobject_t node = new_node("root");
    munit_assert_ptr_not_null(&node);
    munit_assert_string_equal(node.name, "root");
    munit_assert_ptr_null(node.child);
    return MUNIT_OK;
}

static MunitResult test_node_name(MUNIT_UNUSED const MunitParameter params[],
                                  MUNIT_UNUSED void *fixture) {
    snekobject_t node = new_node("child_node");
    munit_assert_string_equal(node.name, "child_node");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/node_creation", test_node_creation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/node_name", test_node_name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    (char *)"/ford_declare", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}