#include "../include/numbers.h"

errorCodes baseParsing(char* str, int* base) {
    if (str == NULL || base == NULL) {
        return POINTER_ERROR;
    }

    char* p;
    errno = 0;
    long result = strtol(str, &p, 10);

    if (*p != '\0') {
        return WRONG_ARGUMENTS;
    }
    if (errno == ERANGE || result == LONG_MAX || result == LONG_MIN) {
        return OVERFLOW_ERROR;
    }
    *base = (int)result;
    if (*base < 2 || *base > 36) {
        return INVALID_BASE;
    }
    return OK;
}

errorCodes numChecker(char* str, const int* base, int* isMinus) {
    if (str == NULL || base == NULL || isMinus == NULL) {
        return POINTER_ERROR;
    }

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
        return EMPTY_INPUT;
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
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }

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
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }

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

errorCodes removeLeadingZeros(char* str) {
    if (str == NULL) {
        return POINTER_ERROR;
    }

    char* src = str;
    char* dst = str;
    int isNegative = 0;

    if (*src == '-') {
        isNegative = 1;
        *dst++ = *src++;
    } else if (*src == '+') {
        src++;
    }

    while (*src == '0') {
        src++;
    }

    if (*src == '\0' && src > str) {
        if (isNegative) {
            str[0] = '-';
            str[1] = '0';
            str[2] = '\0';
        } else {
            str[0] = '0';
            str[1] = '\0';
        }
        return OK;
    }

    if (isNegative) {
        dst = str + 1;
    }
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';

    return OK;
}

errorCodes findMinBase(char* numberStr, int* minBase) {
    if (numberStr == NULL || minBase == NULL) {
        return POINTER_ERROR;
    }

    char temp[1024];
    strcpy(temp, numberStr);

    char* digits = temp;
    if (*digits == '-' || *digits == '+') {
        digits++;
    }

    if (strcmp(digits, "0") == 0) {
        *minBase = 2;
        return OK;
    }

    int maxDigit = 0;
    int hasValidDigits = 0;

    for (char* p = digits; *p; p++) {
        int digit;
        if (isdigit(*p)) {
            digit = *p - '0';
            hasValidDigits = 1;
        } else if (isalpha(*p)) {
            digit = toupper(*p) - 'A' + 10;
            hasValidDigits = 1;
        } else {
            return INVALID_NUMBER;
        }

        if (digit > maxDigit) {
            maxDigit = digit;
        }
    }

    if (!hasValidDigits) {
        return INVALID_NUMBER;
    }

    *minBase = (maxDigit + 1 > 2) ? maxDigit + 1 : 2;

    int isMinus;
    errorCodes result = numChecker(numberStr, minBase, &isMinus);

    if (result == OK) {
        return OK;
    } else {
        for (int base = *minBase + 1; base <= 36; base++) {
            result = numChecker(numberStr, &base, &isMinus);
            if (result == OK) {
                *minBase = base;
                return OK;
            }
        }
    }

    return INVALID_NUMBER;
}