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

typedef struct {
    int rootsCount;
    double r1;
    double r2;
} quadraticSolution;

errorCodes convertStrToNum(const char* str, int* num);
errorCodes isFlagValid(const char* flag);
errorCodes isValidInteger(const char* str);
errorCodes isValidDouble(const char* str);
errorCodes canFormTriangle(float a, float b, float c);
errorCodes equationSolving(double eps, double a, double b, double c, quadraticSolution* answer);
errorCodes q(double eps, double a, double b, double c, quadraticSolution* answer);
errorCodes m(int a, int b, int* isMultiple);
errorCodes t(double eps, float a, float b, float c, int* isTriangle);
errorCodes solveAllPermutations(double eps, double a, double b, double c);

#endif