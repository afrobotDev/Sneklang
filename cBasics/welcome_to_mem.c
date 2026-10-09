#include <stdio.h>

#include "welcome_to_mem.h"

const char *sneklang_welcome(void) { return "Starting the Sneklang interpreter..."; }

#ifndef UNIT_TEST
int main(void) {
    printf("%s\n", sneklang_welcome());
    return 0;
}
#endif
