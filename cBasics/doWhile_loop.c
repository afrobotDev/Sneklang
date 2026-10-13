#include <stdio.h>

#include "doWhile_loop.h"

void print_numbers_countdown(int start, int end) {
    do {
        printf("%d\n", start);
        start--;
    } while (start >= end);
}
