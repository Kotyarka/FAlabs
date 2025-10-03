#include "../include/flags.h"

errorCodes isFlagValid(const char* flag) {
    if (!(flag[0] == '-' || flag[0] == '/') || strlen(flag) < 2) {
        return BAD_INPUT;
    }

    int notNPlace = 1;
    if (flag[1] == 'n') {
        notNPlace = 2;
        if (strlen(flag) != 3) {
            return BAD_INPUT;
        }
    } else if (strlen(flag) != 2) {
        return BAD_INPUT;
    }

    switch (flag[notNPlace]) {
        case 'd':
        case 'i':
        case 's':
        case 'a':
            return OK;
        default:
        return BAD_INPUT;
    }
}

errorCodes d(FILE* input, FILE* output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, output);
        }
    }
    return OK;
    }

errorCodes i(FILE* input, FILE* output) {
    int ch;
    int count = 0;
    int newLine = 1; 
    
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
            newLine = 1;
        } else {
            if (isalpha(ch)) {
                count++;
            }
            newLine = 0;
        }
    }
    if (!newLine) {
        fprintf(output, "%d\n", count);
    }
    
    return OK;
}

errorCodes s(FILE* input, FILE* output) {
    int ch;
    int count = 0;
    int newLine = 1;
    
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') {
            fprintf(output, "%d\n", count);
            count = 0;
            newLine = 1;
        } else {
            if (!isalpha(ch) && !isdigit(ch) && !isspace(ch)) {
                count++;
            }
            newLine = 0;
        }
    }
    
    if (!newLine) {
        fprintf(output, "%d\n", count);
    }
    
    return OK;
}

errorCodes a(FILE* input, FILE* output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isdigit(ch)) {
            fputc(ch, output);
        } else {
            fprintf(output, "%02X", (unsigned char)ch);
        }
    }
    return OK;
}