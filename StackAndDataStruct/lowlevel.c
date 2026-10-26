#include <stdlib.h>
#include "lowlevel.h"

stack_t *stack_new(size_t capacity) {
	stack_t *new_stack = malloc(sizeof(stack_t));
	if (new_stack == NULL) {
		return NULL;
	}
	new_stack->count = 0;
	new_stack->capacity = capacity;
	new_stack->data = malloc(capacity * sizeof(void *));
	if (new_stack->data == NULL) {
		free(new_stack);
		return NULL;
	}
	return new_stack;
}
