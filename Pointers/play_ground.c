#include <stdio.h>
#include <string.h>
int main() {
    char str1[] = "Hi";
    char *str2 = "Snek";
    char first[50] = "Snek";
    char *second = "lang!";
    int A[] = {2,4,5,8};

    printf("%s %s\n", str1, str2);
    printf("==============================\n");
    strcat(first, second);
    printf("Hello, %s\n", first);
    printf("---------------------------------------");

    for(int i = 0; i < 5; i++) {
	    printf("Address = %d\n", &A[i]);
	    printf("Address = %d\n", A+i);
	    printf("value = %d\n", A[i]);
	    printf("valuee = %d\n", *(A+i));
    }

    return 0;
}
