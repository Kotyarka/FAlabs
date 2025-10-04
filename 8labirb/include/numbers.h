#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#ifndef NUMBERS_H
#define NUMBERS_H


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
    CONVERSION_ERROR = 9
} errorCodes;

errorCodes baseParsing(char* str, int* base);
errorCodes numChecker(char* str, const int* base, int* isMinus);
errorCodes toDecInt(char* str, const int base, long* num);
errorCodes toNsystem(char* str, const int base, long* num);

#endif