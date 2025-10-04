#include "../include/flags.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments.\n");
        return WRONG_ARGUMENTS;
    }

    char* flag = argv[1];
    char* numStr = argv[2];
    
    errorCodes flagCheck = isFlagValid(flag);
    if (flagCheck != OK) { 
        printf("Invalid flag");

        return flagCheck;
    }
    
    int num;
    errorCodes converResult = convertStrToNum(numStr, &num);
    if (converResult != OK) {
        switch (converResult) {
            case POINTER_ERROR:
                printf("NULL pointer error\n");
                break;
            case BAD_INPUT:
                printf("Invalid number \n");
                break;
            case OVERFLOW_ERROR:
                printf("Overflow error\n");
                break;
            default:
                printf("unknown error\n");
        }
        return converResult;
    }
    
    char flagChar = flag[1];
    errorCodes resultCode = OK;
    
    switch (flagChar) {
        case 'h': {
            int rangeList[100];
            int count;
            resultCode = h(num, rangeList, &count);
            if (resultCode == OK) {
                if (count == 0) {
                    printf("No multiples of %d found in range 1-100\n", num);
                } else {
                    printf("Multiples of %d in range 1-100: ", num);
                    for (int i = 0; i < count; i++) {
                        printf("%d ", rangeList[i]);
                    }
                    printf("\n");
                }
            } else {
                if (resultCode == BAD_INPUT) {
                    printf("Input number cannot be zero\n");
                }
            }
            break;
        }
        case 'p': {
            int isPrime;
            resultCode = p(num, &isPrime);
            if (resultCode == OK) {
                if (isPrime == 2) {
                    printf("%d is neither prime nor composite\n", num);
                } else if (isPrime == 1) {
                    printf("%d is prime\n", num);
                } else {
                    printf("%d is composite\n", num);
                }
            } else {
                if (resultCode == BAD_INPUT) {
                    printf("Number must be positive\n");
                }
            }
            break;
        }
        case 's': {
            printf("Converting %d to hexadecimal...\n", num);
            char hexRepr[32];
            int length;
            resultCode = s(num, hexRepr, &length);
            if (resultCode == OK) {
                if (num == 0) {
                    printf("Hexadecimal representation of 0: 0\n");
                } else {
                    printf("Hexadecimal representation of %d: ", num);
                    for (int j = length - 1; j >= 0; j--) {
                        printf("%c", hexRepr[j]);
                        if (j > 0) {
                            printf(" "); 
                        }
                    }
                    printf("\n");
                }
            } else {
                printf("Failed to convert %d to hexadecimal\n", num);
            }
            break;
        }
        case 'e': {
            long** listOfNums;
            resultCode = e(num, &listOfNums);
            if (resultCode == OK) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < num; j++) {
                        printf("%10ld ", listOfNums[i][j]);
                    }
                    printf("\n");
                    free(listOfNums[i]);
                }
                free(listOfNums);
            } else {
                if (resultCode == BAD_INPUT) {
                    printf("Exponent must be between 1 and 10\n");
                } else if (resultCode == MALLOC_ERROR) {
                    printf("Memory allocation failed\n");
                }
            }
            break;
        }
        case 'f': {
            long fact;
            resultCode = f(num, &fact);
            if (resultCode == OK) {
                printf("%d! = %ld\n", num, fact);
            } else {
                if (resultCode == BAD_INPUT) {
                    printf("Factorial is only defined for positive numbers\n");
                } else if (resultCode == OVERFLOW_ERROR) {
                    printf("Overflow erorr");
                }
            }
            break;
        }
        case 'a': {
            int sum;
            resultCode = a(num, &sum);
            if (resultCode == OK) {
                printf("Sum of numbers from 1 to %d = %d\n", num, sum);
            } else {
                if (resultCode == BAD_INPUT) {
                    printf("Sum is only defined for positive numbers");
                } else if (resultCode == OVERFLOW_ERROR) {
                    printf("Oveflow error\n");
                }
            }
            break;
        }
    }
    
    if (resultCode != OK) {
        return resultCode;
    }
    return OK;
}