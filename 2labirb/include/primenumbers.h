#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

typedef enum {
    OK = 0,
    MALLOC_ERROR = 1,
    OVERFLOW_ERROR = 2,
    BAD_INPUT = 3,
    INDEX_ERROR = 4
} errorCodes;

errorCodes findPrimes(int n, int** primesArray);

#endif