#include <stdio.h>

#include "while_loop.h"

void print_numbers_reverse(int start, int end) {
    int i = end;
    while (i >= start) {
        printf("%d\n", i);
        i--;
    }
}
