#include <stdio.h>
#include <stdlib.h>
#include "../include/functions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments! type only epsilon");
        return BAD_INPUT;
    }

    double a = 0.0; // по сути, это можно не обьявлять, но так код получается гибче или типо того
    double b = 1.0;
    char* typedEpsilon;
    double eps = strtod(argv[1], &typedEpsilon);

    if (*typedEpsilon != '\0') {
        printf("Type correct epsilon!");
        return BAD_INPUT;
    }

    double result;
    errorCodes status;

    status = trapezoidRule(aFunction, a, b, eps, &result);
    if (status != OK) {
        printf("Error calculating log(1 + x) / x: error code %d\n", status);
        return status;
    }
    printf("log(1 + x) / x: %f\n", result);
    
    status = trapezoidRule(bFunction, a, b, eps, &result);
    if (status != OK) {
        printf("Error calculating exp(-x * x * 0.5): error code %d\n", status);
        return status;
    }
    printf("exp(-x * x * 0.5): %f\n", result);
    
    status = trapezoidRule(cFunction, a, b, eps, &result);
    if (status != OK) {
        printf("Error calculating -log(1 - x): error code %d\n", status);
        return status;
    }
    printf("-log(1 - x): %f\n", result);
    
    status = trapezoidRule(dFunction, a, b, eps, &result);
    if (status != OK) {
        printf("Error calculating pow(x, x): error code %d\n", status);
        return status;
    }
    printf("pow(x, x): %f\n", result);

    return OK;
}