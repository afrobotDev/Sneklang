#include <stdio.h>
#include <string.h>


void print(char *charArray) {
	while(*charArray != '\0') {
		printf("%c", *charArray);
		charArray++;
	}
	printf("\n");
}

int main() {
	int *intPtr;
	char *charPtr;
	double *doublePtr;
	int intArray[10];
	char charArray[20] = "HELLO";
	double doubleArray[10];

	// the size of pointers does not change given that
	// the system is similar i.e 32-bit or 64-bit
	printf("Size of int pointer: %zu bytes\n", sizeof(intPtr));
	printf("Size of char pointer: %zu bytes\n", sizeof(charPtr));
	printf("Size of double pointer: %zu bytes\n", sizeof(doublePtr));
	printf("--------------------------------------------------------\n");

	// the size of arrays depends on data types and 
	// number of its elements
	printf("Size of int array: %zu bytes\n", sizeof(intArray));
	printf("Size of double array: %zu bytes\n", sizeof(doubleArray));
	printf("------------------------------------------------------\n");

	// characters arrays and pointers
	print(charArray);

	return 0;
}
