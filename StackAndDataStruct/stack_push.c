#include "lowlevel.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void stack_push(stack_t *stack, void *obj) {
	if (stack->count == stack->capacity) {
		stack->capacity *= 2;
		void *modify_mem = realloc(stack->data, stack->capacity * sizeof(void *));
		if (modify_mem == NULL) {
			stack->capacity /= 2;
			exit(1);
		}
		stack->data = modify_mem;
	}
	stack->data[stack->count] = obj;
	stack->count++;
	return;
}
