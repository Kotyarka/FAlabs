#include "../include/numbers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: %s input_file output_file\n", argv[0]);
        return WRONG_ARGUMENTS;
    }
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    if (!input) {
        printf("Cannot open input file '%s'\n", argv[1]);
        return FILE_ERROR;
    }
    
    if (!output) {
        printf("Cannot open output file '%s'\n", argv[2]);
        fclose(input);
        return FILE_ERROR;
    }
    
    char numberStr[1024];
    int numbersProcessed = 0;
    int errorOccurred = 0;
    
    while (fscanf(input, "%1023s", numberStr) == 1) {
        numbersProcessed++;
        
        errorCodes result = removeLeadingZeros(numberStr);
        if (result != OK) {
            switch (result) {
                case POINTER_ERROR:
                    printf("NULL pointer passed to removeLeadingZeros\n");
                    break;
                default:
                    printf("Unknown error while removing leading zeros\n");
            }
            errorOccurred = 1;
            break;
        }
        
        int minBase;
        result = findMinBase(numberStr, &minBase);
        if (result != OK) {
            switch (result) {
                case POINTER_ERROR:
                    printf("NULL pointer passed to findMinBase\n");
                    break;
                case INVALID_NUMBER:
                    printf("Invalid number format\n");
                    break;
                default:
                    printf("Unknown error while finding base\n");
            }
            errorOccurred = 1;
            break;
        }
        
        long decimalValue = 0;
        result = toDecInt(numberStr, minBase, &decimalValue);
        
        if (result != OK) {
            switch (result) {
                case POINTER_ERROR:
                    printf("NULL pointer passed to toDecInt\n");
                    break;
                case WRONG_ARGUMENTS:
                    printf("Number '%s' contains invalid characters for base %d\n", numberStr, minBase);
                    break;
                case INVALID_DIGIT:
                    printf("Number '%s' contains digits that exceed base %d\n", numberStr, minBase);
                    break;
                case OVERFLOW_ERROR:
                    printf("Number '%s' causes overflow when converting from base %d to decimal\n", numberStr, minBase);
                    break;
                default:
                    printf("Unknown error\n");
            }
            errorOccurred = 1;
            break;
        }
        
        fprintf(output, "%s %d %ld\n", numberStr, minBase, decimalValue);
    }
    
    fclose(input);
    fclose(output);
    
    if (numbersProcessed == 0) {
        printf("No numbers found in input file\n");
        remove(argv[2]);
        return EMPTY_INPUT;
    }
    
    if (errorOccurred) {
        printf("Program terminated with errors after processing %d numbers\n", numbersProcessed);
        remove(argv[2]);
        return BAD_INPUT;
    } else {
        printf("Program completed successfully. Processed %d numbers\n", numbersProcessed);
        return OK;
    }
}