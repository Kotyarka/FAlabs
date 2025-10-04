#include "../include/numbers.h"

errorCodes isDoubleOverflow(double toCheck) {
    if ((fabs(toCheck) > DBL_MAX) || toCheck == HUGE_VAL || toCheck == -HUGE_VAL || isnan(toCheck) || isinf(toCheck)) {
        return OVERFLOW_ERROR;
    }
    return OK;
}

double calculateHarmonicNumber(double number) {
    double sum = 1;
    for (int i = 2; i <= number; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

errorCodes transferToDouble(const char* str, double* num) {
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }
    
    char* endPtr;
    double value = strtod(str, &endPtr);

    if (*endPtr != '\0') {
        return NOT_A_DOUBLE_ERROR;
    }
    
    errorCodes overflowCheck = isDoubleOverflow(value);
    if (overflowCheck != OK) {
        return overflowCheck;
    }
    
    *num = value;
    return OK;
}

errorCodes calculateELimit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double currentE = 1, prevE = 0;
    int i = 1;
    while (fabs(currentE - prevE) > eps) {
        prevE = currentE;
        currentE = pow(1 + 1.0 / i, i);
        ++i;
    }

    *result = currentE;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculatePiLimit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double current = 4, prev, add = 4;
    long n = 2;
    do {
        prev = current;
        add *= ((double)n / (2 * n - 1)) * ((double)n / (2 * n - 1)) * ((double)n / (2 * n)) * ((double)n / (2 * n));
        add *= 16;
        current = add / n;
        ++n;
    } while (fabs(current - prev) > eps);

    *result = current;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateLnLimit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double current = 1, prev;
    long n = 2;
    do {
        prev = current;
        current = (pow(2, 1.0 / n) - 1) * n;
        ++n;
    } while (fabs(current - prev) > eps);
    
    *result = current;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateSqrt2Limit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double current = -0.5, prev;
    long n = 1;
    do {
        prev = current;
        current = (current - (current * current / 2) + 1);
        ++n;
    } while (fabs(current - prev) > eps);
    
    *result = current;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateGammaLimit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double previous = 0, current = 1;
    long n = 1;
    while (fabs(previous - current) > eps) {
        previous = current;
        n *= 2;
        current = calculateHarmonicNumber(n) - log(n);
    }
    
    *result = current;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateERow(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double e = 1.0, add = 1;
    int i = 2;
    while (add > eps) {
        e += add;
        add /= i;
        ++i;
    }
    
    *result = e;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculatePiRow(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double pi = 0, add;
    int i = 1;
    do {
        add = ((double)1) / (2 * i - 1);

        if ((i - 1) % 2 == 0) {
            pi += add;
        } else {
            pi -= add;
        }
        ++i;
    } while (add > eps);
    
    *result = pi * 4;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateLnRow(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double ln = 0, add = 100;
    int i = 1;
    while (fabs(add) > eps) {
        add = ((double)1) / i;

        if ((i - 1) % 2 == 0) {
            ln += add;
        } else {
            ln -= add;
        }
        ++i;
    }
    
    *result = ln;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateSqrt2Row(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double sqrt2 = 1, degree2 = 0.25;
    while (fabs(degree2) > eps) {
        sqrt2 *= pow(2, degree2);
        degree2 *= 0.5;
    }
    
    *result = sqrt2;
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateGammaRow(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    eps = eps / 100000;
    double sigma = 0, add;
    long k = 2, sqrtFloor;
    do {
        sqrtFloor = (long)(sqrt(k));
        if (sqrtFloor * sqrtFloor == k) {
            ++k;
            sqrtFloor = (long)sqrt(k);
        }
        add = (1.0 / (sqrtFloor * sqrtFloor)) - (1.0 / k);
        sigma += add;
        ++k;
    } while (fabs(add) > eps);

    double pi;
    calculatePiRow(eps, &pi);
    *result = sigma - (pi * pi / 6);
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

double calculateEquationByFunc(double left, double right, double equals, function f, double eps) {
    double middle = (left + right) / 2;
    double res = f(middle);

    if (fabs(res - equals) < eps) {
        return middle;
    } else if (res > equals) {
        return calculateEquationByFunc(left, middle, equals, f, eps);
    } else {
        return calculateEquationByFunc(middle, right, equals, f, eps);
    }
}

errorCodes calculateEEquation(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    *result = calculateEquationByFunc(1, 3, 1, &log, eps);
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK; 
}

errorCodes calculatePiEquation(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double f;
    double x = 3;
    double df;

    f = cos(x) + 1.0;
    while(fabs(f) > eps) {
        df = -sin(x);
        x = x - f / df;
        f = cos(x) + 1.0;
    }
    
    *result = x;
    if (isnan(x)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

errorCodes calculateLnEquation(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    *result = calculateEquationByFunc(0, 1, 2, &exp, eps);
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK; 
}

double squareFunction(double x) {
    return x * x;
}

errorCodes calculateSqrt2Equation(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    *result = calculateEquationByFunc(1, 3, 2, &squareFunction, eps);
    if (isnan(*result)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK; 
}

errorCodes calculateGammaEquation(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    int p = 2;
    double current = log(2) * 0.5, previous = 0, product = 0.5;
    do {
        previous = current;
        do {
            p++;
        } while (!isPrime(p));
        product *= (p - 1.0)/p;
        current = log(p) * product;
    } while (fabs(previous - current) >= eps);
    
    *result = -log(current);
    if (isnan(current)) {
        return TOO_SMALL_EPSILON_ERROR;
    }
    return OK;
}

void getResults(double eps, double results[15]) {
    calculateELimit(eps, &results[0]);
    calculatePiLimit(eps, &results[1]);
    calculateLnLimit(eps, &results[2]);
    calculateSqrt2Limit(eps, &results[3]);
    calculateGammaLimit(eps, &results[4]);

    calculateERow(eps, &results[5]);
    calculatePiRow(eps, &results[6]);
    calculateLnRow(eps, &results[7]);
    calculateSqrt2Row(eps, &results[8]);
    calculateGammaRow(eps, &results[9]);

    calculateEEquation(eps, &results[10]);
    calculatePiEquation(eps, &results[11]);
    calculateLnEquation(eps, &results[12]);
    calculateSqrt2Equation(eps, &results[13]);
    calculateGammaEquation(eps, &results[14]);
}