#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "primenumbers.h"

enum return_code find_primes(int n, int** primes_array, int* primes_count) {
    if (n < 2) {
        *primes_count = 0;
        *primes_array = NULL;
        return OK;
    }

    if (n > 1000000) { 
        return TOO_BIG_NUMBER;
    }

    bool* resheto = (bool*)malloc((n + 1) * sizeof(bool));
    if (resheto == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i <= n; i++) {
        resheto[i] = true;
    }
    resheto[0] = false;
    resheto[1] = false;
    resheto[2] = true;
    for (int j = 4; j <= n; j += 2) {
        resheto[j] = false;
    }

    int sqrt_n = (int)sqrt(n);
    
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (resheto[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                resheto[j] = false;
            }
        }
    }

    *primes_count = 1; 
    for (int i = 3; i <= n; i += 2) {
        if (resheto[i]) {
            (*primes_count)++;
        }
    }

    *primes_array = (int*)malloc((*primes_count) * sizeof(int));
    if (*primes_array == NULL) {
        free(resheto);
        return MEMORY_ALLOCATION_ERROR;
    }

    (*primes_array)[0] = 2;
    int index = 1;
    for (int i = 3; i <= n; i += 2) {
        if (resheto[i]) {
            (*primes_array)[index++] = i;
        }
    }

    free(resheto);
    return OK;
}