#include "free.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  const int num_array = 500;
  for (int i = 0; i < num_array; i++) {
    int *scalar_array = allocate_scalar_array(50000, 2);
    if (scalar_array == NULL) {
      printf("Failed to allocate array\n");
      return 1;
    } else {
      printf("Allocated array%d\n", i);
    }
    free(scalar_array);
  }
  return 0;
}

