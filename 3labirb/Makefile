# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Директории
SRC_DIR = source
INCLUDE_DIR = include
TEST_DIR = tests

# Исходные файлы
MAIN_SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/flags.c
TEST_SOURCES = $(TEST_DIR)/internal_tests.c $(SRC_DIR)/flags.c

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
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/flags.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(SRC_DIR)/flags.o: $(SRC_DIR)/flags.c $(INCLUDE_DIR)/flags.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Компиляция объектных файлов для тестов
$(TEST_DIR)/internal_tests.o: $(TEST_DIR)/internal_tests.c $(INCLUDE_DIR)/flags.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid flag"
	@./$(MAIN_PROGRAM) -x 2>&1 | grep -q "Error occurred" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: -q flag with wrong arguments"
	@./$(MAIN_PROGRAM) -q 2>&1 | grep -q "Wrong value of arguments for -q" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -q 0.1 2>&1 | grep -q "Wrong value of arguments for -q" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: -m flag with wrong arguments"
	@./$(MAIN_PROGRAM) -m 2>&1 | grep -q "Wrong value of arguments for -m" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: -t flag with wrong arguments"
	@./$(MAIN_PROGRAM) -t 2>&1 | grep -q "Wrong value of arguments for -t" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Valid -m flag usage"
	@./$(MAIN_PROGRAM) -m 10 5 2>&1 | grep -q "is multiple" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -m 10 3 2>&1 | grep -q "is not multiple" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 7: Valid -t flag usage"
	@./$(MAIN_PROGRAM) -t 0.001 3 4 5 2>&1 | grep -q "can be sides of a right triangle" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -t 0.001 2 3 4 2>&1 | grep -q "cannot be sides of a right triangle" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 8: Invalid number format"
	@./$(MAIN_PROGRAM) -m abc 10 2>&1 | grep -q "numbers must be valid integers" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -q 0.1 abc 2 3 2>&1 | grep -q "coefficient must be a valid number" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM)
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o

.PHONY: all test clean