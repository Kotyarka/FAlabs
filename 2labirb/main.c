#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "primenumbers.h"

int main() {
    int T;
    if (scanf("%d", &T) != 1 || T < 1) {
        printf("error occured: %d\n", BAD_INPUT);
        return BAD_INPUT;
    }

    int* inputMas = (int*)malloc(T * sizeof(int));
    if (inputMas == NULL) {
        printf("error occured: %d\n", MEMORY_ALLOCATION_ERROR);
        return MEMORY_ALLOCATION_ERROR;
    }
    
    for (int i = 0; i < T; i++) {
        if (scanf("%d", &inputMas[i]) != 1) {
            free(inputMas);
            printf("error occured: %d\n", BAD_INPUT);
            return BAD_INPUT;
        }
    }

    int max_number = inputMas[0];
    for (int i = 1; i < T; i++) {
        if (inputMas[i] > max_number) {
            max_number = inputMas[i];
        }
    }

    int primes_count;
    int* primes_array;

    enum return_code result = find_primes(max_number, &primes_array, &primes_count);

    if (result != OK) {
        free(inputMas);
        printf("error occured: %d\n", result);
        return result;
    }

    for (int i = 0; i < T; i++) {
        int index = inputMas[i];

        if (index <= 0) {
            free(inputMas);
            free(primes_array);
            printf("error occured: %d\n", WRONG_INDEX);
            return WRONG_INDEX;
        }

        if (index > primes_count) {
            free(inputMas);
            free(primes_array);
            printf("error occured: %d\n", WRONG_INDEX);
            return WRONG_INDEX;
        }
        
        printf("%d prime number: %d\n", index, primes_array[index - 1]);
    }
    
    free(inputMas);
    free(primes_array);

    return OK;
}