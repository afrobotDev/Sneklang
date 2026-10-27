#include "sneklang_obj"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
	if (a == NULL || b == NULL) {
		return NULL;
	}
	switch (a->kind) {
		case INTEGER:
			{
				if (b->kind == INTEGER) {
					int sum_integers = a->data.v_int + b->data.v_int;
					return new_snek_integer(sum_integers);
				} else if (b->kind == FLOAT) {
					float sum_floats = (float)a->data.v_int + b->data.v_float;
					return new_snek_float(sum_floats);
				} else {
					return NULL;
				}
			}
		case FLOAT:
			{
				if (b->kind == FLOAT) {
					float sum_floats = a->data.v_float + b->data.v_float;
					return new_snek_float(sum_floats);
				} else if (b->kind == INTEGER) {
					float sum_floats = a->data.v_float + (float)b->data.v_int;
					return new_snek_float(sum_floats);
				} else {
					return NULL;
				}
			}
		case STRING:
			{
				if (b->kind != STRING) {
					return NULL;
				}
				int len_strings= snek_length(a) + snek_length(b) + 1;
				char *string = calloc(len_strings, sizeof(char *));
				strcat(a, b);
				strcat(string, a);
				snek_object_t *new_string_obj = new_snek_string(string);
				free(string);
				return new_string_obj;
			}
		case VECTOR3:
			{
				if (b->kind != VECTOR3) {
					return NULL;
				}
				snek_object_t *new_vector_obj = new_snek_vector3(snek_add(a->data.v_vector3.x, b->data.v_vector3.x), snek_add(a->data.v_vector3.y, b->data.v_vector3.y), snek_add(a->data.v_vector3.z, b->data.v_vector3.z));
				return new_vector_obj;
			}
		case ARRAY:
			{
				if (b->kind != ARRAY) {
					return NULL;
				}
				snek_object_t *array_object = new_snek_array(a->data.v_array.size + b->data.v_array.size);
				for (int i = 0; i < a->data.v_array.size; i++) {
					snek_object_t *obj_a = snek_array_get(a->data.v_array.elements, i);
					snek_array_set(array_object, i, obj_a);

				}
				for (int i = 0; i < b->data.v_array.size; i++) {
					snek_object_t *obj_b = snek_array_get(b->data.v_array.elements, i);
					snek_array_set(array_object, i, obj_b);
				}
				return array_object;
			}
		default:
			return NULL;

	}
}

int snek_length(snek_object_t *obj) {
	if (obj == NULL) {
		return -1;
	}
	if (obj->kind == INTEGER) {
		return 1;
	}
	if (obj->kind == FLOAT) {
		return 1;
	}
	if (obj->kind == STRING) {
		return strlen(obj->data.v_string);
	}
	if (obj->kind == VECTOR3) {
		return 3;
	}
	if (obj->kind == ARRAY) {
		return obj->data.v_array.size;
	}
	return -1;
}

snek_object_t *snek_array_get(snek_object_t *snek_object, size_t index) {
	if (snek_object == NULL) {
		return NULL;
	} else if (snek_object->kind != ARRAY) {
		return NULL;
	} else if (snek_object->data.v_array.size < index) {
		return NULL;
	}
	return snek_object->data.v_array.elements[index];
}


bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
	if (array == NULL || value == NULL) {
		return false;
	} else if (array->kind != ARRAY) {
		return false;
	} else if (array->data.v_array.size < index) {
		return false;
	}
	array->data.v_array.elements[index] = value;
	return true;
}

snek_object_t *new_snek_array(size_t size) {
	snek_object_t *new_array_obj = malloc(sizeof(snek_object_t));
	if (new_array_obj == NULL) { return NULL; }
	snek_object_t **ptr_array = calloc(size, sizeof(snek_object_t *));
	new_array_obj->kind = ARRAY;
	snek_array_t new_array = {.size = size, .elements = ptr_array}; 
	new_array_obj->data = (snek_object_data_t){.v_array = new_array};
	return new_array_obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z) {
	if (x == NULL || y == NULL || z == NULL) { return NULL; }
	snek_object_t *new_vector_obj = malloc(sizeof(snek_object_t));
	if (new_vector_obj == NULL) { return NULL; }
	new_vector_obj->kind = VECTOR3;
	new_vector_obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
	return new_vector_obj;
}
	
snek_object_t *new_snek_string(char *value) {
	snek_object_t ptr_str_obj = malloc(sizeof(snek_object_t));
	if (ptr_str_obj == NULL) { return NULL; }
	size_t len = strlen(value) + 1;
	char *string = malloc(sizeof(char *) * len);
	if (string == NULL) { 
		free(ptr_str_obj);
		return NULL; 
	}
	strcpy(string, value);
	ptr_str_obj->kind = STRING;
	ptr_str_obj->data = (snek_object_data_t) {.v_string = string};
	return ptr_str_obj;
}
	

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
