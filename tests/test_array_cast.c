#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "munit.h"

#include "Pointers/array_cast.h"

static char *capture(graphics_t gsettings[10]) {
    fflush(stdout);
    int saved_stdout = dup(STDOUT_FILENO);
    FILE *tmp = tmpfile();
    dup2(fileno(tmp), STDOUT_FILENO);

    dump_graphics(gsettings);

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
    return buf;
}

static MunitResult test_prints_flattened_order(MUNIT_UNUSED const MunitParameter params[],
                                               MUNIT_UNUSED void *fixture) {
    graphics_t gsettings[10];
    for (int i = 0; i < 10; i++) {
        gsettings[i].fps = i * 3;
        gsettings[i].height = i * 3 + 1;
        gsettings[i].width = i * 3 + 2;
    }

    char expected[1024] = {0};
    size_t off = 0;
    for (int i = 0; i < 30; i++) {
        off += (size_t)snprintf(expected + off, sizeof(expected) - off, "settings[%d] = %d\n", i, i);
    }

    char *out = capture(gsettings);
    fprintf(stderr, "dump_graphics printed %zu bytes\n", strlen(out));
    munit_assert_string_equal(out, expected);
    free(out);
    return MUNIT_OK;
}

static MunitResult test_field_order(MUNIT_UNUSED const MunitParameter params[],
                                    MUNIT_UNUSED void *fixture) {
    graphics_t gsettings[10];
    memset(gsettings, 0, sizeof(gsettings));
    gsettings[0].fps = 100;
    gsettings[0].height = 200;
    gsettings[0].width = 300;

    char *out = capture(gsettings);
    fprintf(stderr, "first lines:\n%.*s", 48, out);
    munit_assert_true(strncmp(out, "settings[0] = 100\nsettings[1] = 200\nsettings[2] = 300\n", 48) == 0);
    free(out);
    return MUNIT_OK;
}

static MunitResult test_prints_thirty_lines(MUNIT_UNUSED const MunitParameter params[],
                                            MUNIT_UNUSED void *fixture) {
    graphics_t gsettings[10];
    memset(gsettings, 0, sizeof(gsettings));

    char *out = capture(gsettings);
    int newlines = 0;
    for (const char *p = out; *p; p++) {
        if (*p == '\n') {
            newlines++;
        }
    }
    fprintf(stderr, "newline count = %d\n", newlines);
    munit_assert_int(newlines, ==, 30);
    free(out);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {(char *)"/prints_flattened_order", test_prints_flattened_order, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/field_order", test_field_order, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"/prints_thirty_lines", test_prints_thirty_lines, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {(char *)"/array_cast", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
