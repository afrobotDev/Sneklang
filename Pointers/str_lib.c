#include "str_lib.h"
#include <string.h>

int smart_append(TextBuffer *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return 1;
    }

    const int buffer_size = 64;
    size_t len_src = strlen(src);
    int spare_space = sizeof(dest->buffer) - dest->length - 1;

    if (len_src > spare_space) {
        strncat(dest->buffer, src, spare_space);
        dest->length = 63;
        return 1;
    }

    strcat(dest->buffer, src);
    dest->length += len_src;

    return 0;
}
