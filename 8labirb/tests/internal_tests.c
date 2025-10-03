#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../include/numbers.h"

// Вспомогательная функция для запуска программы с заданным вводом
int run_program_with_input(const char* input, char* output, int output_size) {
    int pipe_stdin[2], pipe_stdout[2];
    pid_t pid;
    
    if (pipe(pipe_stdin) != 0 || pipe(pipe_stdout) != 0) {
        return -1;
    }
    
    pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        close(pipe_stdin[1]);
        close(pipe_stdout[0]);
        
        dup2(pipe_stdin[0], STDIN_FILENO);
        dup2(pipe_stdout[1], STDOUT_FILENO);
        dup2(pipe_stdout[1], STDERR_FILENO);
        
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);
        
        execl("./number_converter", "number_converter", (char*)NULL);
        exit(1);
    } else if (pid > 0) {
        // Родительский процесс
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);
        
        // Записываем входные данные
        write(pipe_stdin[1], input, strlen(input));
        close(pipe_stdin[1]);
        
        // Читаем вывод
        int bytes_read = read(pipe_stdout[0], output, output_size - 1);
        if (bytes_read > 0) {
            output[bytes_read] = '\0';
        } else {
            output[0] = '\0';
        }
        close(pipe_stdout[0]);
        
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
    
    return -1;
}

// Функция для проверки наличия подстрок в выводе
int output_contains(const char* output, const char* substring) {
    return strstr(output, substring) != NULL;
}

// Тест 1: Нормальная работа с десятичной системой
void test_decimal_normal() {
    printf("Test 1: Decimal system normal workflow... ");
    
    char input[] = "10\n100\n-50\n25\n-200\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: -200"));
    assert(output_contains(output, "В десятичной системе: -200"));
    assert(output_contains(output, "В системе с основанием 9:"));
    assert(output_contains(output, "В системе с основанием 18:"));
    assert(output_contains(output, "В системе с основанием 27:"));
    assert(output_contains(output, "В системе с основанием 36:"));
    
    printf("PASS\n");
}

// Тест 2: Шестнадцатеричная система
void test_hexadecimal() {
    printf("Test 2: Hexadecimal system... ");
    
    char input[] = "16\nFF\n-7F\n32\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: FF") || 
           output_contains(output, "Максимальное по модулю число: -7F"));
    assert(output_contains(output, "В десятичной системе: 255") ||
           output_contains(output, "В десятичной системе: -127"));
    
    printf("PASS\n");
}

// Тест 3: Двоичная система
void test_binary() {
    printf("Test 3: Binary system... ");
    
    char input[] = "2\n1010\n1111\n-1001\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: 1111") ||
           output_contains(output, "Максимальное по модулю число: -1001"));
    assert(output_contains(output, "В десятичной системе: 15") ||
           output_contains(output, "В десятичной системе: -9"));
    
    printf("PASS\n");
}

// Тест 4: Система с максимальным основанием (36)
void test_base_36() {
    printf("Test 4: Base 36 system... ");
    
    char input[] = "36\nZZ\n100\nABC\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: ABC"));
    assert(output_contains(output, "В десятичной системе: 13368"));
    
    printf("PASS\n");
}

// Тест 5: Отрицательные числа
void test_negative_numbers() {
    printf("Test 5: Negative numbers... ");
    
    char input[] = "10\n-1000\n500\n-999\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: -1000"));
    assert(output_contains(output, "В десятичной системе: -1000"));
    
    printf("PASS\n");
}

// Тест 6: Числа с ведущими нулями
void test_leading_zeros() {
    printf("Test 6: Numbers with leading zeros... ");
    
    char input[] = "10\n0000123\n00456\n-000789\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    // Проверяем, что ведущие нули убраны в выводе
    assert(output_contains(output, "Максимальное по модулю число: 456") ||
           output_contains(output, "Максимальное по модулю число: -789"));
    assert(!output_contains(output, "000456") && !output_contains(output, "000789"));
    
    printf("PASS\n");
}

// Тест 7: Только одно число
void test_single_number() {
    printf("Test 7: Single number input... ");
    
    char input[] = "10\n42\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: 42"));
    assert(output_contains(output, "В десятичной системе: 42"));
    
    printf("PASS\n");
}

// Тест 8: Ноль как максимальное число
void test_zero_as_max() {
    printf("Test 8: Zero as maximum number... ");
    
    char input[] = "10\n0\n0\n0\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: 0"));
    assert(output_contains(output, "В десятичной системе: 0"));
    
    printf("PASS\n");
}

