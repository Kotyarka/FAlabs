#include "../include/numbers.h"

int main() {
    int base = 0;
    char str[1024];
    long maxDecimal = 0;
    long num = 0;
    int isMinus = 1;
    errorCodes result;

    printf("Enter the base of the numeric system: ");
    if (scanf("%s", str) != 1) {
        printf("Input error\n");
        return BAD_INPUT;
    }
    
    result = baseParsing(str, &base);
    if (result != OK) {
        switch (result) {
            case WRONG_ARGUMENTS:
                printf("Wrong symbols in base\n");
                break;
            case INVALID_BASE:
                printf("Wrong base, try 2-36\n");
                break;
            case OVERFLOW_ERROR:
                printf("Too big base\n");
                break;
            default:
                printf("Unknown error\n");
        }
        return result;
    }

    printf("Base %d selected\n", base);
    printf("Enter your numbers, 'Stop' to end:\n");

    int firstNumber = 1;

    while (1) {
        if (scanf("%s", str) != 1) {
            printf("Input error\n");
            return BAD_INPUT;
        }
        
        if (strcmp(str, "Stop") == 0) {
            break;
        }
        
        result = numChecker(str, &base, &isMinus);
        if (result != OK) {
            switch (result) {
                case INVALID_DIGIT:
                    printf("Digit too large for base %d: %s\n", base, str);
                    break;
                case WRONG_ARGUMENTS:
                    printf("Wrong symbols in number: %s\n", str);
                    break;
                default:
                    printf("Unknown error in number: %s\n", str);
            }
            return result;
        }

        num = 0;
        result = toDecInt(str, base, &num);
        if (result != OK) {
            printf("Conversion error for: %s\n", str);
            return result;
        }

        if (firstNumber || labs(num) > labs(maxDecimal)) {
            maxDecimal = num;
            firstNumber = 0;
        }
        
        printf("Number: %s (base %d) = %ld (decimal)\n", str, base, num);
    }

    if (firstNumber) {
        printf("No numbers entered\n");
        return OK;
    }

    char maxInOriginalBase[BUFSIZ];
    result = toNsystem(maxInOriginalBase, base, &maxDecimal);
    if (result != OK) {
        printf("Error converting back to base %d\n", base);
        return result;
    }

    printf("\nMax absolute number: %s (base %d)\n", maxInOriginalBase, base);
    printf("Decimal value: %ld\n", maxDecimal);
    

    printf("In other bases:\n");
    for (int i = 9; i <= 36; i += 9) {
        char maxS[BUFSIZ];
        result = toNsystem(maxS, i, &maxDecimal);
        if (result != OK) {
            printf("Conversion error for base %d\n", i);
            continue;
        }
        printf("%d-base: %s\n", i, maxS);
    }

    return OK;
}