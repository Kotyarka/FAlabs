CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

MAIN_SOURCES = source/main.c source/numbers.c
TEST_SOURCES = tests/internal_tests.c source/numbers.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

source/main.o: source/main.c include/numbers.h
	$(CC) $(CFLAGS) -Iinclude -c source/main.c -o source/main.o

source/numbers.o: source/numbers.c include/numbers.h
	$(CC) $(CFLAGS) -Iinclude -c source/numbers.c -o source/numbers.o

tests/internal_tests.o: tests/internal_tests.c include/numbers.h
	$(CC) $(CFLAGS) -Iinclude -c tests/internal_tests.c -o tests/internal_tests.o

test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt 2>&1 | grep -q "usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt output.txt extra 2>&1 | grep -q "usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: File operations"
	@echo "Testing non-existent input file:"
	@./$(MAIN_PROGRAM) nonexistent.txt output.txt 2>&1 | grep -q "Cannot open input file" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) nonexistent.txt output.txt 2>&1)
	@echo "Testing invalid output file:"
	@./$(MAIN_PROGRAM) test_input1.txt /invalid/path/output.txt 2>&1 | grep -q "Cannot open output file" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) test_input1.txt /invalid/path/output.txt 2>&1)
	@echo ""
	
	@echo "Test 3: Valid number processing"
	@echo "101" > test_input1.txt
	@echo "FF" >> test_input1.txt
	@echo "0" >> test_input1.txt
	@echo "Stop" >> test_input1.txt
	@./$(MAIN_PROGRAM) test_input1.txt test_output1.txt 2>&1 | grep -q "successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking output file content:"
	@cat test_output1.txt | grep -q "101 2 5" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output1.txt | grep -q "FF 16 255" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output1.txt | grep -q "0 2 0" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Error handling"
	@echo "12\$3" > test_input2.txt
	@echo "101" >> test_input2.txt
	@echo "Stop" >> test_input2.txt
	@./$(MAIN_PROGRAM) test_input2.txt test_output2.txt 2>&1 | grep -q "Invalid number format" && echo "✓ PASS" || echo "✗ FAIL"
	@test ! -f test_output2.txt && echo "✓ PASS (output file deleted on error)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Empty input file"
	@echo "" > test_input3.txt
	@./$(MAIN_PROGRAM) test_input3.txt test_output3.txt 2>&1 | grep -q "No numbers found" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Negative numbers"
	@echo "-1A" > test_input4.txt
	@echo "-101" >> test_input4.txt
	@echo "Stop" >> test_input4.txt
	@./$(MAIN_PROGRAM) test_input4.txt test_output4.txt 2>&1 | grep -q "successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output4.txt | grep -q "-1A" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output4.txt | grep -q "-101" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Cleaning up test files..."
	@rm -f test_input*.txt test_output*.txt
	
	@echo "All tests completed!"

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) source/*.o tests/*.o test_input*.txt test_output*.txt

.PHONY: all test clean