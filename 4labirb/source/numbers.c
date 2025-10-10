#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/numbers.h"
#include <string.h>

errorCodes eRow(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double e = 1.0;
    double currentTerm = 1.0;
    int termCounter = 1;

    while (currentTerm > eps) {
        currentTerm /= termCounter;
        e += currentTerm;
        termCounter++;
    }
    
    *result = e;
    return OK;
}

errorCodes eLimit(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    long long n = 1;         
    double previousE = 0.0;
    double currentE = pow(1.0 + 1.0/n, n);

    while (fabs(currentE - previousE) > eps) {
        previousE = currentE;
        n *= 2;  
        currentE = pow(1.0 + 1.0/n, n);
    }

    *result = currentE;
    return OK;
}

errorCodes eEquation(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double x = 2.0;
    while (fabs(log(x) - 1.0) * 10 > eps) {
        x = x - (log(x) - 1.0) * x;
    }
    
    *result = x;
    return OK;
}

errorCodes lnLimit(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    long long n = 1;
    double previousLn = 0.0;
    double currentLn = n * (pow(2.0, 1.0/n) - 1.0);

    while (fabs(currentLn - previousLn) > eps) {
        previousLn = currentLn;
        n *= 2;
        currentLn = n * (pow(2.0, 1.0/n) - 1.0);
    }

    *result = currentLn;
    return OK;
}

errorCodes lnRow(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double sumValue = 0.0;
    double currentTerm = 1.0;
    int termCounter = 1;

    while (fabs(currentTerm) > eps) {
        currentTerm = (termCounter % 2 == 1 ? 1.0 / termCounter : -1.0 / termCounter);
        sumValue += currentTerm;
        termCounter++;
    }

    *result = sumValue;
    return OK;
}

errorCodes lnEquation(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double x = 1.0;
    while (fabs(exp(x) - 2.0) > eps) {
        x = x - (exp(x) - 2.0) / exp(x);
    }
    
    *result = x;
    return OK;
}

errorCodes sqrtRow(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    int kValue = 2;
    double x = pow(2.0, 1.0/4.0);
    double previousValue = 0.0;

    while (fabs(x - previousValue) > eps) {
        previousValue = x;
        kValue++;
        x *= pow(2.0, 1.0 / pow(2.0, kValue));
    }

    *result = x;
    return OK;
}

errorCodes sqrtEquation(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double x = 1.0;
    while (fabs(x * x - 2.0) > eps) {
        x = (x + 2.0 / x) / 2.0;
    }
    
    *result = x;
    return OK;
}

errorCodes sqrtLimit(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double x = -0.5;
    double previousValue = x + 2 * eps; 
    while (fabs(x - previousValue) > eps) {
        previousValue = x;
        x = x - x * x / 2 + 1;
    }
    
    *result = x;
    return OK;
}

errorCodes piLimit(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double a_n = 4.0;
    double previous;
    int n = 2;
    int max_iterations = 1000000;
    do {
        previous = a_n;
        double ratio = (4.0 * n * (n-1)) / ((2.0 * n - 1.0) * (2.0 * n - 1.0));
        a_n *= ratio;
        n++;
        if (n > max_iterations) {
            return CALCULATION_ERROR;
        }
    } while (fabs(a_n - previous) > eps);
    *result = a_n;
    return OK;
}

errorCodes piRow(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double sum = 0.0;
    double term;
    int n = 1;
    int max_iterations = 100000000;
    double target_precision = eps / 4.0;
    do {
        term = 1.0 / (2 * n - 1);
        if (n % 2 == 0) term = -term;
        sum += term;
        n++;
        if (n > max_iterations) {
            return CALCULATION_ERROR;
        }
    } while (fabs(term) > target_precision);
    *result = 4.0 * sum;
    return OK;
}

errorCodes piEquation(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double x = 3.0;
    double delta = eps + 1;
    int iterationCount = 0;
    
    while (fabs(delta) > eps) {
        double functionValue = cos(x) + 1.0;
        double derivativeValue = -sin(x);
        
        if (fabs(derivativeValue) < 1e-12) {
            x += 0.1;
        } else {
            delta = functionValue / derivativeValue;
            x -= delta;
        }
        iterationCount++;
    }
    
    *result = x;
    return OK;
}

errorCodes gammaLimit(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double gammaValue = 0.0;
    double previousGamma = gammaValue + 2 * eps;
    int n = 1;
    
    while (fabs(gammaValue - previousGamma) > eps && n > -1) {
        previousGamma = gammaValue;
        gammaValue = 0.0;
        
        double harmonicSum = 0.0;
        for (int i = 1; i <= n; i++) {
            harmonicSum += 1.0 / i;
        }
        
        gammaValue = harmonicSum - log(n);
        n *= 2;
    }
    
    *result = gammaValue;
    return OK;
}

errorCodes gammaRow(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double piValue;
    errorCodes errorCode = piRow(eps, &piValue);
    if (errorCode != OK) return errorCode;
    
    double piSquaredOverSix = (piValue * piValue) / 6.0;
    double totalSum = 0.0;
    int n = 1;

    while (1) {
        int nSquared = n * n;
        int nextNSquared = (n + 1) * (n + 1);
        int termsCount = nextNSquared - nSquared;
        double sumFloor = (double)termsCount / nSquared;

        double harmonicSum = 0.0;
        for (int k = nSquared; k < nextNSquared; k++) {
            harmonicSum += 1.0 / k;
        }

        double intervalSum = sumFloor - harmonicSum;
        totalSum += intervalSum;

        if (fabs(intervalSum) < eps) {
            *result = -piSquaredOverSix + totalSum;
            return OK;
        }

        n++;
    }

    *result = -piSquaredOverSix + totalSum;
    return OK;
}

errorCodes gammaEquation(double eps, double* result) {
    if (eps <= 0) return WRONG_ARGUMENTS;
    if (result == NULL) return POINTER_ERROR;
    
    double t = 10.0;
    double previousGamma = 0.0;
    double gammaValue = 0.0;

    while (1) {
        int limit = (int)t;
        
        char* isPrime = (char*)malloc((limit + 1) * sizeof(char));
        if (!isPrime) return MALLOC_ERROR;
        
        memset(isPrime, 1, (limit + 1) * sizeof(char));
        isPrime[0] = isPrime[1] = 0;
        
        for (int i = 2; i * i <= limit; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= limit; j += i) {
                    isPrime[j] = 0;
                }
            }
        }

        double productValue = 1.0;
        for (int prime = 2; prime <= limit; prime++) {
            if (isPrime[prime]) {
                productValue *= 1.0 / (1.0 - 1.0 / prime);
            }
        }
        
        free(isPrime);

        previousGamma = gammaValue;
        gammaValue = log(productValue / log(t));

        if (fabs(gammaValue - previousGamma) < eps) {
            *result = gammaValue;
            return OK;
        }

        t *= 1.5; 
    }
}