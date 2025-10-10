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

typedef double (*function)(double x);

double aFunction(double x);
double bFunction(double x);
double cFunction(double x);
double dFunction(double x);

double trapezoidProcess(function f, double a, double b, int splitsCount, double previousSum);
errorCodes trapezoidRule (function f, double a, double b, double eps, double* result);

#endif
