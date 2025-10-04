#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/primenumbers.h"

// Функция для запуска программы с входными данными и проверки вывода
int test_program(const char* input, const char* expected_output, int expected_exit_code) {
    int pipe_stdin[2], pipe_stdout[2];
    pid_t pid;
    
    // Создаем пайпы для stdin и stdout
    if (pipe(pipe_stdin) == -1 || pipe(pipe_stdout) == -1) {
        perror("pipe");
        return 0;
    }
    
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 0;
    }
    
    if (pid == 0) { // Дочерний процесс
        close(pipe_stdin[1]);  // Закрываем запись в stdin
        close(pipe_stdout[0]); // Закрываем чтение из stdout
        
        // Перенаправляем stdin и stdout
        dup2(pipe_stdin[0], STDIN_FILENO);
        dup2(pipe_stdout[1], STDOUT_FILENO);
        
        // Закрываем оставшиеся дескрипторы
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);
        
        // Запускаем основную программу
        execl("./prime_program", "prime_program", NULL);
        perror("execl");
        exit(1);
    } else { // Родительский процесс
        close(pipe_stdin[0]);  // Закрываем чтение из stdin
        close(pipe_stdout[1]); // Закрываем запись в stdout
        
        // Записываем входные данные
        if (input != NULL) {
            write(pipe_stdin[1], input, strlen(input));
        }
        close(pipe_stdin[1]);
        
        // Читаем вывод
        char buffer[4096];
        ssize_t bytes_read = read(pipe_stdout[0], buffer, sizeof(buffer) - 1);
        close(pipe_stdout[0]);
        
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
        } else {
            buffer[0] = '\0';
        }
        
        // Ждем завершения дочернего процесса
        int status;
        waitpid(pid, &status, 0);
        int exit_code = WEXITSTATUS(status);
        
        // Проверяем результат
        int success = 1;
        
        if (expected_exit_code != -1 && exit_code != expected_exit_code) {
            printf("FAIL: Expected exit code %d, got %d\n", expected_exit_code, exit_code);
            success = 0;
        }
        
        if (expected_output != NULL && strstr(buffer, expected_output) == NULL) {
            printf("FAIL: Expected output containing '%s', got: %s\n", expected_output, buffer);
            success = 0;
        }
        
        if (success) {
            printf("PASS: Input '%s' -> Output contains '%s'\n", 
                   input ? input : "(null)", 
                   expected_output ? expected_output : "(any)");
        }
        
        return success;
    }
}

// Тест 1: Неверное количество тест-кейсов (отрицательное)
void test_negative_test_cases() {
    printf("=== Test 1: Negative number of test cases ===\n");
    test_program("-5\n", "must be positive", BAD_INPUT);
    printf("\n");
}

// Тест 2: Нулевое количество тест-кейсов
void test_zero_test_cases() {
    printf("=== Test 2: Zero test cases ===\n");
    test_program("0\n", "must be positive", BAD_INPUT);
    printf("\n");
}

// Тест 3: Неверный формат ввода (не число)
void test_invalid_input_format() {
    printf("=== Test 3: Invalid input format ===\n");
    test_program("3\n1 2 abc\n", "Failed to read index", BAD_INPUT);
    printf("\n");
}

// Тест 4: Неполные данные
void test_incomplete_data() {
    printf("=== Test 4: Incomplete data ===\n");
    test_program("3\n1 2\n", "Failed to read index", BAD_INPUT);
    printf("\n");
}

// Тест 5: Отрицательные индексы простых чисел
void test_negative_prime_indices() {
    printf("=== Test 5: Negative prime indices ===\n");
    test_program("2\n1 -5\n", "must be positive", INDEX_ERROR);
    printf("\n");
}

// Тест 6: Нулевые индексы простых чисел
void test_zero_prime_indices() {
    printf("=== Test 6: Zero prime indices ===\n");
    test_program("1\n0\n", "must be positive", INDEX_ERROR);
    printf("\n");
}

