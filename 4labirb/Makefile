# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program

# Директории
SRC_DIR = source
INC_DIR = include
TST_DIR = tests

# Исходные файлы
MAIN_SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/numbers.c

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
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(SRC_DIR)/numbers.o: $(SRC_DIR)/numbers.c $(INC_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@


# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) 0.001 extra_arg 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid epsilon format"
	@./$(MAIN_PROGRAM) "abc" 2>&1 | grep -q "Error occurred" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) "123.45abc" 2>&1 | grep -q "Error occurred" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Invalid epsilon value"
	@./$(MAIN_PROGRAM) "0" 2>&1 | grep -q "epsilon must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) "-0.001" 2>&1 | grep -q "epsilon must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Correct output for valid epsilon"
	@echo "Testing with epsilon=0.001:"
	@./$(MAIN_PROGRAM) "0.001" 2>&1 | grep -q "Calculation using limits" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) "0.001" 2>&1 | grep -q "Calculation using rows" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) "0.001" 2>&1 | grep -q "Calculation using equations" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Very small epsilon"
	@./$(MAIN_PROGRAM) "1e-10" 2>&1 | grep -q "e = " && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(SRC_DIR)/*.o

.PHONY: all test clean