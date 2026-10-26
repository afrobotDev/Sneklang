#include "lowlevel.h"
#include <stdlib.h>
#include <string.h>

void stack_push_multiple_types(stack_t *s) {
	float* float_ptr = malloc(sizeof(float));
	*float_ptr = 3.14;
	stack_push(s, (void *)float_ptr);

	char *string = "Sneklang is blazingly slow!";
	size_t len = strlen(string) + 1;
	char *string_ptr = malloc(sizeof(char) * len);
	strcpy(string_ptr, string);
	stack_push(s, string_ptr);
}
