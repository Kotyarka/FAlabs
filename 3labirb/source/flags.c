#include "../include/flags.h"


errorCodes isValidInteger(const char* str) {
    if (str == NULL) {
        return POINTER_ERROR;
    }
    
    if (*str == '\0') {
        return BAD_INPUT;
    }
    
    int i = 0;
    
    while (str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    
    if (str[i] == '\0') {
        return BAD_INPUT;
    }
    

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return BAD_INPUT;
        }
    }
    
    return OK;
}

errorCodes isValidDouble(const char* str) {
    if (str == NULL) {
        return POINTER_ERROR;
    }
    
    if (*str == '\0') {
        return BAD_INPUT;
    }
    
    int i = 0;
    int has_digit = 0;
    int has_dot = 0;
    
    while (str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            has_digit = 1; 
        }
        else if (str[i] == '.') {
            if (has_dot) {
                return BAD_INPUT; 
            }
            has_dot = 1;
        }
        else if (str[i] == ' ') {
            while (str[i] == ' ') {
                i++;
            }
            if (str[i] != '\0') {
                return BAD_INPUT;  
            }
            break;
        }
        else {
            return BAD_INPUT; 
        }
    }
    
    return has_digit ? OK : BAD_INPUT;
}
errorCodes solveAllPermutations(double eps, double a, double b, double c) {
    double coefficients[3] = {a, b, c};
    int permutationCount = 0;
    
    printf("All permutations and their solutions:\n");
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i != j && i != k && j != k) {
                    permutationCount++;
                    quadraticSolution solution;
                    errorCodes resultCode;
                    
                    resultCode = equationSolving(eps, coefficients[i], coefficients[j], coefficients[k], &solution);
                    
                    if (resultCode == OK) {
                        printf("Coefficients: a=%.2f, b=%.2f, c=%.2f -> ", 
                               coefficients[i], coefficients[j], coefficients[k]);
                        
                        switch (solution.rootsCount) {
                            case -1:
                                printf("not a quadratic equation\n");
                                break;
                            case 0:
                                printf("no real roots\n");
                                break;
                            case 1:
                                printf("one root: %.6f\n", solution.r1);
                                break;
                            case 2:
                                printf("two roots: %.6f, %.6f\n", solution.r1, solution.r2);
                                break;
                        }
                    } else {
                        printf("Error solving equation for permutation %d\n", permutationCount);
                        return resultCode;
                    }
                }
            }
        }
    }
    
    return OK;
}

errorCodes canFormTriangle(float a, float b, float c) {
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return OK;
    }
    return BAD_INPUT;
}

errorCodes convertStrToNum(const char* str, int* num) {
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }
    
    errorCodes validationResult = isValidInteger(str);
    if (validationResult != OK) {
        return validationResult;
    }

    char* end_ptr = NULL;
    long tmp = strtol(str, &end_ptr, 10);
    
    if (*end_ptr != '\0') {
        return BAD_INPUT;
    }
    if (tmp > INT_MAX || tmp < INT_MIN) {
        return OVERFLOW_ERROR;
    }

    *num = (int)tmp;
    return OK;
}

errorCodes isFlagValid(const char* flag) {
    if (flag == NULL) {
        return POINTER_ERROR;
    }
    
    if (!(flag[0] == '-' || flag[0] == '/') || strlen(flag) != 2) {
        return BAD_INPUT;
    }
    switch (flag[1]) {
        case 'q':
        case 'm':
        case 't':
            return OK;
        default:
            return BAD_INPUT;
    }
}

errorCodes equationSolving(double eps, double a, double b, double c, quadraticSolution* answer) {
    if (answer == NULL) {
        return POINTER_ERROR;
    }
    
    if (fabs(a) < eps) {
        answer->rootsCount = -1;
        answer->r1 = 0;
        answer->r2 = 0;
        return OK;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (fabs(discriminant) < eps) {
        answer->rootsCount = 1;
        answer->r1 = -b / (2 * a);
        answer->r2 = answer->r1;
    }
    else if (discriminant > 0) {
        answer->rootsCount = 2;
        answer->r1 = (-b + sqrt(discriminant)) / (2 * a);
        answer->r2 = (-b - sqrt(discriminant)) / (2 * a);
    }
    else {
        answer->rootsCount = 0;
        answer->r1 = 0;
        answer->r2 = 0;
    }
    
    return OK;
}

errorCodes m(int a, int b, int* isMultiple) {
    if (isMultiple == NULL) {
        return POINTER_ERROR;
    }
    
    if (a == 0 || b == 0) {
        return BAD_INPUT;
    }
    
    if (a % b == 0) {
        *isMultiple = 1;
    } else {
        *isMultiple = 0;
    }
    
    return OK;
}

errorCodes t(double eps, float a, float b, float c, int* isTriangle) {
    if (isTriangle == NULL) {
        return POINTER_ERROR;
    }
    
    if (a <= 0 || b <= 0 || c <= 0) {
        *isTriangle = 0;
        return OK;
    }
     
    if (canFormTriangle(a, b, c) != OK) {
        *isTriangle = 0;
        return OK;
    }
    
    float sides[3] = {a, b, c};
     
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (sides[j] > sides[j + 1]) {
                float temp = sides[j];
                sides[j] = sides[j + 1];
                sides[j + 1] = temp;
            }
        }
    }
    
    double hypotenuse_sq = sides[2] * sides[2];
    double legs_sq_sum = sides[0] * sides[0] + sides[1] * sides[1];
    
    if (fabs(hypotenuse_sq - legs_sq_sum) < eps) {
        *isTriangle = 1; 
    } else {
        *isTriangle = 0;
    }
    
    return OK;
}