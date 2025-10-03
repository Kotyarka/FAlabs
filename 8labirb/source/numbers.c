#include "../include/numbers.h"

errorCodes isValidChar(char c, int base, int* isValid) {
    if (isValid == NULL) {
        return POINTER_ERROR;
    }
    
    if (c >= '0' && c <= '9') {
        *isValid = (c - '0') < base;
        return OK;
    }
    if (c >= 'A' && c <= 'Z') {
        *isValid = (c - 'A' + 10) < base;
        return OK;
    }
    *isValid = 0;
    return OK;
}

errorCodes charToValue(char c, int* value) {
    if (value == NULL) {
        return POINTER_ERROR;
    }
    
    if (c >= '0' && c <= '9') {
        *value = c - '0';
        return OK;
    }
    if (c >= 'A' && c <= 'Z') {
        *value = c - 'A' + 10;
        return OK;
    }
    *value = -1;
    return BAD_INPUT;
}

errorCodes convertFromBase(const char* str, int base, long long* result) {
    if (str == NULL || result == NULL) {
        return POINTER_ERROR;
    }
    
    if (strlen(str) == 0) {
        return BAD_INPUT;
    }
    
    int isNegative = 0;
    const char* ptr = str;
    
    while (*ptr == ' ') ptr++;
    
    if (*ptr == '-') {
        isNegative = 1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }
    
    while (*ptr == '0') ptr++;
    
    if (*ptr == '\0') {
        *result = 0;
        return OK;
    }
    
    long long value = 0;
    
    while (*ptr != '\0') {
        int valid;
        errorCodes validResult = isValidChar(*ptr, base, &valid);
        if (validResult != OK) {
            return validResult;
        }
        if (!valid) {
            return BAD_INPUT;
        }
        
        int digit;
        errorCodes valueResult = charToValue(*ptr, &digit);
        if (valueResult != OK) {
            return valueResult;
        }
        
        if (value > (LLONG_MAX - digit) / base) {
            return OVERFLOW_ERROR;
        }
        
        value = value * base + digit;
        ptr++;
    }
    
    *result = isNegative ? -value : value;
    return OK;
}

errorCodes convertToBase(long long num, int base, char* buffer, int bufferSize) {
    if (buffer == NULL || bufferSize <= 0) {
        return POINTER_ERROR;
    }
    
    if (num == 0) {
        if (bufferSize < 2) {
            return OVERFLOW_ERROR;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return OK;
    }
    
    int isNegative = 0;
    long long n = num;
    
    if (n < 0) {
        isNegative = 1;
        n = -n;
    }
    
    char temp[65];
    int index = 0;
    
    while (n > 0) {
        int digit = n % base;
        if (digit < 10) {
            temp[index++] = '0' + digit;
        } else {
            temp[index++] = 'A' + (digit - 10);
        }
        n /= base;
        
        if (index >= 64) {
            return OVERFLOW_ERROR;
        }
    }
    
    int requiredSize = index + (isNegative ? 1 : 0) + 1;
    if (requiredSize > bufferSize) {
        return OVERFLOW_ERROR;
    }
    
    int bufferIndex = 0;
    if (isNegative) {
        buffer[bufferIndex++] = '-';
    }
    
    for (int i = index - 1; i >= 0; i--) {
        buffer[bufferIndex++] = temp[i];
    }
    buffer[bufferIndex] = '\0';
    
    return OK;
}

errorCodes removeLeadingZeros(char* str) {
    if (str == NULL) {
        return POINTER_ERROR;
    }
    
    if (strlen(str) == 0) {
        return OK;
    }
    
    int isNegative = 0;
    char* ptr = str;
    
    if (*ptr == '-') {
        isNegative = 1;
        ptr++;
    }
    
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    if (*ptr == '\0') {
        ptr--;
    }
    
    if (ptr != str + (isNegative ? 1 : 0)) {
        if (isNegative) {
            memmove(str + 1, ptr, strlen(ptr) + 1);
        } else {
            memmove(str, ptr, strlen(ptr) + 1);
        }
    }
    
    return OK;
}

errorCodes readBase(int* base) {
    if (base == NULL) {
        return POINTER_ERROR;
    }
    
    printf("Введите основание системы счисления (2-36): ");
    if (scanf("%d", base) != 1) {
        printf("Ошибка: неверный ввод основания\n");
        return BAD_INPUT;
    }
    
    if (*base < 2 || *base > 36) {
        printf("Ошибка: основание должно быть в диапазоне [2, 36]\n");
        return BAD_INPUT;
    }
    
    return OK;
}

errorCodes processNumbers(int base, long long* maxAbsValue, char* maxOriginalStr, int maxStrSize) {
    if (maxAbsValue == NULL || maxOriginalStr == NULL || maxStrSize <= 0) {
        return POINTER_ERROR;
    }
    
    char inputBuffer[1024];
    *maxAbsValue = 0;
    maxOriginalStr[0] = '\0';
    
    printf("Введите числа (окончание ввода - 'Stop'):\n");
    
    while (1) {
        if (scanf("%1023s", inputBuffer) != 1) {
            printf("Ошибка при чтении ввода\n");
            return BAD_INPUT;
        }
        
        if (strcmp(inputBuffer, "Stop") == 0) {
            break;
        }
        
        if (strlen(inputBuffer) == 0) {
            continue;
        }
        
        long long currentValue;
        errorCodes result = convertFromBase(inputBuffer, base, &currentValue);
        
        if (result != OK) {
            printf("Ошибка преобразования числа '%s': ", inputBuffer);
            switch (result) {
                case BAD_INPUT:
                    printf("неверный формат числа\n");
                    break;
                case OVERFLOW_ERROR:
                    printf("переполнение\n");
                    break;
                default:
                    printf("неизвестная ошибка\n");
                    break;
            }
            return BAD_INPUT;
        }
        
        long long absValue = currentValue < 0 ? -currentValue : currentValue;
        long long currentMaxAbs = *maxAbsValue < 0 ? -(*maxAbsValue) : *maxAbsValue;
        
        if (maxOriginalStr[0] == '\0' || absValue > currentMaxAbs) {
            *maxAbsValue = currentValue;
            
            // Fix: Cast strlen to int for comparison
            if ((int)strlen(inputBuffer) < maxStrSize) {
                strcpy(maxOriginalStr, inputBuffer);
            } else {
                return OVERFLOW_ERROR;
            }
        }
    }
    
    return OK;
}

errorCodes printResults(long long maxAbsValue, const char* maxOriginalStr) {
    if (maxOriginalStr == NULL) {
        return POINTER_ERROR;
    }
    
    if (strlen(maxOriginalStr) == 0) {
        printf("Не было введено ни одного числа\n");
        return BAD_INPUT;
    }
    
    char cleanedStr[1024];
    strcpy(cleanedStr, maxOriginalStr);
    errorCodes removeResult = removeLeadingZeros(cleanedStr);
    if (removeResult != OK) {
        return removeResult;
    }
    
    printf("\nМаксимальное по модулю число: %s\n", cleanedStr);
    printf("В десятичной системе: %lld\n", maxAbsValue);
    
    int targetBases[] = {9, 18, 27, 36};
    char converted[65];
    
    for (int i = 0; i < 4; i++) {
        errorCodes convResult = convertToBase(maxAbsValue, targetBases[i], converted, sizeof(converted));
        if (convResult == OK) {
            printf("В системе с основанием %d: %s\n", targetBases[i], converted);
        } else {
            printf("Ошибка преобразования в систему с основанием %d\n", targetBases[i]);
            return convResult;
        }
    }
    
    return OK;
}

