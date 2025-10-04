#ifndef NUMBERS_H
#define NUMBERS_H

#include <float.h>
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
    NOT_A_DOUBLE_ERROR = 6,
    NOT_AN_INTEGER_ERROR = 7,
    TOO_SMALL_EPSILON_ERROR = 8,
} errorCodes;

typedef double (*function)(double);

errorCodes transferToDouble(const char* str, double* num);
errorCodes isDoubleOverflow(double toCheck);
double calculateHarmonicNumber(double number);
int isPrime(int n);

errorCodes calculateELimit(double eps, double* result);
errorCodes calculatePiLimit(double eps, double* result);
errorCodes calculateLnLimit(double eps, double* result);
errorCodes calculateSqrt2Limit(double eps, double* result);
errorCodes calculateGammaLimit(double eps, double* result);

errorCodes calculateERow(double eps, double* result);
errorCodes calculatePiRow(double eps, double* result);
errorCodes calculateLnRow(double eps, double* result);
errorCodes calculateSqrt2Row(double eps, double* result);
errorCodes calculateGammaRow(double eps, double* result);

errorCodes calculateEEquation(double eps, double* result);
errorCodes calculatePiEquation(double eps, double* result);
errorCodes calculateLnEquation(double eps, double* result);
errorCodes calculateSqrt2Equation(double eps, double* result);
errorCodes calculateGammaEquation(double eps, double* result);

// Main functions
void getResults(double eps, double results[15]);

#endif