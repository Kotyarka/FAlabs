#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../include/numbers.h"

// Функция для сравнения double с учетом точности
int doublesEqual(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

// Тесты для transferToDouble
void testTransferToDouble() {
    double result;
    errorCodes status;
    
    // Тест 1: Корректное число
    status = transferToDouble("3.14", &result);
    assert(status == OK);
    assert(doublesEqual(result, 3.14, 1e-10));
    
    // Тест 2: Отрицательное число
    status = transferToDouble("-42.5", &result);
    assert(status == OK);
    assert(doublesEqual(result, -42.5, 1e-10));
    
    // Тест 3: Научная нотация
    status = transferToDouble("1e-5", &result);
    assert(status == OK);
    assert(doublesEqual(result, 0.00001, 1e-10));
    
    // Тест 4: Не число (ошибка)
    status = transferToDouble("abc", &result);
    assert(status == NOT_A_DOUBLE_ERROR);
    
    // Тест 5: Частично число (ошибка)
    status = transferToDouble("123.45abc", &result);
    assert(status == NOT_A_DOUBLE_ERROR);
    
    // Тест 6: NULL указатель (ошибка)
    status = transferToDouble(NULL, &result);
    assert(status == POINTER_ERROR);
    
    // Тест 7: NULL выходной указатель (ошибка)
    status = transferToDouble("123", NULL);
    assert(status == POINTER_ERROR);
    
    printf("testTransferToDouble: OK\n");
}

// Тесты для calculateELimit
void testCalculateELimit() {
    double result;
    errorCodes status;
    
    // Тест 1: Нормальная точность
    status = calculateELimit(1e-6, &result);
    assert(status == OK);
    assert(result > 2.7 && result < 2.8);
 
    // Тест 2: Нулевая точность (ошибка)
    status = calculateELimit(0, &result);
    assert(status == BAD_INPUT);
    
    // Тест 3: Отрицательная точность (ошибка)
    status = calculateELimit(-1, &result);
    assert(status == BAD_INPUT);
    
    printf("testCalculateELimit: OK\n");
}

// Тесты для calculatePiLimit
void testCalculatePiLimit() {
    double result;
    errorCodes status;
    
    status = calculatePiLimit(1e-6, &result);
    assert(status == OK);
    assert(result > 3.1 && result < 3.2);
    
    printf("testCalculatePiLimit: OK\n");
}

// Тесты для calculateLnLimit
void testCalculateLnLimit() {
    double result;
    errorCodes status;
    
    status = calculateLnLimit(1e-6, &result);
    assert(status == OK);
    assert(result > 0.69 && result < 0.70);
    
    printf("testCalculateLnLimit: OK\n");
}

// Тесты для calculateSqrt2Limit
void testCalculateSqrt2Limit() {
    double result;
    errorCodes status;
    
    status = calculateSqrt2Limit(1e-6, &result);
    assert(status == OK);
    assert(result > 1.41 && result < 1.42);
    
    printf("testCalculateSqrt2Limit: OK\n");
}

// Тесты для calculateERow
void testCalculateERow() {
    double result;
    errorCodes status;
    
    status = calculateERow(1e-6, &result);
    assert(status == OK);
    assert(result > 2.7 && result < 2.8);
    
    printf("testCalculateERow: OK\n");
}

// Тесты для calculatePiRow
void testCalculatePiRow() {
    double result;
    errorCodes status;
    
    status = calculatePiRow(1e-6, &result);
    assert(status == OK);
    assert(result > 3.1 && result < 3.2);
    
    printf("testCalculatePiRow: OK\n");
}

// Тесты для calculateEEquation
void testCalculateEEquation() {
    double result;
    errorCodes status;
    
    status = calculateEEquation(1e-6, &result);
    assert(status == OK);
    assert(result > 2.7 && result < 2.8);
    
    printf("testCalculateEEquation: OK\n");
}

// Тесты для isDoubleOverflow
void testIsDoubleOverflow() {
    errorCodes status;
    
    status = isDoubleOverflow(1.0);
    assert(status == OK);
    
    status = isDoubleOverflow(DBL_MAX * 2);
    assert(status == OVERFLOW_ERROR);
    
    status = isDoubleOverflow(HUGE_VAL);
    assert(status == OVERFLOW_ERROR);
    
    status = isDoubleOverflow(-HUGE_VAL);
    assert(status == OVERFLOW_ERROR);
    
    status = isDoubleOverflow(NAN);
    assert(status == OVERFLOW_ERROR);
    
    printf("testIsDoubleOverflow: OK\n");
}

// Тесты для calculateHarmonicNumber
void testCalculateHarmonicNumber() {
    double result;
    
    result = calculateHarmonicNumber(1);
    assert(doublesEqual(result, 1.0, 1e-10));
    
    result = calculateHarmonicNumber(2);
    assert(doublesEqual(result, 1.5, 1e-10));
    
    result = calculateHarmonicNumber(3);
    assert(doublesEqual(result, 1.0 + 1.0/2 + 1.0/3, 1e-10));
    
    printf("testCalculateHarmonicNumber: OK\n");
}

// Тесты для isPrime
void testIsPrime() {
    assert(isPrime(2) == 1);
    assert(isPrime(3) == 1);
    assert(isPrime(4) == 0);
    assert(isPrime(5) == 1);
    assert(isPrime(10) == 0);
    assert(isPrime(13) == 1);
    assert(isPrime(1) == 0);
    assert(isPrime(0) == 0);
    
    printf("testIsPrime: OK\n");
}

// Комплексный тест всех методов
void testAllMethods() {
    double results[15];
    double eps = 1e-6;
    
    getResults(eps, results);
    
    // Проверяем, что все результаты - валидные числа
    for (int i = 0; i < 15; i++) {
        assert(!isnan(results[i]));
        assert(!isinf(results[i]));
    }
    
    printf("testAllMethods: OK\n");
}

void testAll() {
    testTransferToDouble();
    testIsDoubleOverflow();
    testCalculateHarmonicNumber();
    testIsPrime();
    
    testCalculateELimit();
    testCalculatePiLimit();
    testCalculateLnLimit();
    testCalculateSqrt2Limit();
    
    testCalculateERow();
    testCalculatePiRow();
    
    testCalculateEEquation();
    
    testAllMethods();
    
    printf("All internal tests passed!\n");
}

int main() {
    testAll();
    return 0;
}