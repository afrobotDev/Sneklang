#include <stdio.h>
#include "playground.h"

void printValue(void *ptr, data_type_t type) {
  if (type == INT) {
    printf("Value: %d\n", *(int*)ptr);
  } else if (type == FLOAT) {
    printf("Value: %f\n", *(float*)ptr);
  }
}

int main() {
	int number = 42;
	printValue(&number, INT);
	printf("------------------------------\n");

	float decimal = 3.14;
	printValue(&decimal, FLOAT);

	return 0;
}


