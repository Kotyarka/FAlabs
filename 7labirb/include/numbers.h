#ifndef NUMBERS_H
#define NUMBERS_H

#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
    INVALID_BASE = 6,
    EMPTY_INPUT = 7,
    INVALID_DIGIT = 8,
    CONVERSION_ERROR = 9,
    FILE_ERROR = 10,
    INVALID_NUMBER = 11
} errorCodes;

errorCodes numChecker(char* str, const int* base, int* isMinus);
errorCodes toDecInt(char* str, const int base, long* num);
errorCodes removeLeadingZeros(char* str);
errorCodes findMinBase(char* numberStr, int* minBase);

#endif