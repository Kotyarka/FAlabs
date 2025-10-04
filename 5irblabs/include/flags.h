#ifndef FLAGS_H
#define FLAGS_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
    OPENING_FILE_ERROR = 6,
} errorCodes;


errorCodes isFlagValid(const char* flag);

errorCodes d(FILE* input, FILE* output);
errorCodes i(FILE* input, FILE* output);
errorCodes s(FILE* input, FILE* output);
errorCodes a(FILE* input, FILE* output);
#endif