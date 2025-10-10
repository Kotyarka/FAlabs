#include "../include/functions.h"


double aFunction(double x) {
    if (fabs(x) < 1e-15) {
        return 1.0;
    }
    return log(1 + x) / x;
}

double bFunction(double x) {
    return exp(-x * x * 0.5);
}

double cFunction(double x) {
    if (x >= 1.0) {
    x = 1.0 - 1e-15;
    }
    return -log(1 - x);
}

double dFunction(double x) {
    if (x == 0.0) {
        return 1.0;
    }
    return pow(x, x);
}

double trapezoidProcess(function f, double a, double b, int splitsCount, double previousSum) {
    double step = (b - a) / splitsCount;
    double sum = 0.0;
    for (int i = 1; i < splitsCount; i+=2) {
        sum += f(a + step * i);
    }

    return previousSum / 2 + step * sum;
}

errorCodes trapezoidRule (function f, double a, double b, double eps, double* result) {
    if (f == NULL) {
        return POINTER_ERROR;
    }
    
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    *result = 0;

    int splitsCount = 1;
    double prevIteration = trapezoidProcess(f, a, b, splitsCount, 0);
    double currIteration;

    while (1) {
        splitsCount *= 2;
        currIteration = trapezoidProcess(f, a, b, splitsCount, prevIteration);
        if (fabs(currIteration - prevIteration) < eps) {
            *result = currIteration;
            return OK;
        }
        prevIteration = currIteration;
    }

}

