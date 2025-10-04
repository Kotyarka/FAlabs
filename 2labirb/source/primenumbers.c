#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../include/primenumbers.h"

errorCodes findPrimes(int n, int** primes_array, int* primes_count) {
    if (n <= 0) {
        *primes_count = 0;
        *primes_array = NULL;
        return OK;
    }

    if (n > 100000) { 
        return OVERFLOW_ERROR;
    }

    int upper_bound;
    if (n < 6) {
        upper_bound = 20; 
    } else {
        upper_bound = (int)(n * (log(n) + log(log(n)))) + 100;
    }

    bool* sieve = (bool*)malloc((upper_bound + 1) * sizeof(bool));
    if (sieve == NULL) {
        return MALLOC_ERROR;
    }

    for (int i = 0; i <= upper_bound; i++) {
        sieve[i] = true;
    }
    sieve[0] = false;
    sieve[1] = false;


    int sqrt_upper = (int)sqrt(upper_bound);
    for (int i = 2; i <= sqrt_upper; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= upper_bound; j += i) {
                sieve[j] = false;
            }
        }
    }

    *primes_count = 0;
    for (int i = 2; i <= upper_bound; i++) {
        if (sieve[i]) {
            (*primes_count)++;
        }
    }

    if (*primes_count < n) {
        free(sieve);
        return OVERFLOW_ERROR;
    }

    *primes_array = (int*)malloc(n * sizeof(int));
    if (*primes_array == NULL) {
        free(sieve);
        return MALLOC_ERROR;
    }

    int index = 0;
    for (int i = 2; i <= upper_bound && index < n; i++) {
        if (sieve[i]) {
            (*primes_array)[index++] = i;
        }
    }

    free(sieve);
    return OK;
}