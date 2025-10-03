#ifndef FLAGS_H
#define FLAGS_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
} errorCodes;

errorCodes convertStrToNum(const char* str, int* num);
errorCodes isFlagValid(const char* flag);

errorCodes h(int num, int* list, int* count);
errorCodes p(const int x, int* isPrime);
errorCodes s(int x, char* hexRepr, int* ind);
errorCodes e(int x, long*** list);
errorCodes f(const int x, long* fact);
errorCodes a(const int x, int* result);

#endif