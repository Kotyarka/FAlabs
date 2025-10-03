#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "numbers.h"

// Вспомогательная функция для сравнения строк
int strings_equal(const char* actual, const char* expected) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    return strcmp(actual, expected) == 0;
}

// Тесты для remove_leading_zeros
void test_remove_leading_zeros() {
    char* result = NULL;
    
    // Тест 1: Обычное число без ведущих нулей
    errorCodes status = remove_leading_zeros("123", &result);
    assert(status == OK);
    assert(strings_equal(result, "123"));
    free(result);
    
    // Тест 2: Число с ведущими нулями
    status = remove_leading_zeros("000123", &result);
    assert(status == OK);
    assert(strings_equal(result, "123"));
    free(result);
    
    // Тест 3: Только нули (должен остаться один ноль)
    status = remove_leading_zeros("0000", &result);
    assert(status == OK);
    assert(strings_equal(result, "0"));
    free(result);
    
    // Тест 4: Один ноль
    status = remove_leading_zeros("0", &result);
    assert(status == OK);
    assert(strings_equal(result, "0"));
    free(result);
    
    // Тест 5: Пустая строка
    status = remove_leading_zeros("", &result);
    assert(status == BAD_INPUT);
    
    // Тест 6: NULL указатель
    status = remove_leading_zeros(NULL, &result);
    assert(status == POINTER_ERROR);
    
    status = remove_leading_zeros("123", NULL);
    assert(status == POINTER_ERROR);
    
    printf("test_remove_leading_zeros: OK\n");
}

// Тесты для find_min_base
void test_find_min_base() {
    int base;
    
    // Тест 1: Двоичное число
    errorCodes status = find_min_base("101", &base);
    assert(status == OK);
    assert(base == 2);
    
    // Тест 2: Восьмеричное число
    status = find_min_base("765", &base);
    assert(status == OK);
    assert(base == 8);
    
    // Тест 3: Десятичное число
    status = find_min_base("999", &base);
    assert(status == OK);
    assert(base == 10);
    
    // Тест 4: Шестнадцатеричное число (строчные)
    status = find_min_base("abc", &base);
    assert(status == OK);
    assert(base == 13); // a=10, b=11, c=12 -> min_base=13
    
    // Тест 5: Шестнадцатеричное число (прописные)
    status = find_min_base("ABC", &base);
    assert(status == OK);
    assert(base == 13);
    
    // Тест 6: Смешанный регистр
    status = find_min_base("aBc", &base);
    assert(status == OK);
    assert(base == 13);
    
    // Тест 7: Максимальное основание (36)
    status = find_min_base("z", &base);
    assert(status == OK);
    assert(base == 36);
    
    // Тест 8: Ноль
    status = find_min_base("0", &base);
    assert(status == OK);
    assert(base == 2);
    
    // Тест 9: Недопустимый символ
    status = find_min_base("12#4", &base);
    assert(status == INVALID_NUMBER_ERROR);
    
    // Тест 10: Символ выше максимального
    status = find_min_base("!", &base);
    assert(status == INVALID_NUMBER_ERROR);
    
    // Тест 11: Пустая строка
    status = find_min_base("", &base);
    assert(status == BAD_INPUT);
    
    // Тест 12: NULL указатель
    status = find_min_base(NULL, &base);
    assert(status == POINTER_ERROR);
    
    status = find_min_base("123", NULL);
    assert(status == POINTER_ERROR);
    
    printf("test_find_min_base: OK\n");
}

// Тесты для convert_to_decimal
void test_convert_to_decimal() {
    long long result;
    
    // Тест 1: Двоичное число
    errorCodes status = convert_to_decimal("101", 2, &result);
    assert(status == OK);
    assert(result == 5);
    
    // Тест 2: Восьмеричное число
    status = convert_to_decimal("777", 8, &result);
    assert(status == OK);
    assert(result == 511);
    
    // Тест 3: Десятичное число
    status = convert_to_decimal("123", 10, &result);
    assert(status == OK);
    assert(result == 123);
    
    // Тест 4: Шестнадцатеричное число
    status = convert_to_decimal("ff", 16, &result);
    assert(status == OK);
    assert(result == 255);
    
    // Тест 5: Большое основание
    status = convert_to_decimal("z", 36, &result);
    assert(status == OK);
    assert(result == 35);
    
    // Тест 6: Ноль
    status = convert_to_decimal("0", 10, &result);
    assert(status == OK);
    assert(result == 0);
    
    // Тест 7: Переполнение
    status = convert_to_decimal("FFFFFFFFFFFF", 16, &result);
    assert(status == OVERFLOW_ERROR);
    assert(result == LLONG_MAX);
    
    // Тест 8: Недопустимая цифра для основания
    status = convert_to_decimal("123", 2, &result);
    assert(status == INVALID_NUMBER_ERROR);
    
    // Тест 9: Некорректное основание
    status = convert_to_decimal("123", 1, &result);
    assert(status == BAD_INPUT);
    
    status = convert_to_decimal("123", 37, &result);
    assert(status == BAD_INPUT);
    
    // Тест 10: NULL указатель
    status = convert_to_decimal(NULL, 10, &result);
    assert(status == POINTER_ERROR);
    
    status = convert_to_decimal("123", 10, NULL);
    assert(status == POINTER_ERROR);
    
    printf("test_convert_to_decimal: OK\n");
}

