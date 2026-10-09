CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -I.

LIB_SRCS := cBasics/welcome_to_mem.c cBasics/functions.c cBasics/unittest_alpha.c cBasics/mathops.c cBasics/if_state.c

TEST_DIR := tests
TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)

.PHONY: test clean
test: $(TEST_SRCS:.c=)
	@for t in $(TEST_SRCS:.c=); do echo "==> $$t"; ./$$t || exit 1; done

$(TEST_DIR)/test_%: $(TEST_DIR)/test_%.c $(LIB_SRCS) $(TEST_DIR)/munit.c
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ $< $(LIB_SRCS) $(TEST_DIR)/munit.c

clean:
	rm -f $(TEST_SRCS:.c=)
