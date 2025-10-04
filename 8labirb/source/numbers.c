#include "../include/numbers.h"


errorCodes baseParsing(char* str, int* base) {
    char* p;
    long result = strtol(str, &p, 10);

    if (*p != '\0') { 
        return WRONG_ARGUMENTS;
    }
    if (result == LONG_MAX || result == LONG_MIN) {
        return OVERFLOW_ERROR;
    }
    *base = (int)result;
    if (*base < 2 || *base > 36) {
        return INVALID_BASE;
    }
    return OK;
}

errorCodes numChecker(char* str, const int* base, int* isMinus) {
    char* p = str;
    int num = 0;
    *isMinus = 1;
    
    if (str[0] == '-') {
        *isMinus = -1;
        ++p;
    }
    if (str[0] == '+') {
        ++p;
    }

    if (*p == '\0') {
        return WRONG_ARGUMENTS;
    }

    while (*p) {
        if (isdigit(*p)) {
            num = *p - '0';
        } else if (isalpha(*p)) {
            num = toupper(*p) - 'A' + 10; 
        } else {
            return WRONG_ARGUMENTS;
        }
        
        if (num >= *base) {
            return INVALID_DIGIT;
        }
        ++p;
    }
    return OK;
}

errorCodes toDecInt(char* str, const int base, long* num) {
    char* ptr = str;
    int isMinus = 1;
    long result = 0;
    
    if (str[0] == '-') {
        isMinus = -1;
        ++ptr;
    }
    if (str[0] == '+') {
        ++ptr;
    }

    while (*ptr) {
        int digit;
        if (isdigit(*ptr)) {
            digit = *ptr - '0';
        } else if (isalpha(*ptr)) {
            digit = toupper(*ptr) - 'A' + 10;
        } else {
            return WRONG_ARGUMENTS;
        }
        
        if (digit >= base) {
            return INVALID_DIGIT;
        }
        
        if (result > (LONG_MAX - digit) / base) {
            return OVERFLOW_ERROR;
        }
        
        result = result * base + digit;
        ++ptr;
    }
    
    *num = result * isMinus;
    return OK;
}

errorCodes toNsystem(char* str, const int base, long* num) {
    int digit = 0;
    int start = 0;
    
    if (*num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return OK;
    }

    int isNegative = (*num < 0);
    unsigned long tempNum = isNegative ? -(*num) : *num;
    
    if (isNegative) {
        str[0] = '-';
        start = 1;
    }

    int len = start;
    
    while (tempNum) {
        if (len >= BUFSIZ - 1) {
            return OVERFLOW_ERROR;
        }
        
        digit = tempNum % base;
        if (digit > 9) {
            str[len] = digit - 10 + 'A';
        } else {
            str[len] = digit + '0';
        }
        len++;
        tempNum /= base;
    }
    str[len] = '\0';

    for (int i = start, j = len - 1; i < j; i++, j--) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    
    return OK;
}