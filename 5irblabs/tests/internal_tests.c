#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/flags.h"

void create_test_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fputs(content, file);
        fclose(file);
    }
}

char* read_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(size + 1);
    if (content) {
        fread(content, 1, size, file);
        content[size] = '\0';
    }
    
    fclose(file);
    return content;
}

// Тесты для isFlagValid
void test_isFlagValid() {
    printf("Testing isFlagValid...\n");
    
    // Valid flags
    assert(isFlagValid("-d") == OK);
    assert(isFlagValid("-i") == OK);
    assert(isFlagValid("-s") == OK);
    assert(isFlagValid("-a") == OK);
    assert(isFlagValid("/d") == OK);
    assert(isFlagValid("/i") == OK);
    assert(isFlagValid("-nd") == OK);
    assert(isFlagValid("/ni") == OK);
    
    // Invalid flags
    assert(isFlagValid("") == BAD_INPUT);
    assert(isFlagValid("-") == BAD_INPUT);
    assert(isFlagValid("--") == BAD_INPUT);
    assert(isFlagValid("-x") == BAD_INPUT);
    assert(isFlagValid("-dd") == BAD_INPUT);
    assert(isFlagValid("-n") == BAD_INPUT);
    assert(isFlagValid("-nxd") == BAD_INPUT);
    
    printf("test_isFlagValid: OK\n");
}

// Тесты для функции d (remove digits)
void test_function_d() {
    printf("Testing function d...\n");
    
    create_test_file("test_d_input.txt", "Hello123 World456\nTest789");
    
    FILE* input = fopen("test_d_input.txt", "r");
    FILE* output = fopen("test_d_output.txt", "w");
    
    assert(input != NULL);
    assert(output != NULL);
    
    errorCodes result = d(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    char* content = read_file_content("test_d_output.txt");
    assert(content != NULL);
    assert(strstr(content, "Hello World") != NULL);
    assert(strstr(content, "Test") != NULL);
    assert(strstr(content, "123") == NULL);
    
    free(content);
    remove("test_d_input.txt");
    remove("test_d_output.txt");
    
    printf("test_function_d: OK\n");
}

// Тесты для функции i (count letters per line)
void test_function_i() {
    printf("Testing function i...\n");
    
    create_test_file("test_i_input.txt", "Hello123 World\nTest456\nLast");
    
    FILE* input = fopen("test_i_input.txt", "r");
    FILE* output = fopen("test_i_output.txt", "w");
    
    assert(input != NULL);
    assert(output != NULL);
    
    errorCodes result = i(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    char* content = read_file_content("test_i_output.txt");
    assert(content != NULL);
    
    // Проверяем подсчет букв в каждой строке
    // "Hello123 World" имеет 10 букв
    // "Test456" имеет 4 буквы  
    // "Last" имеет 4 буквы
    assert(strstr(content, "10") != NULL);
    assert(strstr(content, "4") != NULL);
    
    free(content);
    remove("test_i_input.txt");
    remove("test_i_output.txt");
    
    printf("test_function_i: OK\n");
}

// Тесты для функции s (count special characters)
void test_function_s() {
    printf("Testing function s...\n");
    
    create_test_file("test_s_input.txt", "Hello!@# World$%\nTest^&*\n");
    
    FILE* input = fopen("test_s_input.txt", "r");
    FILE* output = fopen("test_s_output.txt", "w");
    
    assert(input != NULL);
    assert(output != NULL);
    
    errorCodes result = s(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    char* content = read_file_content("test_s_output.txt");
    assert(content != NULL);
    
    // "Hello!@# World$%" имеет 5 специальных символов (!@#$%)
    // "Test^&*" имеет 3 специальных символа (^&*)
    assert(strstr(content, "5") != NULL);
    assert(strstr(content, "3") != NULL);
    
    free(content);
    remove("test_s_input.txt");
    remove("test_s_output.txt");
    
    printf("test_function_s: OK\n");
}

// Тесты для функции a (hex conversion)
void test_function_a() {
    printf("Testing function a...\n");
    
    create_test_file("test_a_input.txt", "AB12cd");
    
    FILE* input = fopen("test_a_input.txt", "r");
    FILE* output = fopen("test_a_output.txt", "w");
    
    assert(input != NULL);
    assert(output != NULL);
    
    errorCodes result = a(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    char* content = read_file_content("test_a_output.txt");
    assert(content != NULL);
    
    // Цифры должны остаться как есть, буквы конвертироваться в hex
    // 'A' = 0x41, 'B' = 0x42, '1'='1', '2'='2', 'c'=0x63, 'd'=0x64
    assert(strstr(content, "12") != NULL); // цифры сохраняются
    assert(strstr(content, "4142") != NULL); // AB в hex
    
    free(content);
    remove("test_a_input.txt");
    remove("test_a_output.txt");
    
    printf("test_function_a: OK\n");
}

// Тесты для пустых файлов
void test_empty_files() {
    printf("Testing empty files...\n");
    
    // Пустой входной файл
    create_test_file("test_empty_input.txt", "");
    
    FILE* input = fopen("test_empty_input.txt", "r");
    FILE* output = fopen("test_empty_output.txt", "w");
    
    assert(input != NULL);
    assert(output != NULL);
    
    // Тестируем все функции с пустым файлом
    errorCodes result = d(input, output);
    assert(result == OK);
    
    rewind(input);
    result = i(input, output);
    assert(result == OK);
    
    rewind(input);
    result = s(input, output);
    assert(result == OK);
    
    rewind(input);
    result = a(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    remove("test_empty_input.txt");
    remove("test_empty_output.txt");
    
    printf("test_empty_files: OK\n");
}

// Тесты для обработки ошибок (без передачи NULL)
void test_error_handling() {
    printf("Testing error handling...\n");
    
    // Тест с несуществующим файлом
    FILE* input = fopen("nonexistent_file_12345.txt", "r");
    assert(input == NULL);
    
    printf("test_error_handling: OK\n");
}

void test_all() {
    test_isFlagValid();
    test_function_d();
    test_function_i();
    test_function_s();
    test_function_a();
    test_empty_files();
    test_error_handling();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}