#include "vm.h"
#include "snekobject.h"
#include "stack.h"


void trace(vm_t *vm) {
	if (vm == NULL) { return; }
	stack_t *gray_objects = stack_new(8);
	if (gray_objects == NULL) { return; }
	for (size_t i = 0; i < vm->objects->count; i++) {
		snek_object_t *obj = vm->objects->data[i];
		if (obj->is_marked == true) {
			stack_push(gray_objects, (void *)obj);
		}
	}
	while (gray_objects->count > 0) {
		snek_object_t *new_obj = stack_pop(gray_objects);
		trace_blacken_object(gray_objects, new_obj);
	}
	stack_free(gray_objects);
}

void trace_blacken_object(stack_t *gray_objects, snek_object_t *obj) {
	switch (obj->kind) {
		case INTEGER:
		case FLOAT:
		case STRING:
			break;
		case VECTOR3:
			{
				snek_vector_t vec = obj->data.v_vector3;
				trace_mark_object(gray_objects, vec.x);
				trace_mark_object(gray_objects, vec.y);
				trace_mark_object(gray_objects, vec.z);
				break;
			}
		case ARRAY:
			{
				snek_array_t arr = obj->data.v_array; 
				for (size_t i = 0; i < arr.size; i++) {
					trace_mark_object(gray_objects, arr.elements[i]);
				}
				break;
			}
	}
}

void trace_mark_object(stack_t *gray_objects, snek_object_t *obj) {
	if (obj == NULL || obj->is_marked == true) { return; }
	obj->is_marked = true;
	stack_push(grey_objects, (void *)obj);
}

void mark(vm_t *vm) {
	if (vm == NULL) { return; }
	for (size_t i = 0; i < vm->frames->count; i++) {
		frame_t *frame = vm->frames->data[i];
		for (size_t j = 0; j < frame->references->count; j++) {
			snek_object_t *obj = frame->references->data[j];
			obj->is_marked = true;
		}
	}
}

void frame_reference_object(frame_t *frame, snek_object_t *obj) {
	if (frame == NULL || obj == NULL) { return; }
	stack_push(frame->references, (void *)obj);

}

void vm_free(vm_t *vm) {
	if (vm == NULL) { return; }
	stack_t *frames = &vm->frames;
	stack_t *objs = &vm->objects;
	for (size_t i = 0; i < frames->count; i++) {
		free_frame(frames->data[i]);
	}
	stack_free(frames);

	for (size_t i = 0; i < objs->count; i++) {
		snek_object_free(objs->data[i]);
	}
	stack_free(objs);
	free(vm);
}

void vm_track_object(vm_t *vm, snek_object_t *obj) {
	if (vm == NULL || obj == NULL) { return; }
	stack_push(vm->objects, (void *)obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
	if (vm == NULL || frame == NULL) { return; }
	stack_push(vm->frames, (void *)frame);
}

frame_t *vm_new_frame(vm_t *vm) {
	frame_t *frame = malloc(sizeof(frame_t));
	if (frame == NULL) { return NULL; }
	frame->references = stack_new(8);
	if (frame->references == NULL) {
		free(frame);
		return NULL;
	}

	vm_frame_push(vm, frame);
	return frame;
}

void frame_free(frame_t *frame) {
	if (frame == NULL) { return; }
	stack_free(frame->references);
	free(free);
}


vm_t *vm_new(void) {
	vm_t *vm = malloc(sizeof(vm_t));
	if (vm == NULL) { return NULL; }
	vm->frames = stack_new(8);
	if (vm->frames == NULL) {
		free(vm);
		return NULL;
	}

	vm->objects = stack_new(8);
	if (vm->objects == NULL) {
		free(vm);
		return NULL;
	}

	return vm;
}

void vm_free(vm_t *vm) {
	if (vm == NULL) { return; }
	stack_free(vm->frames);
	stack_free(vm->objects);
	free(vm);
}
