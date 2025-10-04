# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g -Iinclude
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Папки
SRC_DIR = source
INC_DIR = include
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
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/flags.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/flags.o: $(SRC_DIR)/flags.c $(INC_DIR)/flags.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/flags.c -o $(SRC_DIR)/flags.o

# Компиляция объектных файлов для тестов
$(TEST_DIR)/internal_tests.o: $(TEST_DIR)/internal_tests.c $(INC_DIR)/flags.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/internal_tests.c -o $(TEST_DIR)/internal_tests.o

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -h 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -h 123 extra 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid flags"
	@./$(MAIN_PROGRAM) -x 123 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) /z 456 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) --h 789 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Invalid numbers"
	@./$(MAIN_PROGRAM) -h "123abc" 2>&1 | grep -q "Invalid number" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -p "12.34" 2>&1 | grep -q "Invalid number" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Correct flag -h (multiples)"
	@./$(MAIN_PROGRAM) -h 10 2>&1 | grep -q "Multiples of 10" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -h 101 2>&1 | grep -q "No multiples" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -h 0 2>&1 | grep -q "cannot be zero" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Correct flag -p (prime)"
	@./$(MAIN_PROGRAM) -p 7 2>&1 | grep -q "is prime" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -p 10 2>&1 | grep -q "is composite" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -p 1 2>&1 | grep -q "neither prime nor composite" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -p 0 2>&1 | grep -q "must be positive" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Correct flag -s (hexadecimal)"
	@./$(MAIN_PROGRAM) -s 255 2>&1 | grep -q "F F" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -s 0 2>&1 | grep -q "0" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -s -255 2>&1 | grep -q "- F F" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 7: Correct flag -e (powers table)"
	@./$(MAIN_PROGRAM) -e 3 2>&1 | grep -q "1" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -e 0 2>&1 | grep -q "between 1 and 10" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -e 11 2>&1 | grep -q "between 1 and 10" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 8: Correct flag -f (factorial)"
	@./$(MAIN_PROGRAM) -f 5 2>&1 | grep -q "120" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -f 0 2>&1 | grep -q "1" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -f -5 2>&1 | grep -q "positive numbers" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 9: Correct flag -a (sum)"
	@./$(MAIN_PROGRAM) -a 5 2>&1 | grep -q "15" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -a 10 2>&1 | grep -q "55" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -a 0 2>&1 | grep -q "positive numbers" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: all test clean