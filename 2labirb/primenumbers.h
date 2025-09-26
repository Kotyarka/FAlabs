#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

enum return_code {
    OK = 0,
    BAD_INPUT = 1,
    MEMORY_ALLOCATION_ERROR = 2,
    TOO_BIG_NUMBER = 3,
    WRONG_INDEX = 4
};

enum return_code find_primes(int n, int** primes_array, int* primes_count);

#endif