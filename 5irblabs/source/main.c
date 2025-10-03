#include "../include/flags.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Wrong calue of arguments\n");
        return WRONG_ARGUMENTS;
    }

    char* flag = argv[1];
    char* inputFile = argv[2];
    char* outputName = NULL;
    char outputBuffer[1024];

    if (flag[1] == 'n' && strlen(flag) == 3) {
        if (argc != 4) {
            printf("there is no output file name!");
            return WRONG_ARGUMENTS;
        }
        outputName = argv[3];
    } else {
        snprintf(outputBuffer, sizeof(outputBuffer), "out_%s", inputFile);
        outputName = outputBuffer;
    }

    
    errorCodes flagCheck = isFlagValid(flag);
    if (flagCheck != OK) {
        printf("Error occured: %d\n", flagCheck);
        return flagCheck;
    }
    
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Occured error while openning file");
        return OPENING_FILE_ERROR;
    }

    FILE* output = fopen(outputName, "w");
    if (output == NULL) {
        printf("Occured error while openning file");
        return OPENING_FILE_ERROR;
    }

    char flagChar = flag[strlen(flag)-1];
    int resultCode = OK;

    switch (flagChar) {
        case 'd':
            resultCode = d(input,output);
            break;
        case 'i':
            resultCode = i(input,output);
            break;
        case 's':
            resultCode = s(input,output);
            break;
        case 'a':
            resultCode = a(input,output);
            break;
        default:
            resultCode = BAD_INPUT;
            break;
    }

    fclose(input);
    fclose(output);
    if (resultCode != OK) {
        printf("Error occured when do something with files: %d\n", resultCode);
        return resultCode;
    }

    return OK;
}