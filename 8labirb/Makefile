# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Исходные файлы
MAIN_SOURCES = main.c numbers.c
TEST_SOURCES = internal_tests.c numbers.c

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
main.o: main.c numbers.h
	$(CC) $(CFLAGS) -c main.c

numbers.o: numbers.c numbers.h
	$(CC) $(CFLAGS) -c numbers.c

# Компиляция объектных файлов для тестов
internal_tests.o: internal_tests.c numbers.h
	$(CC) $(CFLAGS) -c internal_tests.c

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid base input"
	@echo "Testing non-numeric base:"
	@echo "abc" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong symbols" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing base out of range:"
	@echo "1" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong base" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing too large base:"
	@echo "37" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong base" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Valid base and number processing"
	@echo "Testing base 16 with valid numbers:"
	@printf "16\nFF\n2A\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Max absolute number" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing base 2 with valid numbers:"
	@printf "2\n1010\n1101\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Max absolute number" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Invalid number format"
	@echo "Testing invalid digit for base:"
	@printf "10\n12A\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "too much for this base" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing wrong symbols in number:"
	@printf "10\n12$3\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "wrong symbols" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Negative numbers handling"
	@printf "16\n-FF\n1A\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Max absolute number" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Base conversion output"
	@printf "16\nFF\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "9-base:" && echo "✓ PASS" || echo "✗ FAIL"
	@printf "16\nFF\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "18-base:" && echo "✓ PASS" || echo "✗ FAIL"
	@printf "16\nFF\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "27-base:" && echo "✓ PASS" || echo "✗ FAIL"
	@printf "16\nFF\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "36-base:" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Empty input handling"
	@printf "16\nStop\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "No numbers entered" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o

.PHONY: all test clean