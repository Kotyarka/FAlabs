#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
} errorCodes;

errorCodes isValidChar(char c, int base, int* isValid);
errorCodes charToValue(char c, int* value);
errorCodes convertFromBase(const char* str, int base, long long* result);
errorCodes convertToBase(long long num, int base, char* buffer, int bufferSize);
errorCodes removeLeadingZeros(char* str);
errorCodes readBase(int* base);
errorCodes processNumbers(int base, long long* maxAbsValue, char* maxOriginalStr, int maxStrSize);
errorCodes printResults(long long maxAbsValue, const char* maxOriginalStr);

#endif