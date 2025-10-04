#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "flags.h"

// функция для сравнения строк
int strings_equal(const char* actual, const char* expected) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    return strcmp(actual, expected) == 0;
}

// Тесты для isFlagValid
void test_isFlagValid() {
    // Тест 1: Корректные флаги
    errorCodes status = isFlagValid("-d");
    assert(status == OK);
    
    status = isFlagValid("/i");
    assert(status == OK);
    
    status = isFlagValid("-ns");
    assert(status == OK);
    
    status = isFlagValid("/na");
    assert(status == OK);
    
    // Тест 2: Некорректные флаги
    status = isFlagValid("-x");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("/z");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("--d");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("d");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("-n");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("-nxx");
    assert(status == BAD_INPUT);
    
    // Тест 3: NULL pointer
    status = isFlagValid(NULL);
    assert(status == POINTER_ERROR);

    printf("test_isFlagValid: OK\n");
}

// Тесты для функции d
void test_d_function() {
    // Создаем временные файлы для тестирования
    FILE* input = fopen("test_input_d.txt", "w");
    fprintf(input, "abc123def456ghi\n789jkl");
    fclose(input);
    
    FILE* output = fopen("test_output_d.txt", "w");
    
    input = fopen("test_input_d.txt", "r");
    errorCodes status = d(input, output);
    fclose(input);
    fclose(output);
    
    assert(status == OK);
    
    // Проверяем результат
    output = fopen("test_output_d.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), output);
    fclose(output);
    
    assert(strings_equal(buffer, "abcdefghi\n"));
    
    // Удаляем временные файлы
    remove("test_input_d.txt");
    remove("test_output_d.txt");
    
    printf("test_d_function: OK\n");
}

// Тесты для функции i
void test_i_function() {
    // Создаем временные файлы для тестирования
    FILE* input = fopen("test_input_i.txt", "w");
    fprintf(input, "Hello World 123!\nTest Line 456\nLast");
    fclose(input);
    
    FILE* output = fopen("test_output_i.txt", "w");
    
    input = fopen("test_input_i.txt", "r");
    errorCodes status = i(input, output);
    fclose(input);
    fclose(output);
    
    assert(status == OK);
    
    // Проверяем результат
    output = fopen("test_output_i.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "10\n"));
    
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "9\n"));
    
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "4\n"));
    
    fclose(output);
    
    // Удаляем временные файлы
    remove("test_input_i.txt");
    remove("test_output_i.txt");
    
    printf("test_i_function: OK\n");
}

// Тесты для функции s
void test_s_function() {
    // Создаем временные файлы для тестирования
    FILE* input = fopen("test_input_s.txt", "w");
    fprintf(input, "Hello, World! 123\nTest@Line#456$\nNormal text");
    fclose(input);
    
    FILE* output = fopen("test_output_s.txt", "w");
    
    input = fopen("test_input_s.txt", "r");
    errorCodes status = s(input, output);
    fclose(input);
    fclose(output);
    
    assert(status == OK);
    
    // Проверяем результат
    output = fopen("test_output_s.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "3\n"));
    
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "3\n"));
    
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "0\n"));
    
    fclose(output);
    
    // Удаляем временные файлы
    remove("test_input_s.txt");
    remove("test_output_s.txt");
    
    printf("test_s_function: OK\n");
}

// Тесты для функции a
void test_a_function() {
    // Создаем временные файлы для тестирования
    FILE* input = fopen("test_input_a.txt", "w");
    fprintf(input, "ab1cd2");
    fclose(input);
    
    FILE* output = fopen("test_output_a.txt", "w");
    
    input = fopen("test_input_a.txt", "r");
    errorCodes status = a(input, output);
    fclose(input);
    fclose(output);
    
    assert(status == OK);
    
    // Проверяем результат
    output = fopen("test_output_a.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), output);
    fclose(output);
    
    // "ab1cd2" -> "616231636432" (a=61, b=62, 1=1, c=63, d=64, 2=2)
    assert(strings_equal(buffer, "616231636432"));
    
    // Удаляем временные файлы
    remove("test_input_a.txt");
    remove("test_output_a.txt");
    
    printf("test_a_function: OK\n");
}

// Тесты на NULL pointers
void test_null_pointers() {
    errorCodes status = d(NULL, NULL);
    assert(status == POINTER_ERROR);
    
    status = i(NULL, NULL);
    assert(status == POINTER_ERROR);
    
    status = s(NULL, NULL);
    assert(status == POINTER_ERROR);
    
    status = a(NULL, NULL);
    assert(status == POINTER_ERROR);
    
    printf("test_null_pointers: OK\n");
}

// Интеграционные тесты
void test_integration() {
    // Тест комплексного сценария
    FILE* input = fopen("test_integration.txt", "w");
    fprintf(input, "Line 1: Hello! 123\nLine 2: Test@456\n");
    fclose(input);
    
    // Тестируем функцию i
    FILE* output = fopen("test_integration_i.txt", "w");
    input = fopen("test_integration.txt", "r");
    errorCodes status = i(input, output);
    fclose(input);
    fclose(output);
    assert(status == OK);
    
    // Тестируем функцию s
    output = fopen("test_integration_s.txt", "w");
    input = fopen("test_integration.txt", "r");
    status = s(input, output);
    fclose(input);
    fclose(output);
    assert(status == OK);
    
    // Проверяем результаты
    output = fopen("test_integration_i.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "7\n"));
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "5\n"));
    fclose(output);
    
    output = fopen("test_integration_s.txt", "r");
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "3\n"));
    fgets(buffer, sizeof(buffer), output);
    assert(strings_equal(buffer, "2\n"));
    fclose(output);
    
    // Удаляем временные файлы
    remove("test_integration.txt");
    remove("test_integration_i.txt");
    remove("test_integration_s.txt");
    
    printf("test_integration: OK\n");
}

void test_all() {
    test_isFlagValid();
    test_d_function();
    test_i_function();
    test_s_function();
    test_a_function();
    test_null_pointers();
    test_integration();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}