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
					int sum = a->data.v_int + b->data.v_int;
					return new_snek_integer(sum);
				} else if (b->kind == FLOAT) {
					float sum = (float)a->data.v_int + b->data.v_float;
					return new_snek_float(sum);
				} else {
					return NULL;
				}
			}
		case FLOAT:
			{
				if (b->kind == FLOAT) {
					float sum = a->data.v_float + b->data.v_float;
					return new_snek_float(sum);
				} else if (b->kind == INTEGER) {
					float sum = a->data.v_float + (float)b->data.v_int;
					return new_snek_float(sum);
				} else {
					return NULL;
				}
			}
		case STRING:
			{
				if (b->kind != STRING) {
					return NULL;
				}
				int len = snek_length(a) + snek_length(b) + 1;
				char *string = calloc(len, sizeof(char *));
				strcat(a->data.v_string, b->data.v_string);
				strcat(string, a->data.v_string);
				snek_object_t *obj = new_snek_string(string);
				free(string);
				return obj;
			}
		case VECTOR3:
			{
				snek_vector_t vec_a = a->data.v_vector3; 
				snek_vector_t vec_b = b->data.v_vector3;
				if (b->kind != VECTOR3) {
					return NULL;
				}
				snek_object_t *obj = new_snek_vector3(snek_add(vec_a.x, vec_b.x), snek_add(vec_a.y, vec_b.y), snek_add(vec_a.z, vec_b.z));
				return obj;
			}
		case ARRAY:
			{
				snek_array_t arr_a = a->data.v_array;
				snek_array_t arr_b = b->data.v_array;
				if (b->kind != ARRAY) {
					return NULL;
				}
				snek_object_t *obj = new_snek_array(arr_a.size + arr_b.size);
				for (int i = 0; i < arr_a.size; i++) {
					snek_object_t *obj_a = snek_array_get(arr_a.elements, i);
					snek_array_set(obj, i, obj_a);

				}
				for (int i = 0; i < arr_b.size; i++) {
					snek_object_t *obj_b = snek_array_get(arr_b.elements, i);
					snek_array_set(obj, i + arr_a.size, obj_b);
				}
				return obj;
			}
		default:
			return NULL;

	}
}

int snek_length(snek_object_t *obj) {
	if (obj == NULL) {
		return -1;
	} else if (obj->kind == INTEGER) {
		return 1;
	} else if (obj->kind == FLOAT) {
		return 1;
	} else if (obj->kind == STRING) {
		return strlen(obj->data.v_string);
	} else if (obj->kind == VECTOR3) {
		return 3;
	} else if (obj->kind == ARRAY) {
		return obj->data.v_array.size;
	} else { return -1; }
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
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) { return NULL; }
	snek_object_t **ptr = calloc(size, sizeof(snek_object_t *));
	obj->kind = ARRAY;
	snek_array_t arr = {.size = size, .elements = ptr}; 
	obj->data = (snek_object_data_t){.v_array = arr};
	return obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z) {
	if (x == NULL || y == NULL || z == NULL) { return NULL; }
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) { return NULL; }
	obj->kind = VECTOR3;
	obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
	return obj;
}
	
snek_object_t *new_snek_string(char *value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) { return NULL; }
	size_t len = strlen(value) + 1;
	char *str = malloc(sizeof(char *) * len);
	if (str == NULL) { 
		free(obj);
		return NULL; 
	}
	strcpy(str, value);
	obj->kind = STRING;
	obj->data = (snek_object_data_t) {.v_string = string};
	return obj;
}
	

snek_object_t *new_snek_float(float value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) { return NULL; }
	obj->kind = FLOAT;
	obj->data = (snek_object_data_t) {.v_float = value};
	return obj;
}


snek_object_t *new_snek_integer(int value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL)  {
		return NULL;
	}
	obj->kind = INTEGER;
	obj->data = (snek_object_data_t){.v_int = value};
	return obj;
}
