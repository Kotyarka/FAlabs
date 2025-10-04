#include "../include/numbers.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong value of arguments. Expected: ./program epsilon\n");
        return WRONG_ARGUMENTS;
    }
    
    double eps;
    errorCodes validationResult = transferToDouble(argv[1], &eps);

    if (validationResult != OK) {
        printf("Error occurred: %d\n", validationResult);
        return validationResult;
    }

    if (eps <= 0) {
        printf("Error: epsilon must be positive\n");
        return BAD_INPUT;
    }

    double results[15];
    getResults(eps, results);

    char* constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    
    printf("Calculation using limits\n");
    for (int i = 0; i < 5; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 
        printf("%s = %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");

    printf("Calculation using rows\n");
    for (int i = 5; i < 10; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 
        printf("%s = %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");
    
    printf("Calculation using equations\n");
    for (int i = 10; i < 15; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 
        printf("%s = %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");
    
    return OK;
}