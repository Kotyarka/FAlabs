#include "../include/numbers.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong value of arguments. Usage: %s <input_file> <output_file>\n", argv[0]);
        return WRONG_ARGUMENTS;
    }

    char* inputFile = argv[1];
    char* outputFile = argv[2];
    
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Occured error while opening input file\n");
        return OPENING_FILE_ERROR;
    }

    FILE* output = fopen(outputFile, "w");
    if (output == NULL) {
        printf("Occured error while opening output file\n");
        fclose(input);
        return OPENING_FILE_ERROR;
    }

    errorCodes resultCode = process_numbers(input, output);

    fclose(input);
    fclose(output);
    
    if (resultCode != OK) {
        printf("Error occured when processing numbers: %d\n", resultCode);
        return resultCode;
    }

    return OK;
}