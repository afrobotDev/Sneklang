#include "snekobject.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool snek_array_set(snek_object_t *snek_obj, size_t index,
                    snek_object_t *value) {
  snek_array_t arr = snek_obj->data.v_array;
  if (snek_obj == NULL || value == NULL) {
    return false;
  }
  if (snek_obj->kind != ARRAY) {
    return false;
  }
  if (index >= arr.size) {
    return false;
  }
  refcount_inc(value); 
  if (arr.elements != NULL) {
	  refcount_dec(arr.elements[index]);
  }
  arr.elements[index] = value;
  return true;
}


snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }
  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
  refcount_inc(x);
  refcount_inc(y);
  refcount_inc(z);
  return obj;
}


void refcount_dec(snek_object_t *obj) {
	if (obj == NULL) { return; }
	obj->refcount--;
	if (obj->refcount == 0) {
		refcount_free(obj);
	}
}

void refcount_free(snek_object_t *obj) {
	if (obj->kind == INTEGER || obj->kind == FLOAT) {
		free(obj);
	} else if (obj->kind == STRING) {
		free(obj->data.v_string);
		free(obj);
	} else if (obj->kind == VECTOR3) {
		snek_vector_t vec = obj->data.v_vector3;
		refcount_dec(vec.x);
		refcount_dec(vec.y);
		refcount_dec(vec.z);
	} else if (obj->kind == ARRAY) {
		snek_array_t *arr = &obj->data.v_array;
		for (size_t i = 0; i < arr.size; i++) {
			refcount_dec(arr.elements[i]);
		}
		free(arr.elements);
	}else { return; }
}

void refcount_inc(snek_object_t *obj) {
	if (obj == NULL) { return; }
	obj->refcount++;
}

snek_object_t *_new_snek_object(void) {
	snek_object *obj = calloc(1, sizeof(snek_object_t));
	if (obj == NULL) { return NULL; }
	obj->refcount = 1;
	return obj;
}


snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};

  return obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}

