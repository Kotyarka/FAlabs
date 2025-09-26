#ifndef FLAGS_H
#define FLAGS_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum return_code {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
};

int convertStrToNum(const char* str, int* num);
int isFlagValid(const char* flag);

int h(int num, int* list, int* count);
int p(const int x, int* isPrime);
int s(int x, char* hexRepr, int* ind);
int e(int x, long*** list);
int f(const int x, long* fact);
int a(const int x, int* result);

#endif