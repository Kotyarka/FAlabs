# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 -g
LDFLAGS = -fsanitize=address

# Директории
SRC_DIR = source
INCLUDE_DIR = include
TEST_DIR = tests

# Имена исполняемых файлов
MAIN_PROGRAM = number_converter
TEST_PROGRAM = number_tests

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
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/numbers.o: $(SRC_DIR)/numbers.c $(INCLUDE_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/numbers.c -o $(SRC_DIR)/numbers.o

# Компиляция объектных файлов для тестов
$(TEST_DIR)/internal_tests.o: $(TEST_DIR)/internal_tests.c $(INCLUDE_DIR)/numbers.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(TEST_DIR)/internal_tests.c -o $(TEST_DIR)/internal_tests.o

# Запуск тестов
test: $(TEST_PROGRAM)
	@echo "=== Running Integration Tests ==="
	./$(TEST_PROGRAM)

# Очистка
clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(SRC_DIR)/*.o $(TEST_DIR)/*.o test_input_*.txt test_output_*.txt

.PHONY: all test clean
