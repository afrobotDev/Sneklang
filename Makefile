CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -I.

LIB_SRCS := cBasics/welcome_to_mem.c cBasics/functions.c cBasics/unittest_alpha.c cBasics/mathops.c cBasics/if_state.c cBasics/for_loop.c cBasics/while_loop.c cBasics/doWhile_loop.c Structs/structs_intro.c Structs/scale_coord.c Pointers/memory.c Pointers/coordinate.c Pointers/pointers_basics.c Pointers/cArrays.c Pointers/array_cast.c Pointers/cString.c Pointers/str_lib.c Pointers/ford_declare.c AdvancedPointers/pointer_pointers.c Enums/switch_case.c Unions/unions_intro.c StackAndHeap/theHeap.c StackAndHeap/malloc.c AdvancedPointers/array_pointers.c AdvancedPointers/void_pointers.c StackAndDataStruct/lowlevel.c StackAndDataStruct/stack_push.c StackAndDataStruct/stack_pop.c Objects/sneklang_int.c

TEST_DIR := tests
TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)

# --- short helpers -----------------------------------------------------
# make r FILE=Pointers/play_ground.c [ARGS=...]   compile+run any .c
# make t T=memory                                 run one test suite
# make t                                          run all test suites
.PHONY: r t

r:
	@tmp=$$(mktemp /tmp/snkr_XXXXXX); \
	$(CC) $(CFLAGS) -o $$tmp $(FILE) && $$tmp; st=$$?; rm -f $$tmp; exit $$st

t: $(if $(T),$(TEST_DIR)/test_$(T),$(TEST_SRCS:.c=))
	@if [ -n "$(T)" ]; then ./$(TEST_DIR)/test_$(T) --show-stderr; \
	else for x in $(TEST_SRCS:.c=); do \
	   echo "==> $$x"; ./$$x --show-stderr || exit 1; \
	done; fi

.PHONY: test clean
test: $(TEST_SRCS:.c=)
	@for t in $(TEST_SRCS:.c=); do echo "==> $$t"; ./$$t --show-stderr || exit 1; done

$(TEST_DIR)/test_%: $(TEST_DIR)/test_%.c $(LIB_SRCS) $(TEST_DIR)/munit.c
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ $< $(LIB_SRCS) $(TEST_DIR)/munit.c

clean:
	rm -f $(TEST_SRCS:.c=)
