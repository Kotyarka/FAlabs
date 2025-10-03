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
    errorCodes resultCode;
    
    switch (flagChar) {
        case 'q': {
            if (argc != 6) {
                printf("Wrong value of arguments for -q. Expected: -q epsilon a b c\n");
                return WRONG_ARGUMENTS;
            }
            
            // Проверка корректности epsilon (вещественное число)
            if (!isValidDouble(argv[2])) {
                printf("Error: epsilon must be a valid number\n");
                return BAD_INPUT;
            }
            double eps = atof(argv[2]);
            if (eps <= 0) {
                printf("Error: epsilon must be positive\n");
                return BAD_INPUT;
            }
            
            // Проверка корректности коэффициентов (вещественные числа)
            for (int i = 3; i < 6; i++) {
                if (!isValidDouble(argv[i])) {
                    printf("Error: coefficient must be a valid number\n");
                    return BAD_INPUT;
                }
            }
            
            double a = atof(argv[3]);
            double b = atof(argv[4]);
            double c = atof(argv[5]);
            
            double coefficients[3] = {a, b, c};
            int permutationCount = 0;
            
            printf("All permutations and their solutions:\n");
            printf("=====================================\n");
            
            // Перебор всех уникальных перестановок коэффициентов
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (i != j && i != k && j != k) {
                            permutationCount++;
                            quadraticSolution solution;
                            
                            // Решаем уравнение для текущей перестановки
                            resultCode = equationSolving(eps, coefficients[i], coefficients[j], coefficients[k], &solution);
                            
                            if (resultCode == OK) {
                                // Вывод в формате "коэффициенты: корни"
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
                            }
                        }
                    }
                }
            }
            break;
        }
        case 'm': {
            if (argc != 4) {
                printf("Wrong value of arguments for -m. Expected: -m num1 num2\n");
                return WRONG_ARGUMENTS;
            }
            
            // Проверка корректности чисел (целые числа)
            if (!isValidInteger(argv[2]) || !isValidInteger(argv[3])) {
                printf("Error: numbers must be valid integers\n");
                return BAD_INPUT;
            }
            
            int num1, num2;
            errorCodes convertResult1 = convertStrToNum(argv[2], &num1);
            errorCodes convertResult2 = convertStrToNum(argv[3], &num2);
            
            if (convertResult1 != OK || convertResult2 != OK) {
                printf("Error occurred: invalid number format\n");
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
            
            // Проверка корректности epsilon (вещественное число)
            if (!isValidDouble(argv[2])) {
                printf("Error: epsilon must be a valid number\n");
                return BAD_INPUT;
            }
            double eps = atof(argv[2]);
            if (eps <= 0) {
                printf("Error: epsilon must be positive\n");
                return BAD_INPUT;
            }
            
            // Проверка корректности сторон (вещественные числа)
            for (int i = 3; i < 6; i++) {
                if (!isValidDouble(argv[i])) {
                    printf("Error: side length must be a valid number\n");
                    return BAD_INPUT;
                }
            }
            
            float a = atof(argv[3]);
            float b = atof(argv[4]);
            float c = atof(argv[5]);
            
            // Проверка на положительность сторон
            if (a <= 0 || b <= 0 || c <= 0) {
                printf("Error: all sides must be positive numbers\n");
                return BAD_INPUT;
            }
            
            // Проверка существования треугольника
            if (!canFormTriangle(a, b, c)) {
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
        printf("Error occurred: %d\n", resultCode);
        return resultCode;
    }
    
    return OK;
}