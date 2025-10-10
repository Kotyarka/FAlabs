CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -Iinclude
LDFLAGS = -fsanitize=address -lm

SRC_DIR = source
INCLUDE_DIR = include
TEST_DIR = tests

MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

MAIN_SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/functions.c
TEST_SOURCES = $(TEST_DIR)/internal_tests.c $(SRC_DIR)/functions.c

MAIN_OBJECTS = main.o functions.o
TEST_OBJECTS = internal_tests.o functions.o

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/functions.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o main.o

functions.o: $(SRC_DIR)/functions.c $(INCLUDE_DIR)/functions.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/functions.c -o functions.o

internal_tests.o: $(TEST_DIR)/internal_tests.c $(INCLUDE_DIR)/functions.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/internal_tests.c -o internal_tests.o

test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running main program tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) 0.001 extra_arg 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid epsilon format"
	@./$(MAIN_PROGRAM) "abc" 2>&1 | grep -q "Type correct epsilon" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) "0.001abc" 2>&1 | grep -q "Type correct epsilon" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Valid epsilon calculation"
	@./$(MAIN_PROGRAM) 0.0001 2>&1 | grep -q "log(1 + x) / x:" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) 0.0001 2>&1 | grep -q "exp(-x \* x \* 0.5):" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) 0.0001 2>&1 | grep -q -- "-log(1 - x):" && echo "✓ PASS" || echo "✗ FAIL"  # ← исправлено
	@./$(MAIN_PROGRAM) 0.0001 2>&1 | grep -q "pow(x, x):" && echo "✓ PASS" || echo "✗ FAIL"	
	@echo ""
	
	
	@echo "All tests completed!"

test-internal: $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)

run: $(MAIN_PROGRAM)
	@echo "=== Running main program with epsilon=0.0001 ==="
	./$(MAIN_PROGRAM) 0.0001

clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(MAIN_PROGRAM) $(TEST_PROGRAM)

clean-bin:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM)

clean-obj:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS)

tree:
	@echo "Project structure:"
	@echo "."
	@echo "├── Makefile"
	@echo "├── include/"
	@echo "│   └── functions.h"
	@echo "├── source/"
	@echo "│   ├── main.c"
	@echo "│   └── functions.c"
	@echo "├── tests/"
	@echo "│   └── internal_tests.c"
	@echo "├── main.o"
	@echo "├── functions.o"
	@echo "├── internal_tests.o"
	@echo "├── program"
	@echo "└── internal_tests"

.PHONY: all test test-internal run clean clean-bin clean-obj tree