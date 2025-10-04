# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Исходные файлы
MAIN_SOURCES = main.c flags.c
TEST_SOURCES = internal_tests.c flags.c

# Объектные файлы
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Правило по умолчанию
all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

# Сборка основной программы
$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

# Сборка тестовой программы
$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

# Компиляция объектных файлов для основной программы
main.o: main.c flags.h
	$(CC) $(CFLAGS) -c main.c

flags.o: flags.c flags.h
	$(CC) $(CFLAGS) -c flags.c

# Компиляция объектных файлов для тестов
internal_tests.o: internal_tests.c flags.h
	$(CC) $(CFLAGS) -c internal_tests.c

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -d 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -d input.txt output.txt extra 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid flags"
	@./$(MAIN_PROGRAM) -x input.txt 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) /z input.txt 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) --d input.txt 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: File operations"
	@echo "Testing non-existent input file:"
	@./$(MAIN_PROGRAM) -d nonexistent.txt 2>&1 | grep -q "Cannot open input file" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing -n flag without output file:"
	@./$(MAIN_PROGRAM) -nd input.txt 2>&1 | grep -q "requires output file name" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Correct flag processing"
	@echo "Hello123World" > test_input.txt
	@echo "Testing -d flag:"
	@./$(MAIN_PROGRAM) -d test_input.txt 2>&1 | grep -q "Successfully processed" && echo "✓ PASS" || echo "✗ FAIL"
	@test -f "out_test_input.txt" && echo "✓ PASS (output file created)" || echo "✗ FAIL"
	@echo "Testing -i flag:"
	@./$(MAIN_PROGRAM) -i test_input.txt 2>&1 | grep -q "Counting letters" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing -n flag with output:"
	@./$(MAIN_PROGRAM) -nd test_input.txt custom_output.txt 2>&1 | grep -q "Successfully processed" && echo "✓ PASS" || echo "✗ FAIL"
	@test -f "custom_output.txt" && echo "✓ PASS (custom output file created)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Output file naming"
	@./$(MAIN_PROGRAM) -s test_input.txt 2>&1 | grep -q "out_test_input.txt" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -na test_input.txt my_output.txt 2>&1 | grep -q "my_output.txt" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Cleaning up test files..."
	@rm -f test_input.txt out_test_input.txt custom_output.txt my_output.txt test_*.txt
	
	@echo "All tests completed!"

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o test_*.txt out_*.txt custom_output.txt my_output.txt

.PHONY: all test clean