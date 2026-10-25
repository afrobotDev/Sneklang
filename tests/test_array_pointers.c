#include <string.h>
#include <stdio.h>

#include "munit.h"

#include "AdvancedPointers/array_pointers.h"

static MunitResult test_token_pointer_arrays(MUNIT_UNUSED const MunitParameter params[],
                                             MUNIT_UNUSED void *fixture) {
    token_t if_chain[] = {{"if", 1, 1}, {"(", 1, 3}, {"true", 1, 5}, {")", 1, 9}};
    token_t hello[] = {{"hello", 3, 1}};
    struct { token_t *tokens; size_t count; } cases[] = {
        {if_chain, 4},
        {hello, 1},
    };

    for (size_t c = 0; c < sizeof(cases) / sizeof(cases[0]); c++) {
        token_t *tokens = cases[c].tokens;
        size_t count = cases[c].count;
        token_t **got = create_token_pointer_array(tokens, count);

        fprintf(stderr, "create_token_pointer_array(count=%zu) -> [", count);
        for (size_t i = 0; i < count; i++) {
            fprintf(stderr, "%s\"%s\" %d:%d", i ? ", " : "", got[i]->literal,
                    got[i]->line, got[i]->column); /* print each example token */
            munit_assert_ptr_not_equal(got[i], &tokens[i]); /* fresh heap copies */
            munit_assert_string_equal(got[i]->literal, tokens[i].literal);
            munit_assert_int(got[i]->line, ==, tokens[i].line);
            munit_assert_int(got[i]->column, ==, tokens[i].column);
            free(got[i]);
        }
        fprintf(stderr, "]\n");
        free(got);
    }
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/token_pointer_arrays", test_token_pointer_arrays, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/array_pointers", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
