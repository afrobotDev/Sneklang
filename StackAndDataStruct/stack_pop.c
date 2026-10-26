#include "lowlevel.h"
#include <stddef.h>
#include <stdlib.h>

void stack_pop(stack_t *stack) {
	if (stack->count == 0) {
		return NULL;
	}
	stack->count--;
	return stack->data[stack->count];
	
}
