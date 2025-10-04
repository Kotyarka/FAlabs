#include "../include/flags.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Wrong number of arguments");
        printf("usage: %s <flag> <input_file> [output_file]\n", argv[0]);
        return WRONG_ARGUMENTS;
    }

    char* flag = argv[1];
    char* inputFile = argv[2];
    char* outputName = NULL;
    char outputBuffer[1024];

    if ((flag[1] == 'n' || (flag[0] == '/' && flag[1] == 'n')) && strlen(flag) == 3) {
        if (argc != 4) {
            printf("Wrong number of arguments\n", flag);
            return WRONG_ARGUMENTS;
        }
        outputName = argv[3];
    } else {
        snprintf(outputBuffer, sizeof(outputBuffer), "out_%s", inputFile);
        outputName = outputBuffer;
    }

    errorCodes flagCheck = isFlagValid(flag);
    if (flagCheck != OK) {
        printf("Invalid flag", flag);
        return flagCheck;
    }
    
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Cannot open input file\n", inputFile);
        return OPENING_FILE_ERROR;
    }

    FILE* output = fopen(outputName, "w");
    if (output == NULL) {
        printf("Cannot open output file\n", outputName);
        fclose(input);
        return OPENING_FILE_ERROR;
    }

    char flagChar = flag[strlen(flag)-1];
    errorCodes resultCode = OK;
    
    switch (flagChar) {
        case 'd':
            resultCode = d(input, output);
            break;
        case 'i':
            resultCode = i(input, output);
            break;
        case 's':
            resultCode = s(input, output);
            break;
        case 'a':
            resultCode = a(input, output);
            break;
        default:
            resultCode = BAD_INPUT;
            break;
    }

    fclose(input);
    fclose(output);
    
    if (resultCode != OK) {
        printf("Doings failed with code %d\n", resultCode);
        switch (resultCode) {
            case BAD_INPUT:
                printf("Invalid input data\n");
                break;
            case OVERFLOW_ERROR:
                printf("Overflow occurred\n");
                break;
            case MALLOC_ERROR:
                printf("Memory allocation failed!!\n");
                break;
            case POINTER_ERROR:
                printf("NULL pointer encountered\n");
                break;
            default:
                printf("Unknown error occurred\n");
        }
        return resultCode;
    }
    return OK;
}