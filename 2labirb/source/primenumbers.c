#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/primenumbers.h"

errorCodes findPrimes(int n, int** primesArray, int* primesCount) {
    if (n <= 0) {
        *primesCount = 0;
        *primesArray = NULL;
        return OK;
    }

    if (n > 100000) { 
        return OVERFLOW_ERROR;
    }

    int upperBound;
    if (n < 6) {
        upperBound = 20; 
    } else {
        upperBound = (int)(n * (log(n) + log(log(n)))) + 100;
    }

    bool* sieve = (bool*)malloc((upperBound + 1) * sizeof(bool));
    if (sieve == NULL) {
        return MALLOC_ERROR;
    }

    for (int i = 0; i <= upperBound; i++) {
        sieve[i] = true;
    }
    sieve[0] = false;
    sieve[1] = false;


    int sqrtUpper = (int)sqrt(upperBound);
    for (int i = 2; i <= sqrtUpper; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= upperBound; j += i) {
                sieve[j] = false;
            }
        }
    }

    *primesCount = 0;
    for (int i = 2; i <= upperBound; i++) {
        if (sieve[i]) {
            (*primesCount)++;
        }
    }

    if (*primesCount < n) {
        free(sieve);
        return OVERFLOW_ERROR;
    }

    *primesArray = (int*)malloc(n * sizeof(int));
    if (*primesArray == NULL) {
        free(sieve);
        return MALLOC_ERROR;
    }

    int index = 0;
    for (int i = 2; i <= upperBound && index < n; i++) {
        if (sieve[i]) {
            (*primesArray)[index++] = i;
        }
    }

    free(sieve);
    return OK;
}