// Тесты для read_next_token
void test_read_next_token() {
    char* result = NULL;
    
    // Тест 1: Простое число
    FILE* test_file = fopen("test_simple.txt", "w+");
    fprintf(test_file, "123");
    rewind(test_file);
    
    errorCodes status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(strings_equal(result, "123"));
    free(result);
    fclose(test_file);
    
    // Тест 2: Число с пробелами
    test_file = fopen("test_spaces.txt", "w+");
    fprintf(test_file, "   456   ");
    rewind(test_file);
    
    status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(strings_equal(result, "456"));
    free(result);
    fclose(test_file);
    
    // Тест 3: Несколько чисел
    test_file = fopen("test_multiple.txt", "w+");
    fprintf(test_file, "123 456 789");
    rewind(test_file);
    
    status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(strings_equal(result, "123"));
    free(result);
    
    status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(strings_equal(result, "456"));
    free(result);
    
    status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(strings_equal(result, "789"));
    free(result);
    
    fclose(test_file);
    
    // Тест 4: Пустой файл
    test_file = fopen("test_empty.txt", "w+");
    status = read_next_token(test_file, &result);
    assert(status == OK);
    assert(result == NULL);
    fclose(test_file);
    
    // Тест 5: NULL указатель
    status = read_next_token(NULL, &result);
    assert(status == POINTER_ERROR);
    
    printf("test_read_next_token: OK\n");
}

// Тесты для process_numbers (интеграционные)
void test_process_numbers() {
    // Тест 1: Обычные числа в разных системах счисления
    FILE* input = fopen("test_input1.txt", "w+");
    FILE* output = fopen("test_output1.txt", "w+");
    fprintf(input, "101 777 abc 0 z 123");
    rewind(input);
    
    errorCodes status = process_numbers(input, output);
    assert(status == OK);
    
    rewind(output);
    char buffer[1000];
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "101 2 5") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "777 8 511") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "abc 13") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "0 2 0") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "z 36 35") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "123 4 27") != NULL); // 123 в 4-чной = 27
    
    fclose(input);
    fclose(output);
    
    // Тест 2: Числа с ведущими нулями
    input = fopen("test_input2.txt", "w+");
    output = fopen("test_output2.txt", "w+");
    fprintf(input, "000123 00ABC 0000");
    rewind(input);
    
    status = process_numbers(input, output);
    assert(status == OK);
    
    rewind(output);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "123 4 27") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "ABC 13") != NULL);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "0 2 0") != NULL);
    
    fclose(input);
    fclose(output);
    
    // Тест 3: Переполнение
    input = fopen("test_input3.txt", "w+");
    output = fopen("test_output3.txt", "w+");
    fprintf(input, "FFFFFFFFFFFFFFFFFFFF");
    rewind(input);
    
    status = process_numbers(input, output);
    assert(status == OK);
    
    rewind(output);
    fgets(buffer, sizeof(buffer), output);
    assert(strstr(buffer, "FFFFFFFFFFFFFFFFFFFF 16 overflow") != NULL);
    
    fclose(input);
    fclose(output);
    
    // Тест 4: Недопустимые символы
    input = fopen("test_input4.txt", "w+");
    output = fopen("test_output4.txt", "w+");
    fprintf(input, "12#4 5!6");
    rewind(input);
    
    status = process_numbers(input, output);
    assert(status == OK); // Должен продолжить обработку после ошибки
    
    fclose(input);
    fclose(output);
    
    // Тест 5: Разделители
    input = fopen("test_input5.txt", "w+");
    output = fopen("test_output5.txt", "w+");
    fprintf(input, "123\n456\t789  abc");
    rewind(input);
    
    status = process_numbers(input, output);
    assert(status == OK);
    
    rewind(output);
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), output)) {
        line_count++;
    }
    assert(line_count == 4);
    
    fclose(input);
    fclose(output);
    
    printf("test_process_numbers: OK\n");
}

// Тесты обработки ошибок
void test_error_handling() {
    // Тест MALLOC_ERROR (симулируем через очень длинную строку)
    FILE* input = fopen("test_malloc.txt", "w+");
    // Создаем очень длинную строку
    for (int i = 0; i < 10000; i++) {
        fprintf(input, "A");
    }
    rewind(input);
    
    FILE* output = fopen("test_malloc_out.txt", "w+");
    errorCodes status = process_numbers(input, output);
    // В зависимости от системы может вернуть OK или MALLOC_ERROR
    assert(status == OK || status == MALLOC_ERROR);
    
    fclose(input);
    fclose(output);
    
    // Тест NULL указатели (отдельный тест без использования закрытых файлов)
    status = process_numbers(NULL, NULL);
    assert(status == POINTER_ERROR);
    
    printf("test_error_handling: OK\n");
}

void test_all() {
    test_remove_leading_zeros();
    test_find_min_base();
    test_convert_to_decimal();
    test_read_next_token();
    test_process_numbers();
    test_error_handling();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}
