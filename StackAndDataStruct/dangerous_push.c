#include "lowlevel.h"
#include <stdlib.h>

void scary_double_push(stack_t *s) {
	stack_push(s, (void *)1337);
	int *int_ptr = malloc(sizeof(int));
	*int_ptr = 1024;
	stack_push(int_ptr, (void *)int_ptr);
}
