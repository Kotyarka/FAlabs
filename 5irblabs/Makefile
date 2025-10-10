# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -I./include
LDFLAGS = -fsanitize=address

# Имена исполняемых файлов
MAIN_PROGRAM = program
TEST_PROGRAM = internal_tests

# Исходные файлы
MAIN_SOURCES = source/main.c source/flags.c
TEST_SOURCES = tests/internal_tests.c source/flags.c

# Правило по умолчанию
all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

# Сборка основной программы
$(MAIN_PROGRAM): $(MAIN_SOURCES)
	$(CC) $(CFLAGS) -o $(MAIN_PROGRAM) $(MAIN_SOURCES) $(LDFLAGS)

# Сборка тестовой программы
$(TEST_PROGRAM): $(TEST_SOURCES)
	$(CC) $(CFLAGS) -o $(TEST_PROGRAM) $(TEST_SOURCES) $(LDFLAGS)

# Запуск тестов
test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid number of arguments"
	@./$(MAIN_PROGRAM) 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) -d input.txt output.txt extra 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 2: Invalid flag"
	@./$(MAIN_PROGRAM) -x input.txt 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@./$(MAIN_PROGRAM) /x input.txt 2>&1 | grep -q "Invalid flag" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 3: Missing output file for -n flag"
	@./$(MAIN_PROGRAM) -nd input.txt 2>&1 | grep -q "Wrong number of arguments" && echo "✓ PASS" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: File operations with -d flag (remove digits)"
	@echo "Hello123 World456" > test_input_d.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -d test_input_d.txt test_output_d.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@cat test_output_d.txt 2>/dev/null | grep -q "Hello World" && echo "✓ Content correct" || echo "✗ Content incorrect"
	@rm -f test_input_d.txt test_output_d.txt
	
	@echo "Test 5: File operations with -i flag (count letters)"
	@echo "Hello123 World" > test_input_i1.txt
	@echo "Test456" >> test_input_i1.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -i test_input_i1.txt test_output_i1.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@cat test_output_i1.txt 2>/dev/null | head -n1 | grep -q "10" && echo "✓ First line count correct" || echo "✗ First line count incorrect"
	@cat test_output_i1.txt 2>/dev/null | tail -n1 | grep -q "4" && echo "✓ Second line count correct" || echo "✗ Second line count incorrect"
	@rm -f test_input_i1.txt test_output_i1.txt
	
	@echo "Test 6: File operations with -s flag (count special chars)"
	@echo "Hello!@# World$$%" > test_input_s.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -s test_input_s.txt test_output_s.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@cat test_output_s.txt 2>/dev/null | head -n1 | grep -q "5" && echo "✓ Special chars count correct" || echo "✗ Special chars count incorrect"
	@rm -f test_input_s.txt test_output_s.txt
	
	@echo "Test 7: File operations with -a flag (hex conversion)"
	@echo "AB12" > test_input_a.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -a test_input_a.txt test_output_a.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@cat test_output_a.txt 2>/dev/null | grep -q "12" && echo "✓ Digits preserved" || echo "✗ Digits not preserved"
	@cat test_output_a.txt 2>/dev/null | grep -q "4142" && echo "✓ Hex conversion correct" || echo "✗ Hex conversion incorrect"
	@rm -f test_input_a.txt test_output_a.txt
	
	@echo "Test 8: Automatic output filename"
	@echo "Test content" > input_auto.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -d input_auto.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@test -f "out_input_auto.txt" && echo "✓ Auto file created" || echo "✗ Auto file not created"
	@rm -f input_auto.txt out_input_auto.txt
	
	@echo "Test 9: Custom output filename with -n flag"
	@echo "Test content" > input_custom.txt
	@sleep 0.1
	@./$(MAIN_PROGRAM) -nd input_custom.txt custom_output.txt 2>&1 | grep -q "Doings failed" && echo "✗ FAIL" || echo "✓ PASS"
	@sleep 0.1
	@test -f "custom_output.txt" && echo "✓ Custom file created" || echo "✗ Custom file not created"
	@rm -f input_custom.txt custom_output.txt
	
	@echo ""
	@echo "All tests completed!"

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o test_*.txt input_*.txt output_*.txt custom_*.txt out_*.txt

.PHONY: all test clean