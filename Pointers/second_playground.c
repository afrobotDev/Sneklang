#include <stdio.h>
#include <string.h>


void print(char *charArray) {
	while(*charArray != '\0') {
		printf("%c", *charArray);
		charArray++;
	}
	printf("\n");
}


void funcMultiD(int (*multiArray)[2][2]) {
	// body goes here
}

int main() {

	int *intPtr;
	char *charPtr;
	double *doublePtr;
	int intArray[10];
	char charArray[20] = "HELLO";
	double doubleArray[10];


	int threedArray[3][2][2] = {
		{{2, 5}, {7, 9}},
		{{3, 4}, {6, 1}},
		{{0, 8}, {11, 13}}
	};

	// the size of pointers does not change given that
	// the system is similar i.e 32-bit or 64-bit
	printf("Size of int pointer: %zu bytes\n", sizeof(intPtr));
	printf("Size of char pointer: %zu bytes\n", sizeof(charPtr));
	printf("Size of double pointer: %zu bytes\n", sizeof(doublePtr));
	printf("--------------------------------------------------------\n");

	// characters arrays and pointers
	print(charArray);
	printf("-------------------------------------------------------\n");

	// Pointers and multi- dimensional arrays
	printf("threedArray= %d\n", threedArray);
	printf("*threedArray= %d\n", *threedArray);
        printf("threedArray[0]= %d\n", threedArray[0]);
	printf("&threedArray[0][0]= %d\n", &threedArray[0][0]);
	printf("*(threedArray[0][0]+1)= %d\n", *(threedArray[0][0]+1));

	// Passing multi- dimensional arrays as arguements
	funcMultiD(threedArray);


	return 0;
}
