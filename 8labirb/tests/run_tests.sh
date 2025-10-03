#!/bin/bash

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Пути
PROGRAM="../program"
TESTS_FILE="all_tests.txt"

# Функция для запуска тестов из секции
run_test_section() {
    local section_name="$1"
    local test_count=0
    local passed_count=0
    
    echo -e "${BLUE}=== $section_name ===${NC}"
    
    # Ищем начало секции и читаем до следующей секции или конца файла
    while IFS='|' read -r command expected_exit expected_output; do
        # Пропускаем комментарии и пустые строки
        if [[ -z "$command" || "$command" == \#* ]]; then
            continue
        fi
        
        # Если нашли новую секцию - выходим
        if [[ "$command" == \[*\] ]]; then
            break
        fi
        
        # Убираем лишние пробелы
        command=$(echo "$command" | sed 's/^ *//;s/ *$//')
        expected_exit=$(echo "$expected_exit" | sed 's/^ *//;s/ *$//')
        expected_output=$(echo "$expected_output" | sed 's/^ *//;s/ *$//')
        
        test_count=$((test_count + 1))
        
        echo "Тест $test_count: $command"
        echo "Ожидается: код $expected_exit, вывод: '$expected_output'"
        
        # Выполняем команду
        output=$($PROGRAM $command 2>&1)
        actual_exit=$?
        
        # Проверяем код возврата
        exit_match=0
        if [ $actual_exit -eq $expected_exit ]; then
            exit_match=1
        fi
        
        # Проверяем вывод (если указан)
        output_match=1
        if [ -n "$expected_output" ] && [ "$expected_output" != "-" ]; then
            if echo "$output" | grep -q "$expected_output"; then
                output_match=1
            else
                output_match=0
            fi
        fi
        
        # Определяем результат
        if [ $exit_match -eq 1 ] && [ $output_match -eq 1 ]; then
            echo -e "${GREEN}✓ УСПЕХ${NC}"
            passed_count=$((passed_count + 1))
        else
            echo -e "${RED}✗ ОШИБКА${NC}"
            echo "Получен код: $actual_exit"
            echo "Получен вывод: $output"
        fi
        echo "---"
        
    done
    
    # Выводим статистику по секции
    if [ $test_count -gt 0 ]; then
        echo -e "${YELLOW}Результат $section_name: $passed_count/$test_count пройдено${NC}"
        echo
    fi
    
    return $passed_count
}

# Проверяем, что программа скомпилирована
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Ошибка: программа не скомпилирована${NC}"
    echo "Запустите 'make' сначала"
    exit 1
fi

# Проверяем наличие файла тестов
if [ ! -f "$TESTS_FILE" ]; then
    echo -e "${RED}Ошибка: файл тестов $TESTS_FILE не найден${NC}"
    exit 1
fi

echo -e "${GREEN}=== ТЕСТИРОВАНИЕ ПРОГРАММЫ ===${NC}"
echo

total_tests=0
total_passed=0

# Используем exec для работы с файлом дескриптором
exec 3< "$TESTS_FILE"

# Читаем файл и запускаем тесты по секциям
while IFS= read -r line <&3; do
    # Ищем начало секции
    if [[ "$line" == \[*\] ]]; then
        section_name=$(echo "$line" | sed 's/\[//;s/\]//')
        run_test_section "$section_name"
        section_passed=$?
        total_passed=$((total_passed + section_passed))
    fi
done

exec 3<&-

echo -e "${GREEN}=== ОБЩИЙ РЕЗУЛЬТАТ ===${NC}"
echo -e "${YELLOW}Всего пройдено: $total_passed тестов${NC}"

if [ $total_passed -eq $total_tests ]; then
    echo -e "${GREEN}🎉 ВСЕ ТЕСТЫ ПРОЙДЕНЫ!${NC}"
else
    echo -e "${RED}⚠ НЕ ВСЕ ТЕСТЫ ПРОЙДЕНЫ${NC}"
fi
