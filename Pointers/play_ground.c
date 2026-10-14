#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hi";
    char *str2 = "Snek";
    char first[50] = "Snek";
    char *second = "lang!";

    printf("%s %s\n", str1, str2);
    printf("==============================\n");
    strcat(first, second);
    printf("Hello, %s\n", first);

    return 0;
}
