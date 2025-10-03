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
    OPENING_FILE_ERROR = 6,
    INVALID_NUMBER_ERROR = 7,
} errorCodes;

// Основная функция обработки чисел
errorCodes process_numbers(FILE* input, FILE* output);

// Вспомогательные функции
errorCodes find_min_base(const char* number, int* result_base);
errorCodes convert_to_decimal(const char* number, int base, long long* result);
errorCodes remove_leading_zeros(const char* number, char** result);
errorCodes read_next_token(FILE* file, char** result);

#endif