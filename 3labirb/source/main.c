#include "../include/flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Wrong value of arguments\n");
        return WRONG_ARGUMENTS;
    }

    char* flag = argv[1];
    
    errorCodes flagCheck = isFlagValid(flag);
    if (flagCheck != OK) { 
        printf("Error occurred: %d\n", flagCheck);
        return flagCheck;
    }
    
    char flagChar = flag[1];
    errorCodes resultCode = OK;
    
    switch (flagChar) {
        case 'q': {
            if (argc != 6) {
                printf("Wrong value of arguments for -q. Expected: -q epsilon a b c\n");
                return WRONG_ARGUMENTS;
            }
            
            errorCodes epsValidation = isValidDouble(argv[2]);
            if (epsValidation != OK) {
                printf("Error: epsilon must be a valid number\n");
                return BAD_INPUT;
            }
            double eps = atof(argv[2]);
            if (eps <= 0) {
                printf("Error: epsilon must be positive\n");
                return BAD_INPUT;
            }
            
            for (int i = 3; i < 6; i++) {
                errorCodes coeffValidation = isValidDouble(argv[i]);
                if (coeffValidation != OK) {
                    printf("Error: coefficient must be a valid number\n");
                    return BAD_INPUT;
                }
            }
            
            double a = atof(argv[3]);
            double b = atof(argv[4]);
            double c = atof(argv[5]);
            
            resultCode = solveAllPermutations(eps, a, b, c);
            break;
        }
        case 'm': {
            if (argc != 4) {
                printf("Wrong value of arguments for -m. Expected: -m num1 num2\n");
                return WRONG_ARGUMENTS;
            }
            errorCodes num1Validation = isValidInteger(argv[2]);
            errorCodes num2Validation = isValidInteger(argv[3]);
            if (num1Validation != OK || num2Validation != OK) {
                printf("Numbers must be valid integers\n");
                return BAD_INPUT;
            }
            
            int num1, num2;
            errorCodes convertResult1 = convertStrToNum(argv[2], &num1);
            errorCodes convertResult2 = convertStrToNum(argv[3], &num2);
            
            if (convertResult1 != OK || convertResult2 != OK) {
                printf("Invalid number format\n");
                return BAD_INPUT;
            }
            
            int isMultiple;
            resultCode = m(num1, num2, &isMultiple);
            
            if (resultCode == OK) {
                if (isMultiple) {
                    printf("%d is multiple of %d\n", num1, num2);
                } else {
                    printf("%d is not multiple of %d\n", num1, num2);
                }
            }
            break;
        }
        case 't': {
            if (argc != 6) {
                printf("Wrong value of arguments for -t. Expected: -t epsilon a b c\n");
                return WRONG_ARGUMENTS;
            }
            
            errorCodes epsValidation = isValidDouble(argv[2]);
            if (epsValidation != OK) {
                printf("Epsilon must be a valid number\n");
                return BAD_INPUT;
            }
            double eps = atof(argv[2]);
            if (eps <= 0) {
                printf("Epsilon must be positive\n");
                return BAD_INPUT;
            }
            
            for (int i = 3; i < 6; i++) {
                errorCodes sideValidation = isValidDouble(argv[i]);
                if (sideValidation != OK) {
                    printf("Error: side length must be a valid number\n");
                    return BAD_INPUT;
                }
            }
            
            float a = atof(argv[3]);
            float b = atof(argv[4]);
            float c = atof(argv[5]);
            
            if (a <= 0 || b <= 0 || c <= 0) {
                printf("Error: all sides must be positive numbers\n");
                return BAD_INPUT;
            }
            errorCodes triangleValidation = canFormTriangle(a, b, c);
            if (triangleValidation != OK) {
                printf("Error: sides %.2f, %.2f, %.2f cannot form any triangle\n", a, b, c);
                return BAD_INPUT;
            }
            
            int isTriangle;
            resultCode = t(eps, a, b, c, &isTriangle);
            
            if (resultCode == OK) {
                if (isTriangle) {
                    printf("Numbers %.2f, %.2f, %.2f can be sides of a right triangle\n", a, b, c);
                } else {
                    printf("Numbers %.2f, %.2f, %.2f cannot be sides of a right triangle\n", a, b, c);
                }
            }
            break;
        }
        default: {
            printf("Unknown flag: %s\n", flag);
            return WRONG_ARGUMENTS;
        }
    }
    
    if (resultCode != OK) {
        return resultCode;
    }
    
    return OK;
}