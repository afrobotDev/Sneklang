#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "munit.h"

#include "../cBasics/doWhile_loop.h"

static char *capture(int start, int end) {
    fflush(stdout);
    int saved_stdout = dup(STDOUT_FILENO);
    FILE *tmp = tmpfile();
    dup2(fileno(tmp), STDOUT_FILENO);

    print_numbers_countdown(start, end);

    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    fseek(tmp, 0, SEEK_SET);
    char *buf = malloc(1);
    size_t len = 0;
    int c;
    while ((c = fgetc(tmp)) != EOF) {
        buf = realloc(buf, len + 2);
        buf[len++] = (char)c;
    }
    buf[len] = '\0';
    fclose(tmp);
    fprintf(stderr, "print_numbers_countdown(%d, %d) output:\n%s", start, end, buf);
    return buf;
}

static MunitResult test_range(MUNIT_UNUSED const MunitParameter params[],
                              MUNIT_UNUSED void *fixture) {
    char *out = capture(1, 3);
    munit_assert_string_equal(out, "1\n");
    free(out);
    return MUNIT_OK;
}

static MunitResult test_single(MUNIT_UNUSED const MunitParameter params[],
                               MUNIT_UNUSED void *fixture) {
    char *out = capture(5, 5);
    munit_assert_string_equal(out, "5\n");
    free(out);
    return MUNIT_OK;
}

static MunitResult test_descending(MUNIT_UNUSED const MunitParameter params[],
                                   MUNIT_UNUSED void *fixture) {
    char *out = capture(3, 1);
    munit_assert_string_equal(out, "3\n2\n1\n");
    free(out);
    return MUNIT_OK;
}

static MunitResult test_negative(MUNIT_UNUSED const MunitParameter params[],
                                 MUNIT_UNUSED void *fixture) {
    char *out = capture(-2, 0);
    munit_assert_string_equal(out, "-2\n");
    free(out);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/at_least_once", test_range, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/single", test_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/descending", test_descending, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/doWhile_loop", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}