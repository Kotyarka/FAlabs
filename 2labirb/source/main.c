#include <stdio.h>
#include <stdlib.h>
#include "../include/primenumbers.h"

int main() {
    int T;
    if (scanf("%d", &T) != 1) {
        printf("Failed to read number\n");
        return BAD_INPUT;
    }
    
    if (T < 1) {
        printf("Number must be positive\n");
        return BAD_INPUT;
    }

    int* inputMas = (int*)malloc(T * sizeof(int));
    if (inputMas == NULL) {
        printf("Memory allocation failed for input array\n");
        return MALLOC_ERROR;
    }
    
    for (int i = 0; i < T; i++) {
        if (scanf("%d", &inputMas[i]) != 1) {
            printf("Failed to read index number at position %d\n", i + 1);
            free(inputMas);
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

    errorCodes result = findPrimes(max_number, &primes_array, &primes_count);

    if (result != OK) {
        free(inputMas);
        switch (result) {
            case MALLOC_ERROR:
                printf("Memory allocation failed while generating primes array\n");
                break;
            case OVERFLOW_ERROR:
                printf("Overflow error");
                break;
            case BAD_INPUT:
                printf("Invalid input parameter \n");
                break;
            default:
                printf("Unknown error occurred while generating primes\n");
        }
        return result;
    }

    for (int i = 0; i < T; i++) {
        int index = inputMas[i];

        if (index <= 0) {
            printf("Prime index must be positive");
            free(inputMas);
            free(primes_array);
            return INDEX_ERROR;
        }
        printf("%d. The %d prime number is: %d\n", i + 1, index, primes_array[index - 1]);
    }
    
    free(inputMas);
    free(primes_array);
    return OK;
}