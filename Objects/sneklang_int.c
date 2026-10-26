#include "sneklang_obj"
#include <stddef.h>
#include <stdlib.h>


snek_object_t *new_snek_float(float value) {
	snek_object_t ptr_mod_obj = malloc(sizeof(snek_object_t));
	if (ptr_mod_obj == NULL) { return NULL; }
	ptr_mod_obj->kind = FLOAT;
	ptr_mod_obj->data = (snek_object_data_t) {.v_float = value};
	return ptr_mod_obj;
}


snek_object_t *new_snek_integer(int value) {
	snek_object_t *ptr_snek_obj = malloc(sizeof(snek_object_t));
	if (ptr_snek_obj == NULL)  {
		return NULL;
	}
	ptr_snek_obj->kind = INTEGER;
	ptr_snek_obj->data = (snek_object_data_t){.v_int = value};
	return ptr_snek_obj;
}
