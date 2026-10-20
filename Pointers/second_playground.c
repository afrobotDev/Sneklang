#include <stdio.h>

int main() {
	int *intPtr;
	char *charPtr;
	double *doublePtr;
	int intArray[10];
	char charArray[10];
	double doubleArray[10];

	printf("Size of int pointer: %zu bytes\n", sizeof(intPtr));
	printf("Size of char pointer: %zu bytes\n", sizeof(charPtr));
	printf("Size of double pointer: %zu bytes\n", sizeof(doublePtr));
	printf("--------------------------------------------------------\n");

	printf("Size of int array: %zu bytes\n", sizeof(intArray));
	printf("Size of char array: %zu bytes\n", sizeof(charArray));
	printf("Size of double array: %zu bytes\n", sizeof(doubleArray));
	return 0;
}
