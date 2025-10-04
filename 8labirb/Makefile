# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g -Iinclude
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Исходные файлы
MAIN_SOURCES = source/main.c source/numbers.c
TEST_SOURCES = tests/internal_tests.c source/numbers.c

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

# Компиляция объектных файлов
source/%.o: source/%.c include/numbers.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c include/numbers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Запуск только внутренних тестов (без внешних)
test-internal: $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)

# Запуск только внешних тестов
test-external: $(MAIN_PROGRAM)
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
	
	@echo "Test 3: Invalid number format (program exits on error)"
	@echo "Testing invalid digit for base:"
	@printf "10\n12A\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "too large for base" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Testing wrong symbols in number:"
	@printf "10\n12$3\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong symbols" && echo "✓ PASS" || echo "✗ FAIL"
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
	
	@echo "All external tests completed!"

# Альтернативные тесты с проверкой кодов возврата
test-external-exit-codes: $(MAIN_PROGRAM)
	@echo "=== Testing exit codes ==="
	@echo "Testing invalid base (abc):"
	@echo "abc" | ./$(MAIN_PROGRAM) > /dev/null 2>&1; test $$? -eq 2 && echo "✓ PASS (WRONG_ARGUMENTS)" || echo "✗ FAIL"
	@echo "Testing invalid digit (base 10, number 12A):"
	@printf "10\n12A\n" | ./$(MAIN_PROGRAM) > /dev/null 2>&1; test $$? -eq 3 && echo "✓ PASS (INVALID_DIGIT)" || echo "✗ FAIL"
	@echo "Testing wrong symbols (base 10, number 12\$3):"
	@printf "10\n12\$3\n" | ./$(MAIN_PROGRAM) > /dev/null 2>&1; test $$? -eq 2 && echo "✓ PASS (WRONG_ARGUMENTS)" || echo "✗ FAIL"

# Полный запуск тестов
test: test-internal test-external

# Отладочная сборка тестов
debug-test: CFLAGS += -DDEBUG -O0
debug-test: $(TEST_PROGRAM)
	@echo "=== Running tests with debug output ==="
	./$(TEST_PROGRAM)

# Показать вывод программы для отладки
debug-main: $(MAIN_PROGRAM)
	@echo "=== Debug program output ==="
	@echo "Testing invalid digit (base 10, number 12A):"
	@printf "10\n12A\n" | ./$(MAIN_PROGRAM) 2>&1 || echo "Exit code: $$?"
	@echo ""
	@echo "Testing wrong symbols (base 10, number 12\$3):"
	@printf "10\n12\$3\n" | ./$(MAIN_PROGRAM) 2>&1 || echo "Exit code: $$?"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) source/*.o tests/*.o

.PHONY: all test test-internal test-external test-external-exit-codes debug-test debug-main clean