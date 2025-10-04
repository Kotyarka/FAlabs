#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../include/primenumbers.h"

// Вспомогательная функция для сравнения массивов
int arrays_equal(const int* actual, const int* expected, int size) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    
    for (int i = 0; i < size; i++) {
        if (actual[i] != expected[i]) {
            return 0;
        }
    }
    return 1;
}

// Тесты для функции findPrimes
void test_findPrimes() {
    int* primes_array = NULL;
    int primes_count = 0;

    // Тест 1: n=5 (первые 5 простых чисел)
    errorCodes status = findPrimes(5, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 5);
    
    int expected_5[] = {2, 3, 5, 7, 11};
    assert(arrays_equal(primes_array, expected_5, 5));
    free(primes_array);
    primes_array = NULL;

    // Тест 2: n=1 (первое простое число)
    status = findPrimes(1, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 1);
    assert(primes_array[0] == 2);
    free(primes_array);
    primes_array = NULL;

    // Тест 3: n=0 (нет простых чисел)
    status = findPrimes(0, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 0);
    assert(primes_array == NULL);

    // Тест 4: n=10 (первые 10 простых чисел)
    status = findPrimes(10, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 10);
    
    int expected_10[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    assert(arrays_equal(primes_array, expected_10, 10));
    free(primes_array);
    primes_array = NULL;

    // Тест 5: n=-1 (некорректный ввод)
    status = findPrimes(-1, &primes_array, &primes_count);
    assert(status == BAD_INPUT);

    // Тест 6: n=1000000 (слишком большое число)
    status = findPrimes(1000000, &primes_array, &primes_count);
    assert(status == OVERFLOW_ERROR);

    printf("test_findPrimes: OK\n");
}

// Тесты для проверки граничных случаев
void test_edge_cases() {
    int* primes_array = NULL;
    int primes_count = 0;

    // Тест 1: n=2 (минимальное ненулевое простое число)
    errorCodes status = findPrimes(2, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 2);
    assert(primes_array[0] == 2);
    assert(primes_array[1] == 3);
    free(primes_array);
    primes_array = NULL;

    // Тест 2: n=3
    status = findPrimes(3, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 3);
    assert(primes_array[0] == 2);
    assert(primes_array[1] == 3);
    assert(primes_array[2] == 5);
    free(primes_array);
    primes_array = NULL;

    printf("test_edge_cases: OK\n");
}

// Тест производительности для средних значений
void test_performance_cases() {
    int* primes_array = NULL;
    int primes_count = 0;

    // Тест 1: n=100 (первые 100 простых чисел)
    errorCodes status = findPrimes(100, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 100);
    // Проверяем несколько известных значений
    assert(primes_array[0] == 2);    // 1-е простое
    assert(primes_array[4] == 11);   // 5-е простое
    assert(primes_array[24] == 97);  // 25-е простое
    assert(primes_array[99] == 541); // 100-е простое
    free(primes_array);
    primes_array = NULL;

    // Тест 2: n=1000 (первые 1000 простых чисел)
    status = findPrimes(1000, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_count == 1000);
    // Проверяем граничные значения
    assert(primes_array[0] == 2);      // 1-е простое
    assert(primes_array[999] == 7919); // 1000-е простое
    free(primes_array);
    primes_array = NULL;

    printf("test_performance_cases: OK\n");
}

// Тест на обработку ошибок памяти
void test_memory_handling() {
    int* primes_array = NULL;
    int primes_count = 0;

    // Тест должен пройти без утечек памяти
    errorCodes status = findPrimes(5, &primes_array, &primes_count);
    assert(status == OK);
    assert(primes_array != NULL);
    assert(primes_count == 5);
    
    // Освобождаем память
    free(primes_array);
    primes_array = NULL;

    // Тест с нулевым указателем на выходной массив
    status = findPrimes(5, NULL, &primes_count);
    assert(status != OK);

    printf("test_memory_handling: OK\n");
}

void test_all() {
    test_findPrimes();
    test_edge_cases();
    test_performance_cases();
    test_memory_handling();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}