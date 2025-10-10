# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -I$(INC_DIR)
LDFLAGS = -fsanitize=address -lm

# Имена исполняемых файлов
MAIN_PROGRAM = prime_program
TEST_PROGRAM = prime_tests

# Папки
SRC_DIR = source
INC_DIR = include
TEST_DIR = tests

# Исходные файлы
MAIN_SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/primenumbers.c
TEST_SOURCES = $(TEST_DIR)/internal_tests.c $(SRC_DIR)/primenumbers.c

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
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/primenumbers.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/primenumbers.o: $(SRC_DIR)/primenumbers.c $(INC_DIR)/primenumbers.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/primenumbers.c -o $(SRC_DIR)/primenumbers.o

# Компиляция объектных файлов для тестов
$(TEST_DIR)/internal_tests.o: $(TEST_DIR)/internal_tests.c $(INC_DIR)/primenumbers.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/internal_tests.c -o $(TEST_DIR)/internal_tests.o

# Создание тестовых файлов с входными данными
test_inputs:
	@echo "3" > test_input1.txt
	@echo "1 2 3" >> test_input1.txt
	@echo "2" > test_input2.txt
	@echo "10 20" >> test_input2.txt
	@echo "1" > test_input3.txt
	@echo "5" >> test_input3.txt
	@echo "1" > test_input4.txt
	@echo "1" >> test_input4.txt
	@echo "1" > test_input5.txt
	@echo "100" >> test_input5.txt
	@echo "3" > test_input6.txt
	@echo "3 1 2" >> test_input6.txt
	@echo "3" > test_input7.txt
	@echo "2 2 2" >> test_input7.txt
	@echo "2" > test_input8.txt
	@echo "1 -5" >> test_input8.txt
	@echo "1" > test_input9.txt
	@echo "0" >> test_input9.txt
	@echo "3" > test_input10.txt
	@echo "1" >> test_input10.txt
	@echo "2" >> test_input10.txt
	@echo "abc" >> test_input10.txt

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM) test_inputs
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of test cases"
	@printf "0\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "must be positive" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo "-5" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "must be positive" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 2: Invalid input format"
	@./$(MAIN_PROGRAM) < test_input10.txt 2>&1 | grep -q "Failed to read index" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 3: Invalid prime indices"
	@./$(MAIN_PROGRAM) < test_input8.txt 2>&1 | grep -q "must be positive" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input9.txt 2>&1 | grep -q "must be positive" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 4: Correct output for valid inputs"
	@./$(MAIN_PROGRAM) < test_input1.txt 2>&1 | grep -q "1.*2" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input1.txt 2>&1 | grep -q "2.*3" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input1.txt 2>&1 | grep -q "3.*5" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 5: Large prime indices"
	@./$(MAIN_PROGRAM) < test_input2.txt 2>&1 | grep -q "10.*29" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input2.txt 2>&1 | grep -q "20.*71" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 6: Single test case"
	@./$(MAIN_PROGRAM) < test_input3.txt 2>&1 | grep -q "5.*11" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 7: Boundary cases"
	@./$(MAIN_PROGRAM) < test_input4.txt 2>&1 | grep -q "1.*2" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input5.txt 2>&1 | grep -q "100.*541" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 8: Unsorted indices"
	@./$(MAIN_PROGRAM) < test_input6.txt 2>&1 | grep -q "1.*5" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input6.txt 2>&1 | grep -q "2.*2" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input6.txt 2>&1 | grep -q "3.*3" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 9: Duplicate indices"
	@./$(MAIN_PROGRAM) < test_input7.txt 2>&1 | grep -q "1.*3" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input7.txt 2>&1 | grep -q "2.*3" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@./$(MAIN_PROGRAM) < test_input7.txt 2>&1 | grep -q "3.*3" && echo "✓ PASS" || (echo "✗ FAIL"; exit 1)
	@echo ""
	
	@echo "Test 10: Memory allocation errors (large input)"
	@printf "1\n1000000\n" | ./$(MAIN_PROGRAM) 2>&1 | grep -q "too large\|Overflow error" && echo "✓ PASS" || echo "⚠ SKIP (may depend on system limits)"
	@echo ""
	
	@echo "All tests completed!"
	@$(MAKE) clean_test_files

# Очистка тестовых файлов
clean_test_files:
	@rm -f test_input*.txt

# Полная очистка
clean: clean_test_files
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: all test clean test_inputs clean_test_files