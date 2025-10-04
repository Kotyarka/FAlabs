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
    long i = 1;
    while (fabs(currentE - prevE) > eps) {
        prevE = currentE;
        currentE = pow(1 + 1.0 / i, i);
        i++;
        if (i > 10000000) break;
    }

    *result = currentE;
    return OK;
}

errorCodes calculatePiLimit(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double previous = 0;
    double current = 4.0;
    long n = 1;
    
    while (n == 1 || fabs(current - previous) > eps) {
        previous = current;
        n++;
        
        double factorial_n = 1.0;
        for (long i = 1; i <= n; i++) {
            factorial_n *= i;
        }
        
        double factorial_2n = 1.0;
        for (long i = 1; i <= 2 * n; i++) {
            factorial_2n *= i;
        }
        
        double numerator = pow(pow(2, n) * factorial_n, 4);
        double denominator = n * pow(factorial_2n, 2);
        
        current = numerator / denominator;
        
        if (isnan(current) || isinf(current)) {
            *result = previous;
            return OK;
        }
        
        if (n > 10000) {
            *result = current;
            return OK;
        }
    }
    
    *result = current;
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
        n++;
        if (n > 10000000) break;
    } while (fabs(current - prev) > eps);
    
    *result = current;
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
        n++;
        if (n > 10000000) break;
    } while (fabs(current - prev) > eps);
    
    *result = current;
    return OK;
}

errorCodes calculateGammaLimit(double eps, double* result) {
    if (result == NULL) return POINTER_ERROR;
    if (eps <= 0) return BAD_INPUT;
    
    double previous = 0, current = 0;
    long m = 2;
    int max_iterations = 1000;
    
    do {
        previous = current;
        current = 0;
        
        for (long k = 1; k <= m; k++) {

            double binom = 1.0;
            for (long i = 1; i <= k; i++) {
                binom = binom * (m - i + 1) / i;
            }
            double ln_factorial = 0.0;
            for (long i = 1; i <= k; i++) {
                ln_factorial += log(i);
            }
            
            double sign = (k % 2 == 0) ? 1.0 : -1.0;
            double term = sign * binom * ln_factorial / k;
            
            current += term;
            
            if (isnan(current) || isinf(current)) {
                *result = previous;
                return OK;
            }
        }
        
        m++;
        
        if (m > max_iterations) {
            *result = current;
            return OK;
        }
        
    } while (fabs(current - previous) > eps);
    
    *result = current;
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
    long i = 2;
    while (add > eps) {
        e += add;
        add /= i;
        i++;
        if (i > 10000000) break;
    }
    
    *result = e;
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
    long i = 1;
    do {
        add = 1.0 / (2 * i - 1);

        if ((i - 1) % 2 == 0) {
            pi += add;
        } else {
            pi -= add;
        }
        i++;
        if (i > 10000000) break;
    } while (fabs(add) > eps);
    
    *result = pi * 4;
    return OK;
}

errorCodes calculateLnRow(double eps, double* result) {
    if (result == NULL) {
        return POINTER_ERROR;
    }
    if (eps <= 0) {
        return BAD_INPUT;
    }
    
    double ln = 0, add;
    long i = 1;
    do {
        add = 1.0 / i;

        if ((i - 1) % 2 == 0) {
            ln += add;
        } else {
            ln -= add;
        }
        i++;
        if (i > 10000000) break;
    } while (fabs(add) > eps);
    
    *result = ln;
    return OK;
}

errorCodes calculateSqrt2Row(double eps, double* result) {
    if (result == NULL) return POINTER_ERROR;
    if (eps <= 0) return BAD_INPUT;
    
    double product = 1.0;
    double prev_product;
    int k = 2;
    
    do {
        prev_product = product;
        double exponent = pow(0.5, k);
        product *= pow(2, exponent);
        k++;
        if (k > 1000) break;
    } while (fabs(product - prev_product) > eps);
    
    *result = product;
    return OK;
}

errorCodes calculateGammaRow(double eps, double* result) {
    if (result == NULL) return POINTER_ERROR;
    if (eps <= 0) return BAD_INPUT;
    
    double pi;
    errorCodes status = calculatePiRow(eps/10, &pi);
    if (status != OK) return status;
    double pi_sq_over_6 = (pi * pi) / 6.0;
    
    double sum = 0.0;
    double compensation = 0.0;
    double previous_gamma = 0.0;
    double current_gamma = -pi_sq_over_6; 
    long k = 2;
    
    long min_iterations = 100000;
    
    do {
        previous_gamma = current_gamma;
        
        long floor_sqrt_k = (long)sqrt(k);
        double term = 1.0 / ((double)floor_sqrt_k * floor_sqrt_k) - 1.0 / k;
        
        double y = term - compensation;
        double t = sum + y;
        compensation = (t - sum) - y;
        sum = t;
        
        current_gamma = -pi_sq_over_6 + sum;
        
        k++;

    } while (k < min_iterations || fabs(current_gamma - previous_gamma) > eps);
    
    *result = current_gamma;
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
    return OK; 
}

errorCodes calculateGammaEquation(double eps, double* result) {
    if (result == NULL) return POINTER_ERROR;
    if (eps <= 0) return BAD_INPUT;
    
    double product = 1.0;
    double prev_limit;
    double current_limit = 0;
    long t = 2;
    int prime_count = 0;
    
    int min_primes = 1000;
    
    do {
        prev_limit = current_limit;
        
        if (isPrime(t)) {
            product *= (t - 1.0) / t;
            prime_count++;
            current_limit = log(t) * product;
        }
        
        t++;
        
    } while (prime_count < min_primes || fabs(current_limit - prev_limit) > eps);
    
    *result = -log(current_limit);
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