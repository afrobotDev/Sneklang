#include "vm.h"
#include "snekobject.h"
#include "stack.h"

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
