#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    MALLOC_ERROR = 2,
    OVERFLOW_ERROR = 3,
    INDEX_ERROR  = 4,
} errorCodes;

errorCodes findPrimes(int n, int** primesArray, int* primesCount);

#endif