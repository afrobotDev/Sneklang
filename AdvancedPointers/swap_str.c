void swap_strings(char **a, char **b) {
	char **pointer_pointer_a = *b;
	char **pointer_pointer_b = *a;
	pointer_pointer_a, pointer_pointer_b = pointer_pointer_b, pointer_pointer_a;
}
