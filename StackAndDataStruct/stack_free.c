#include "lowlevel.h"
#include <stdddef>
#include <stdlib.h>

void stack_free(stack_t *stack) {
	if (stack == NULL) {
		return;
	} else if (stack->data == NULL) {
		return;
	}
	free(stack->data);
	free(stack);
	
}
