# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
LIBS = -lm

# Исходные файлы
SOURCES = source/main.c flags/flags.c
TARGET = program

# Цели по умолчанию
all: $(TARGET)

# Компиляция основной программы
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -I./include $(SOURCES) -o $(TARGET) $(LIBS)

# Запуск тестов
test: $(TARGET)
	@echo "=== ЗАПУСК ТЕСТОВ ==="
	@chmod +x tests/run_tests.sh
	@./tests/run_tests.sh

# Отладочная сборка
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Очистка
clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f */*.o

# Пересборка
rebuild: clean all

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all      - компиляция программы (по умолчанию)"
	@echo "  debug    - отладочная сборка"
	@echo "  test     - запуск всех тестов"
	@echo "  clean    - очистка скомпилированных файлов"
	@echo "  rebuild  - пересборка программы"
	@echo "  help     - показать эту справку"

.PHONY: all test debug clean rebuild help