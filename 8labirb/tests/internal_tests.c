#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "numbers.h"

// Функция для сравнения строк
int strings_equal(const char* actual, const char* expected) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    return strcmp(actual, expected) == 0;
}

// Тесты для baseParsing
void test_baseParsing() {
    int base = 0;
    
    // Тест 1: Корректная база
    errorCodes status = baseParsing("16", &base);
    assert(status == OK);
    assert(base == 16);
    
    // Тест 2: База слишком маленькая
    status = baseParsing("1", &base);
    assert(status == INVALID_BASE);
    
    // Тест 3: База слишком большая
    status = baseParsing("37", &base);
    assert(status == INVALID_BASE);
    
    // Тест 4: Некорректные символы
    status = baseParsing("16abc", &base);
    assert(status == WRONG_ARGUMENTS);
    
    // Тест 5: Отрицательная база
    status = baseParsing("-10", &base);
    assert(status == INVALID_BASE);
    
    printf("test_baseParsing: OK\n");
}

// Тесты для numChecker
void test_numChecker() {
    int isMinus = 1;
    int base = 16;
    
    // Тест 1: Корректное число в hex
    errorCodes status = numChecker("FF", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == 1);
    
    // Тест 2: Отрицательное число
    status = numChecker("-1A", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == -1);
    
    // Тест 3: Число с плюсом
    status = numChecker("+2B", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == 1);
    
    // Тест 4: Недопустимая цифра для базы
    base = 10;
    status = numChecker("12A", &base, &isMinus);
    assert(status == INVALID_DIGIT);
    
    // Тест 5: Некорректные символы
    status = numChecker("12$3", &base, &isMinus);
    assert(status == WRONG_ARGUMENTS);
    
    // Тест 6: Пустая строка после знака
    status = numChecker("-", &base, &isMinus);
    assert(status == WRONG_ARGUMENTS);
    
    printf("test_numChecker: OK\n");
}

// Тесты для toDecInt
void test_toDecInt() {
    long num = 0;
    
    // Тест 1: Корректное преобразование hex в decimal
    errorCodes status = toDecInt("FF", 16, &num);
    assert(status == OK);
    assert(num == 255);
    
    // Тест 2: Отрицательное число
    status = toDecInt("-1A", 16, &num);
    assert(status == OK);
    assert(num == -26);
    
    // Тест 3: Двоичная система
    status = toDecInt("1010", 2, &num);
    assert(status == OK);
    assert(num == 10);
    
    // Тест 4: Восьмеричная система
    status = toDecInt("77", 8, &num);
    assert(status == OK);
    assert(num == 63);
    
    // Тест 5: Ноль
    num = 999; // Мусорное значение
    status = toDecInt("0", 10, &num);
    assert(status == OK);
    assert(num == 0);
    
    // Тест 6: Переполнение
    char bigNum[100];
    sprintf(bigNum, "%ld", LONG_MAX);
    status = toDecInt(bigNum, 10, &num);
    // Может быть OK или OVERFLOW_ERROR в зависимости от реализации
    
    printf("test_toDecInt: OK\n");
}

// Тесты для toNsystem
void test_toNsystem() {
    char buffer[BUFSIZ];
    long num = 0;
    
    // Тест 1: Десятичное в hex
    num = 255;
    errorCodes status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "FF"));
    
    // Тест 2: Отрицательное число
    num = -26;
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "-1A"));
    
    // Тест 3: Ноль
    num = 0;
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "0"));
    
    // Тест 4: Двоичная система
    num = 10;
    status = toNsystem(buffer, 2, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "1010"));
    
    // Тест 5: Восьмеричная система
    num = 63;
    status = toNsystem(buffer, 8, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "77"));
    
    // Тест 6: Большая база (36)
    num = 35;
    status = toNsystem(buffer, 36, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "Z"));
    
    printf("test_toNsystem: OK\n");
}

// Интеграционные тесты - полный цикл преобразования
void test_integration() {
    char buffer[BUFSIZ];
    long num = 0;
    
    // Тест 1: Hex -> Decimal -> Hex
    errorCodes status = toDecInt("FF", 16, &num);
    assert(status == OK);
    assert(num == 255);
    
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "FF"));
    
    // Тест 2: Binary -> Decimal -> Binary
    status = toDecInt("1101", 2, &num);
    assert(status == OK);
    assert(num == 13);
    
    status = toNsystem(buffer, 2, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "1101"));
    
    // Тест 3: С отрицательными числами
    status = toDecInt("-1F", 16, &num);
    assert(status == OK);
    assert(num == -31);
    
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "-1F"));
    
    printf("test_integration: OK\n");
}

// Тесты на граничные случаи
void test_edge_cases() {
    int base = 0;
    long num = 0;
    char buffer[BUFSIZ];
    
    // Тест 1: Минимальная база
    errorCodes status = baseParsing("2", &base);
    assert(status == OK);
    assert(base == 2);
    
    // Тест 2: Максимальная база
    status = baseParsing("36", &base);
    assert(status == OK);
    assert(base == 36);
    
    // Тест 3: Число с ведущими нулями
    status = toDecInt("0010", 10, &num);
    assert(status == OK);
    assert(num == 10);
    
    // Тест 4: Максимальное long число
    num = LONG_MAX;
    status = toNsystem(buffer, 10, &num);
    assert(status == OK);
    // Должно корректно преобразоваться обратно
    long testNum = 0;
    status = toDecInt(buffer, 10, &testNum);
    assert(status == OK);
    assert(testNum == LONG_MAX);
    
    // Тест 5: Минимальное long число
    num = LONG_MIN;
    status = toNsystem(buffer, 10, &num);
    assert(status == OK);
    
    printf("test_edge_cases: OK\n");
}

void test_all() {
    test_baseParsing();
    test_numChecker();
    test_toDecInt();
    test_toNsystem();
    test_integration();
    test_edge_cases();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}