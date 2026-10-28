#pragma once
#include "stack.h"
#include "snekobject.h"

typedef struct VirtualMachine {
  stack_t *frames;
  stack_t *objects;
} vm_t;

typedef struct StackFrame {
  stack_t *references;
} frame_t;

frame_t *vm_new_frame(vm_t *vm);
vm_t *vm_new(void);

void vm_free(vm_t *vm);
void vm_frame_push(vm_t *vm, frame_t *frame);
void vm_track_object(vm_t *vm, snek_object_t *obj);
void frame_free(frame_t *frame);
void frame_reference_object(frame_t *frame, snek_object_t *obj)

