# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address

# Директории
SRC_DIR = source
INC_DIR = include
TEST_DIR = tests

# Имена исполняемых файлов
MAIN_PROGRAM = number_converter
TEST_PROGRAM = internal_tests

# Исходные файлы
MAIN_SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/numbers.c
TEST_SOURCES = $(TEST_DIR)/internal_tests.c $(SRC_DIR)/numbers.c

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
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/numbers.o: $(SRC_DIR)/numbers.c $(INC_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/numbers.c -o $(SRC_DIR)/numbers.o

# Компиляция объектных файлов для тестов
$(TEST_DIR)/internal_tests.o: $(TEST_DIR)/internal_tests.c $(INC_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(TEST_DIR)/internal_tests.c -o $(TEST_DIR)/internal_tests.o

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Wrong number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) input.txt output.txt extra 2>&1 | grep -q "Wrong value of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: File opening errors"
	@./$(MAIN_PROGRAM) nonexistent.txt output.txt 2>&1 | grep -q "opening input file" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Normal operation with various number systems"
	@echo "101 777 abc 0 z 123" > test_input.txt
	@./$(MAIN_PROGRAM) test_input.txt test_output.txt
	@echo "Checking binary (101):"
	@grep -q "101 2 5" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking octal (777):"
	@grep -q "777 8 511" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking base-13 (abc):"
	@grep -q "abc 13" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking zero (0):"
	@grep -q "0 2 0" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking base-36 (z):"
	@grep -q "z 36 35" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking base-4 (123):"
	@grep -q "123 4 27" test_output.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Leading zeros removal"
	@echo "000123 00ABC 0000" > test_input2.txt
	@./$(MAIN_PROGRAM) test_input2.txt test_output2.txt
	@echo "Checking leading zeros removal:"
	@grep -q "123 4 27" test_output2.txt && echo "✓ PASS" || echo "✗ FAIL"
	@grep -q "ABC 13" test_output2.txt && echo "✓ PASS" || echo "✗ FAIL"
	@grep -q "0 2 0" test_output2.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Overflow handling"
	@echo "FFFFFFFFFFFFFFFFFFFF" > test_input3.txt
	@./$(MAIN_PROGRAM) test_input3.txt test_output3.txt
	@echo "Checking overflow:"
	@grep -q "overflow" test_output3.txt && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Invalid characters"
	@echo "12#4 5!6" > test_input4.txt
	@./$(MAIN_PROGRAM) test_input4.txt test_output4.txt 2>&1 | grep -q "cannot be represented" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 7: Whitespace handling"
	@printf "123\n456\t789  abc" > test_input5.txt
	@./$(MAIN_PROGRAM) test_input5.txt test_output5.txt
	@echo "Checking whitespace handling:"
	@test $$(wc -l < test_output5.txt) -eq 4 && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "All tests completed!"
	@rm -f test_*.txt

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(SRC_DIR)/*.o $(TEST_DIR)/*.o test_*.txt

.PHONY: all test clean