// Тест 9: Некорректное основание системы
void test_invalid_base() {
    printf("Test 9: Invalid base... ");
    
    char input[] = "1\nStop\n";
    char output[4096];
    
    run_program_with_input(input, output, sizeof(output));
    
    assert(output_contains(output, "Ошибка") || output_contains(output, "ошибка"));
    assert(output_contains(output, "диапазон") || output_contains(output, "основание"));
    
    printf("PASS\n");
}

// Тест 10: Некорректный ввод чисел
void test_invalid_number_input() {
    printf("Test 10: Invalid number input... ");
    
    char input[] = "10\n123\n12G\nStop\n";
    char output[4096];
    
    run_program_with_input(input, output, sizeof(output));
    
    // Программа должна сообщить об ошибке некорректного числа
    assert(output_contains(output, "Ошибка") || output_contains(output, "ошибка"));
    assert(output_contains(output, "неверный формат") || output_contains(output, "G"));
    
    printf("PASS\n");
}

// Тест 11: Большие числа (граничные случаи)
void test_large_numbers() {
    printf("Test 11: Large numbers... ");
    
    char input[] = "10\n9223372036854775807\n-9223372036854775807\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "9223372036854775807"));
    
    printf("PASS\n");
}

// Тест 12: Переполнение
void test_overflow() {
    printf("Test 12: Overflow detection... ");
    
    char input[] = "10\n999999999999999999999999999999\nStop\n";
    char output[4096];
    
    run_program_with_input(input, output, sizeof(output));
    
    // Должна быть ошибка переполнения
    assert(output_contains(output, "Ошибка") || output_contains(output, "ошибка"));
    assert(output_contains(output, "переполнение"));
    
    printf("PASS\n");
}

// Тест 13: Пустой ввод (только Stop)
void test_empty_input() {
    printf("Test 13: Empty input (only Stop)... ");
    
    char input[] = "10\nStop\n";
    char output[4096];
    
    run_program_with_input(input, output, sizeof(output));
    
    assert(output_contains(output, "Не было введено ни одного числа"));
    
    printf("PASS\n");
}

// Тест 14: Разные системы с преобразованием
void test_multiple_bases_conversion() {
    printf("Test 14: Multiple bases conversion... ");
    
    char input[] = "16\nFF\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: FF"));
    assert(output_contains(output, "В десятичной системе: 255"));
    // Проверяем, что все преобразования выполнены
    assert(output_contains(output, "В системе с основанием 9:"));
    assert(output_contains(output, "В системе с основанием 18:"));
    assert(output_contains(output, "В системе с основанием 27:"));
    assert(output_contains(output, "В системе с основанием 36:"));
    
    printf("PASS\n");
}

// Тест 15: Смешанные положительные и отрицательные числа
void test_mixed_positive_negative() {
    printf("Test 15: Mixed positive and negative numbers... ");
    
    char input[] = "10\n-100\n50\n-200\n300\n-25\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    // Максимальное по модулю должно быть -200 или 300
    assert(output_contains(output, "Максимальное по модулю число: 300") || 
           output_contains(output, "Максимальное по модулю число: -200"));
    
    printf("PASS\n");
}

// Тест 16: Восьмеричная система
void test_octal_system() {
    printf("Test 16: Octal system... ");
    
    char input[] = "8\n777\n-377\n100\nStop\n";
    char output[4096];
    
    int result = run_program_with_input(input, output, sizeof(output));
    
    assert(result == OK);
    assert(output_contains(output, "Максимальное по модулю число: 777") ||
           output_contains(output, "Максимальное по модулю число: -377"));
    assert(output_contains(output, "В десятичной системе: 511") ||
           output_contains(output, "В десятичной системе: -255"));
    
    printf("PASS\n");
}

void run_all_integration_tests() {
    printf("=== INTEGRATION TESTS FOR NUMBER CONVERTER ===\n\n");
    
    test_decimal_normal();
    test_hexadecimal();
    test_binary();
    test_octal_system();
    test_base_36();
    test_negative_numbers();
    test_leading_zeros();
    test_single_number();
    test_zero_as_max();
    test_invalid_base();
    test_invalid_number_input();
    test_large_numbers();
    test_overflow();
    test_empty_input();
    test_multiple_bases_conversion();
    test_mixed_positive_negative();
    
    printf("\n=== ALL INTEGRATION TESTS PASSED! ===\n");
}

int main() {
    // Проверяем, что основная программа скомпилирована
    if (access("./number_converter", F_OK) != 0) {
        printf("Error: number_converter not found. Please run 'make all' first.\n");
        return 1;
    }
    
    run_all_integration_tests();
    return 0;
}
