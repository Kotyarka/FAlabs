CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

MAIN_SOURCES = main.c numbers.c
TEST_SOURCES = internal_tests.c numbers.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: main.c numbers.h
	$(CC) $(CFLAGS) -c main.c

numbers.o: numbers.c numbers.h
	$(CC) $(CFLAGS) -c numbers.c

internal_tests.o: internal_tests.c numbers.h
	$(CC) $(CFLAGS) -c internal_tests.c

test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt 2>&1 | grep -q "Usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt output.txt extra 2>&1 | grep -q "Usage:" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: File operations"
	@echo "Testing non-existent input file:"
	@./$(MAIN_PROGRAM) nonexistent.txt output.txt 2>&1 | grep -q "Cannot open input file" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing invalid output file:"
	@./$(MAIN_PROGRAM) input.txt /invalid/path/output.txt 2>&1 | grep -q "Cannot open output file" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Valid number processing"
	@echo "101\nFF\n0\nStop" > test_input1.txt
	@./$(MAIN_PROGRAM) test_input1.txt test_output1.txt 2>&1 | grep -q "successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking output file content:"
	@cat test_output1.txt | grep -q "101 2 5" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output1.txt | grep -q "FF 16 255" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output1.txt | grep -q "0 2 0" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Error handling"
	@echo "12$3\n101\nStop" > test_input2.txt
	@./$(MAIN_PROGRAM) test_input2.txt test_output2.txt 2>&1 | grep -q "Invalid number format" && echo "✓ PASS" || echo "✗ FAIL"
	@test ! -f test_output2.txt && echo "✓ PASS (output file deleted on error)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Empty input file"
	@echo "" > test_input3.txt
	@./$(MAIN_PROGRAM) test_input3.txt test_output3.txt 2>&1 | grep -q "No numbers found" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Negative numbers"
	@echo "-1A\n-101\nStop" > test_input4.txt
	@./$(MAIN_PROGRAM) test_input4.txt test_output4.txt 2>&1 | grep -q "successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output4.txt | grep -q "-1A 11 -21" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output4.txt | grep -q "-101 2 -5" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Cleaning up test files..."
	@rm -f test_input*.txt test_output*.txt
	
	@echo "All tests completed!"

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o test_input*.txt test_output*.txt

.PHONY: all test clean