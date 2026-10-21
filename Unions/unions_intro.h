#pragma once

/* What kind of value an object holds; exactly what unions_intro.c switches on. */
typedef enum {
  INTEGER,
  STRING
} snek_object_kind_t;

/* The shared storage: only one of the two members is meaningful at a time,
 * decided by `kind` in snek_object_t. */
typedef union {
  int v_int;
  char *v_string;
} snek_data_t;

typedef struct {
  snek_object_kind_t kind;
  snek_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer);
snek_object_t new_integer(int i);
snek_object_t new_string(char *str);
