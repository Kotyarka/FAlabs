# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = prime_program
TEST_PROGRAM = prime_tests

# Исходные файлы
MAIN_SOURCES = main.c primenumbers.c
TEST_SOURCES = internal_tests.c primenumbers.c

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
main.o: main.c ../include/primenumbers.h
	$(CC) $(CFLAGS) -c main.c

primenumbers.o: primenumbers.c ../include/primenumbers.h
	$(CC) $(CFLAGS) -c primenumbers.c

# Компиляция объектных файлов для тестов
internal_tests.o: internal_tests.c ../include/primenumbers.h
	$(CC) $(CFLAGS) -c internal_tests.c

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of test cases"
	@echo "0" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "-5" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid input format"
	@echo "3" | ./$(MAIN_PROGRAM) <<< "1 2 abc" 2>&1 | grep -q "Failed to read index" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Invalid prime indices"
	@echo "2" | ./$(MAIN_PROGRAM) <<< "1 -5" 2>&1 | grep -q "must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "1" | ./$(MAIN_PROGRAM) <<< "0" 2>&1 | grep -q "must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Correct output for valid inputs"
	@echo "3" | ./$(MAIN_PROGRAM) <<< "1 2 3" 2>&1 | grep -q "1. The 1 prime number is: 2" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "3" | ./$(MAIN_PROGRAM) <<< "1 2 3" 2>&1 | grep -q "2. The 2 prime number is: 3" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "3" | ./$(MAIN_PROGRAM) <<< "1 2 3" 2>&1 | grep -q "3. The 3 prime number is: 5" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Large prime indices"
	@echo "2" | ./$(MAIN_PROGRAM) <<< "10 20" 2>&1 | grep -q "10. The 10 prime number is: 29" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "2" | ./$(MAIN_PROGRAM) <<< "10 20" 2>&1 | grep -q "20. The 20 prime number is: 71" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Memory allocation errors"
	@echo "Testing with very large input..."
	@echo "1" | ./$(MAIN_PROGRAM) <<< "1000000" 2>&1 | grep -q "too large" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o

.PHONY: all test clean