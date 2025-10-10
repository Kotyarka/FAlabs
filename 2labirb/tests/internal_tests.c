#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "../include/primenumbers.h"

static bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

static void verifyFirstNPrimes(int* primes, int n) {
    int knownPrimes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
        157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229
    };
    
    for (int i = 0; i < n && i < 50; i++) {
        assert(primes[i] == knownPrimes[i]);
    }
}

static void testFindPrimesBasic() {
    printf("Running testFindPrimesBasic...\n");
    
    int* primesArray;
    
    // Тест 1: n = 1
    errorCodes result = findPrimes(1, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    assert(primesArray[0] == 2);
    free(primesArray);
    
    // Тест 2: n = 5
    result = findPrimes(5, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    verifyFirstNPrimes(primesArray, 5);
    free(primesArray);
    
    // Тест 3: n = 10
    result = findPrimes(10, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    verifyFirstNPrimes(primesArray, 10);
    free(primesArray);
    
    printf("testFindPrimesBasic: PASSED\n\n");
}

static void testFindPrimesBoundary() {
    printf("Running testFindPrimesBoundary...\n");
    
    int* primesArray;
    
    // Тест 1: n = 0
    errorCodes result = findPrimes(0, &primesArray);
    assert(result == OK);
    assert(primesArray == NULL);
    
    // Тест 2: n = 2
    result = findPrimes(2, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    assert(primesArray[0] == 2);
    assert(primesArray[1] == 3);
    free(primesArray);
    
    // Тест 3: n = 100
    result = findPrimes(100, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    
    // Проверяем, что все числа действительно простые и в правильном порядке
    for (int i = 0; i < 100; i++) {
        assert(isPrime(primesArray[i]));
        if (i > 0) {
            assert(primesArray[i] > primesArray[i-1]);
        }
    }
    // Проверяем конкретные известные значения
    assert(primesArray[0] == 2);    // 1-е простое
    assert(primesArray[4] == 11);   // 5-е простое
    assert(primesArray[99] == 541); // 100-е простое
    free(primesArray);
    
    printf("testFindPrimesBoundary: PASSED\n\n");
}

static void testFindPrimesErrorCases() {
    printf("Running testFindPrimesErrorCases...\n");
    
    int* primesArray;
    
    // Тест 1: Отрицательное n
    errorCodes result = findPrimes(-5, &primesArray);
    assert(result == OK);
    assert(primesArray == NULL);
    
    // Тест 2: Слишком большое n (больше 100000)
    result = findPrimes(100001, &primesArray);
    assert(result == OVERFLOW_ERROR);
    
    printf("testFindPrimesErrorCases: PASSED\n\n");
}

static void testFindPrimesLargeValues() {
    printf("Running testFindPrimesLargeValues...\n");
    
    int* primesArray;
    
    // Тест с большими значениями (в пределах ограничения)
    errorCodes result = findPrimes(1000, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    
    // Проверяем, что первые 1000 чисел простые
    for (int i = 0; i < 1000; i++) {
        assert(isPrime(primesArray[i]));
    }
    
    // Проверяем несколько известных значений
    assert(primesArray[0] == 2);      // 1-е простое
    assert(primesArray[99] == 541);   // 100-е простое
    assert(primesArray[999] == 7919); // 1000-е простое
    
    free(primesArray);
    
    printf("testFindPrimesLargeValues: PASSED\n\n");
}

static void testFindPrimesEdgeCases() {
    printf("Running testFindPrimesEdgeCases...\n");
    
    int* primesArray;
    
    // Тест малых значений, которые обрабатываются специально в коде (n < 6)
    for (int n = 1; n < 6; n++) {
        errorCodes result = findPrimes(n, &primesArray);
        assert(result == OK);
        assert(primesArray != NULL);
        
        // Проверяем, что все числа простые
        for (int i = 0; i < n; i++) {
            assert(isPrime(primesArray[i]));
        }
        
        free(primesArray);
    }
    
    printf("testFindPrimesEdgeCases: PASSED\n\n");
}

static void testFindPrimesMemoryManagement() {
    printf("Running testFindPrimesMemoryManagement...\n");
    
    int* primesArray;
    
    // Многократный вызов для проверки утечек памяти
    for (int i = 0; i < 10; i++) {
        errorCodes result = findPrimes(10, &primesArray);
        assert(result == OK);
        assert(primesArray != NULL);
        free(primesArray); // Важно освобождать память
    }
    
    printf("testFindPrimesMemoryManagement: PASSED\n\n");
}

static void testFindPrimesConsistency() {
    printf("Running testFindPrimesConsistency...\n");
    
    int* primesArray1;
    int* primesArray2;
    
    errorCodes result1 = findPrimes(50, &primesArray1);
    errorCodes result2 = findPrimes(50, &primesArray2);
    
    assert(result1 == OK);
    assert(result2 == OK);
    assert(primesArray1 != NULL);
    assert(primesArray2 != NULL);
    
    for (int i = 0; i < 50; i++) {
        assert(primesArray1[i] == primesArray2[i]);
    }
    
    free(primesArray1);
    free(primesArray2);
    
    printf("testFindPrimesConsistency: PASSED\n\n");
}

static void testFindPrimesSpecificValues() {
    printf("Running testFindPrimesSpecificValues...\n");
    
    int* primesArray;
    
    // Тестируем конкретные известные значения
    struct TestCase {
        int n;
        int expectedPrime;
    } testCases[] = {
        {1, 2},
        {2, 3},
        {3, 5},
        {4, 7},
        {5, 11},
        {10, 29},
        {20, 71},
        {50, 229},
        {100, 541},
        {500, 3571}
    };
    
    size_t testCasesCount = sizeof(testCases) / sizeof(testCases[0]);
    for (size_t i = 0; i < testCasesCount; i++) {
        errorCodes result = findPrimes(testCases[i].n, &primesArray);
        assert(result == OK);
        assert(primesArray != NULL);
        assert(primesArray[testCases[i].n - 1] == testCases[i].expectedPrime);
        free(primesArray);
    }
    
    printf("testFindPrimesSpecificValues: PASSED\n\n");
}

static void testFindPrimesArraySize() {
    printf("Running testFindPrimesArraySize...\n");
    
    int* primesArray;
    
    // Тест: проверяем, что массив содержит ровно n элементов
    int n = 25;
    errorCodes result = findPrimes(n, &primesArray);
    assert(result == OK);
    assert(primesArray != NULL);
    
    // Проверяем, что можем безопасно обращаться к элементам 0..n-1
    for (int i = 0; i < n; i++) {
        assert(primesArray[i] > 0);
        assert(isPrime(primesArray[i]));
    }
    
    free(primesArray);
    
    printf("testFindPrimesArraySize: PASSED\n\n");
}

int main() {
    printf("Starting internal tests for prime numbers library...\n\n");
    
    testFindPrimesBasic();
    testFindPrimesBoundary();
    testFindPrimesErrorCases();
    testFindPrimesLargeValues();
    testFindPrimesEdgeCases();
    testFindPrimesMemoryManagement();
    testFindPrimesConsistency();
    testFindPrimesSpecificValues();
    testFindPrimesArraySize();
    
    printf("========================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("========================================\n");
    
    return 0;
}