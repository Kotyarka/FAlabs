#include "./flags/flags.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong value of arguments\n");
        return WRONG_ARGUMENTS;
    }

    char* flag = argv[1];
    char* numStr = argv[2];
    
    int flagCheck = isFlagValid(flag);
    if (flagCheck != OK) { 
        printf("Error occurred: %d\n", flagCheck);
        return flagCheck;
    }
    
    int num;
    int converResult = convertStrToNum(numStr, &num);
    if (converResult != OK) {
        printf("Error occurred: %d\n", converResult);
        return converResult;
    }
    
    char flagChar = flag[1];
    int resultCode;
    
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
            }
            break;
        }
        case 's': {
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
            }
            break;
        }
        case 'e': {
            long** listOfNums;
            resultCode = e(num, &listOfNums);
            if (resultCode == OK) {
                printf("Powers 1-%d for numbers 1-10:\n", num);
                for (int i = 0; i < 10; i++) {
                    printf("%d: ", i + 1);
                    for (int j = 0; j < num; j++) {
                        printf("%ld ", listOfNums[i][j]);
                    }
                    printf("\n");
                    free(listOfNums[i]);
                }
                free(listOfNums);
            }
            break;
        }
        case 'f': {
            long fact;
            resultCode = f(num, &fact);
            if (resultCode == OK) {
                printf("%d! = %ld\n", num, fact);
            }
            break;
        }
        case 'a': {
            int sum;
            resultCode = a(num, &sum);
            if (resultCode == OK) {
                printf("Sum of numbers from 1 to %d = %d\n", num, sum);
            }
            break;
        }
    }
    
    if (resultCode != OK) {
        printf("Error occurred: %d\n", resultCode);
        return resultCode;
    }
    
    return OK;
}