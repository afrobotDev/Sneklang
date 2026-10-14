#include "array_cast.h"
#include <stdio.h>

void dump_graphics(graphics_t gsettings[10]) {
    int *ptr = (int *)gsettings;
    for (int i = 0; i < (3 * 10); i++) {
        printf("settings[%d] = %d\n", i, ptr[i]);
    }
}
