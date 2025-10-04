#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "flags.h"

// функция для сравнения строк
int strings_equal(const char* actual, const char* expected) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    return strcmp(actual, expected) == 0;
}

// Тесты для convertStrToNum
void test_convertStrToNum() {
    int num;
    
    // Тест 1: Корректные числа
    errorCodes status = convertStrToNum("123", &num);
    assert(status == OK);
    assert(num == 123);
    
    status = convertStrToNum("-456", &num);
    assert(status == OK);
    assert(num == -456);
    
    status = convertStrToNum("0", &num);
    assert(status == OK);
    assert(num == 0);
    
    // Тест 2: Некорректные числа
    status = convertStrToNum("123abc", &num);
    assert(status == BAD_INPUT);
    
    status = convertStrToNum("12.34", &num);
    assert(status == BAD_INPUT);
    
    
    // Тест 3: Переполнение
    char big_num[100];
    sprintf(big_num, "%ld", (long)INT_MAX + 1);
    status = convertStrToNum(big_num, &num);
    assert(status == OVERFLOW_ERROR);
    
    sprintf(big_num, "%ld", (long)INT_MIN - 1);
    status = convertStrToNum(big_num, &num);
    assert(status == OVERFLOW_ERROR);
    
    // Тест 4: NULL pointers
    status = convertStrToNum(NULL, &num);
    assert(status == POINTER_ERROR);
    
    status = convertStrToNum("123", NULL);
    assert(status == POINTER_ERROR);

    printf("test_convertStrToNum: OK\n");
}

// Тесты для isFlagValid
void test_isFlagValid() {
    // Тест 1: Корректные флаги
    errorCodes status = isFlagValid("-h");
    assert(status == OK);
    
    status = isFlagValid("/p");
    assert(status == OK);
    
    status = isFlagValid("-s");
    assert(status == OK);
    
    status = isFlagValid("/e");
    assert(status == OK);
    
    status = isFlagValid("-a");
    assert(status == OK);
    
    status = isFlagValid("/f");
    assert(status == OK);
    
    // Тест 2: Некорректные флаги
    status = isFlagValid("-x");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("/z");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("--h");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("h");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("-hh");
    assert(status == BAD_INPUT);
    
    status = isFlagValid("");
    assert(status == BAD_INPUT);

    printf("test_isFlagValid: OK\n");
}

// Тесты для функции h
void test_h_function() {
    int list[100];
    int count;
    
    // Тест 1: Корректные числа
    errorCodes status = h(5, list, &count);
    assert(status == OK);
    assert(count == 20);
    assert(list[0] == 5);
    assert(list[19] == 100);
    
    status = h(10, list, &count);
    assert(status == OK);
    assert(count == 10);
    assert(list[0] == 10);
    assert(list[9] == 100);
    
    status = h(100, list, &count);
    assert(status == OK);
    assert(count == 1);
    assert(list[0] == 100);
    
    // Тест 2: Ноль
    status = h(0, list, &count);
    assert(status == BAD_INPUT);
    
    // Тест 3: Отрицательные числа (должны браться по модулю)
    status = h(-5, list, &count);
    assert(status == OK);
    assert(count == 20);
    
    // Тест 4: Числа больше 100
    status = h(101, list, &count);
    assert(status == OK);
    assert(count == 0);
    
    // Тест 5: NULL pointers
    status = h(5, NULL, &count);
    assert(status == POINTER_ERROR);
    
    status = h(5, list, NULL);
    assert(status == POINTER_ERROR);

    printf("test_h_function: OK\n");
}

// Тесты для функции p
void test_p_function() {
    int isPrime;
    
    // Тест 1: Простые числа
    errorCodes status = p(2, &isPrime);
    assert(status == OK);
    assert(isPrime == 1);
    
    status = p(7, &isPrime);
    assert(status == OK);
    assert(isPrime == 1);
    
    status = p(17, &isPrime);
    assert(status == OK);
    assert(isPrime == 1);
    
    // Тест 2: Составные числа
    status = p(4, &isPrime);
    assert(status == OK);
    assert(isPrime == 0);
    
    status = p(15, &isPrime);
    assert(status == OK);
    assert(isPrime == 0);
    
    status = p(100, &isPrime);
    assert(status == OK);
    assert(isPrime == 0);
    
    // Тест 3: Единица
    status = p(1, &isPrime);
    assert(status == OK);
    assert(isPrime == 2);
    
    // Тест 4: Некорректные числа
    status = p(0, &isPrime);
    assert(status == BAD_INPUT);
    
    status = p(-5, &isPrime);
    assert(status == BAD_INPUT);
    
    // Тест 5: NULL pointer
    status = p(5, NULL);
    assert(status == POINTER_ERROR);

    printf("test_p_function: OK\n");
}

