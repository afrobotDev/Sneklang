#include "pointer_pointers.h"
#include <stdlib.h>

void allocate_int(int **pointer_pointer, int value) {
    int *new_pointer = malloc(sizeof(int));
    *new_pointer = value;
    *pointer_pointer = new_pointer;
}