// Тест 7: Корректный ввод - малые числа
void test_small_valid_input() {
    printf("=== Test 7: Small valid input ===\n");
    test_program("3\n1 2 3\n", "1. The 1 prime number is: 2", OK);
    test_program("3\n1 2 3\n", "2. The 2 prime number is: 3", OK);
    test_program("3\n1 2 3\n", "3. The 3 prime number is: 5", OK);
    printf("\n");
}

// Тест 8: Корректный ввод - средние числа
void test_medium_valid_input() {
    printf("=== Test 8: Medium valid input ===\n");
    test_program("2\n10 20\n", "10. The 10 prime number is: 29", OK);
    test_program("2\n10 20\n", "20. The 20 prime number is: 71", OK);
    printf("\n");
}

// Тест 9: Один тест-кейс
void test_single_case() {
    printf("=== Test 9: Single test case ===\n");
    test_program("1\n5\n", "5. The 5 prime number is: 11", OK);
    printf("\n");
}

// Тест 10: Большое количество тест-кейсов
void test_multiple_cases() {
    printf("=== Test 10: Multiple test cases ===\n");
    test_program("5\n1 3 5 7 9\n", "1. The 1 prime number is: 2", OK);
    test_program("5\n1 3 5 7 9\n", "3. The 3 prime number is: 5", OK);
    test_program("5\n1 3 5 7 9\n", "5. The 5 prime number is: 11", OK);
    test_program("5\n1 3 5 7 9\n", "7. The 7 prime number is: 17", OK);
    test_program("5\n1 3 5 7 9\n", "9. The 9 prime number is: 23", OK);
    printf("\n");
}

// Тест 11: Очень большой индекс (проверка переполнения)
void test_large_index() {
    printf("=== Test 11: Large index (overflow check) ===\n");
    test_program("1\n1000000\n", "too large", OVERFLOW_ERROR);
    printf("\n");
}

// Тест 12: Граничные случаи
void test_boundary_cases() {
    printf("=== Test 12: Boundary cases ===\n");
    test_program("1\n1\n", "1. The 1 prime number is: 2", OK);
    test_program("1\n100\n", "100. The 100 prime number is: 541", OK);
    printf("\n");
}

// Тест 13: Сортировка индексов
void test_sorted_indices() {
    printf("=== Test 13: Sorted indices ===\n");
    test_program("3\n3 1 2\n", "1. The 3 prime number is: 5", OK);
    test_program("3\n3 1 2\n", "2. The 1 prime number is: 2", OK);
    test_program("3\n3 1 2\n", "3. The 2 prime number is: 3", OK);
    printf("\n");
}

// Тест 14: Повторяющиеся индексы
void test_duplicate_indices() {
    printf("=== Test 14: Duplicate indices ===\n");
    test_program("3\n2 2 2\n", "1. The 2 prime number is: 3", OK);
    test_program("3\n2 2 2\n", "2. The 2 prime number is: 3", OK);
    test_program("3\n2 2 2\n", "3. The 2 prime number is: 3", OK);
    printf("\n");
}

void test_all() {
    printf("Starting comprehensive main() tests...\n\n");
    
    test_negative_test_cases();
    test_zero_test_cases();
    test_invalid_input_format();
    test_incomplete_data();
    test_negative_prime_indices();
    test_zero_prime_indices();
    test_small_valid_input();
    test_medium_valid_input();
    test_single_case();
    test_multiple_cases();
    test_large_index();
    test_boundary_cases();
    test_sorted_indices();
    test_duplicate_indices();
    
    printf("All main() tests completed!\n");
}

int main() {
    // Проверяем что программа скомпилирована
    if (access("./prime_program", F_OK) == -1) {
        printf("Error: prime_program not found. Please compile the program first.\n");
        return 1;
    }
    
    test_all();
    return 0;
}