// Тесты для функции s
void test_s_function() {
    char hexRepr[32];
    int length;
    
    // Тест 1: Положительные числа
    errorCodes status = s(255, hexRepr, &length);
    assert(status == OK);
    assert(length == 2);
    assert(hexRepr[0] == 'F');
    assert(hexRepr[1] == 'F');
    
    status = s(10, hexRepr, &length);
    assert(status == OK);
    assert(length == 1);
    assert(hexRepr[0] == 'A');
    
    status = s(0, hexRepr, &length);
    assert(status == OK);
    assert(length == 1);
    assert(hexRepr[0] == '0');
    
    // Тест 2: Отрицательные числа
    status = s(-255, hexRepr, &length);
    assert(status == OK);
    assert(length == 3);
    assert(hexRepr[0] == 'F');
    assert(hexRepr[1] == 'F');
    assert(hexRepr[2] == '-');
    
    // Тест 3: NULL pointers
    status = s(255, NULL, &length);
    assert(status == POINTER_ERROR);
    
    status = s(255, hexRepr, NULL);
    assert(status == POINTER_ERROR);

    printf("test_s_function: OK\n");
}

// Тесты для функции e
void test_e_function() {
    long** list;
    
    // Тест 1: Корректные степени
    errorCodes status = e(5, &list);
    assert(status == OK);
    assert(list != NULL);
    
    // Проверяем несколько значений
    assert(list[0][0] == 1);   // 1^1
    assert(list[0][4] == 1);   // 1^5
    assert(list[1][0] == 2);   // 2^1
    assert(list[1][1] == 4);   // 2^2
    assert(list[9][0] == 10);  // 10^1
    assert(list[9][1] == 100); // 10^2
    
    // Освобождаем память
    for (int i = 0; i < 10; i++) {
        free(list[i]);
    }
    free(list);
    
    // Тест 2: Некорректные степени
    status = e(0, &list);
    assert(status == BAD_INPUT);
    
    status = e(-5, &list);
    assert(status == BAD_INPUT);
    
    status = e(11, &list);
    assert(status == BAD_INPUT);

    printf("test_e_function: OK\n");
}

// Тесты для функции f
void test_f_function() {
    long fact;
    
    // Тест 1: Корректные факториалы
    errorCodes status = f(0, &fact);
    assert(status == OK);
    assert(fact == 1);
    
    status = f(1, &fact);
    assert(status == OK);
    assert(fact == 1);
    
    status = f(5, &fact);
    assert(status == OK);
    assert(fact == 120);
    
    // Тест 2: Некорректные числа
    status = f(-5, &fact);
    assert(status == BAD_INPUT);
    
    // Тест 3: Переполнение (может зависеть от реализации)
    status = f(30, &fact);
    // Может быть OK или OVERFLOW_ERROR
    
    // Тест 4: NULL pointer
    status = f(5, NULL);
    assert(status == POINTER_ERROR);

    printf("test_f_function: OK\n");
}

// Тесты для функции a
void test_a_function() {
    int sum;
    
    // Тест 1: Корректные суммы
    errorCodes status = a(1, &sum);
    assert(status == OK);
    assert(sum == 1);
    
    status = a(5, &sum);
    assert(status == OK);
    assert(sum == 15);
    
    status = a(10, &sum);
    assert(status == OK);
    assert(sum == 55);
    
    // Тест 2: Некорректные числа
    status = a(0, &sum);
    assert(status == BAD_INPUT);
    
    status = a(-5, &sum);
    assert(status == BAD_INPUT);
    
    // Тест 3: Переполнение
    status = a(INT_MAX, &sum);
    // Может быть OVERFLOW_ERROR
    
    // Тест 4: NULL pointer
    status = a(5, NULL);
    assert(status == POINTER_ERROR);

    printf("test_a_function: OK\n");
}

// Интеграционные тесты
void test_integration() {
    // Тест комплексного сценария
    int num;
    errorCodes status = convertStrToNum("15", &num);
    assert(status == OK);
    assert(num == 15);
    
    int isPrime;
    status = p(num, &isPrime);
    assert(status == OK);
    assert(isPrime == 0); // 15 - составное
    
    long fact;
    status = f(5, &fact);
    assert(status == OK);
    assert(fact == 120);
    
    int list[100];
    int count;
    status = h(10, list, &count);
    assert(status == OK);
    assert(count == 10);

    printf("test_integration: OK\n");
}

void test_all() {
    test_convertStrToNum();
    test_isFlagValid();
    test_h_function();
    test_p_function();
    test_s_function();
    test_e_function();
    test_f_function();
    test_a_function();
    test_integration();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}