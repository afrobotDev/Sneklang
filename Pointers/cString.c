#include "cString.h"

// implement our own string concatenation function
void concat_strings(char *str1, const char *str2) {
    int indx = 0;
    while (str1[indx] != '\0') {
        indx++;
    }

    int str2_ptr = 0;
    while (str2[str2_ptr] != '\0') {
        str1[indx + str2_ptr] = str2[str2_ptr];
        str2_ptr++;
    }
    str1[indx + str2_ptr] = '\0';
}
