#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
    CALCULATION_ERROR = 9
} errorCodes;

errorCodes eRow(double eps, double* result);
errorCodes eLimit(double eps, double* result);
errorCodes eEquation(double eps, double* result);

errorCodes lnLimit(double eps, double* result);
errorCodes lnRow(double eps, double* result);
errorCodes lnEquation(double eps, double* result);

errorCodes sqrtEquation(double eps, double* result);
errorCodes sqrtRow(double eps, double* result);
errorCodes sqrtLimit(double eps, double* result);

errorCodes piLimit(double eps, double* result);
errorCodes piEquation(double eps, double* result);
errorCodes piRow(double eps, double* result);

errorCodes gammaLimit(double eps, double* result);
errorCodes gammaRow(double eps, double* result);
errorCodes gammaEquation(double eps, double* result);

#endif