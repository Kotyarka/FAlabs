#include "flags.h"

errorCodes convertStrToNum(const char* str, int* num) {
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }

    char* end_ptr = NULL;

    long tmp = strtol(str, &end_ptr, 10);
    if (*end_ptr != '\0') {
        return BAD_INPUT;
    }
    if (tmp > INT_MAX || tmp < INT_MIN) {
        return OVERFLOW_ERROR;
    }

    *num = (int)tmp;

    return OK;
}

errorCodes isFlagValid(const char* flag) {
    if (!(flag[0] == '-' || flag[0] == '/') || strlen(flag) != 2) {
        return BAD_INPUT;
    }
    switch (flag[1]) {
        case 'h':
        case 'p':
        case 's':
        case 'e':
        case 'a':
        case 'f':
            return OK;
        default:
            return BAD_INPUT;
    }
}

errorCodes h(int num, int* list, int* count) { // натуральные числа в пределах 100 включительно, кратные x
    if (list == NULL || count == NULL) {
        return POINTER_ERROR;
    }
    if (num == 0) {
        return BAD_INPUT;
    }
    int i = 1;
    *count = 0;
    num = abs(num);

    while (num * i <= 100) {
        list[*count] = num * i;
        *count = *count + 1;
        ++i;
    }
    return OK;
}

errorCodes p(const int x, int* isPrime) { // является ли число x простым; является ли x составным; 
    if (isPrime == NULL) {
        return POINTER_ERROR;
    }
    if (x <= 0) {
        return BAD_INPUT;
    }
    *isPrime = 1;
    if (x == 1) {
        *isPrime = 2;
        return OK;
    }

    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            *isPrime = 0;
            break;
        }
    }
    return OK;
}

errorCodes s(int x, char* hexRepr, int* ind) { // в 16 отдельно разделяя пробелом от старших к младшим в строковом
    if (hexRepr == NULL || ind == NULL) {
        return POINTER_ERROR;
    }
    
    *ind = 0;
    int isNegative = 0;
    
    if (x < 0) {
        isNegative = 1;
        x = -x; 
    }
    
    if (x == 0) {
        hexRepr[0] = '0';
        *ind = 1;
        return OK;
    }

    while (x > 0) {
        int digit = x % 16;
        if (digit < 10) {
            hexRepr[*ind] = '0' + digit;
        } else {
            hexRepr[*ind] = 'A' + (digit - 10);
        }
        ++(*ind);
        x /= 16;
    }
        
    if (isNegative) {
        hexRepr[*ind] = '-';
        ++(*ind);
    }
    
    return OK;
}

errorCodes e(int x, long*** list) { // таблица степеней до х до 10 основания
    if (x > 10 || x <= 0) {
        return BAD_INPUT;
    }
    *list = (long**)malloc(10 * sizeof(long*));
    if (*list == NULL) {
        return MALLOC_ERROR;
    }

    for (int i = 0; i < 10; ++i) {
        (*list)[i] = (long*)malloc(x * sizeof(long));
        if ((*list)[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free((*list)[j]);
            }
            free(*list);
            *list = NULL;
            return MALLOC_ERROR;
        }
    }
    for (int i = 1; i <= 10; ++i) {
        long res = i;
        for (int j = 1; j <= x; ++j) {
            (*list)[i - 1][j - 1] = res;
            res *= i;
        }
    }
    return OK;
}

errorCodes f(const int x, long* fact) { // факториал
    if (fact == NULL) {
        return POINTER_ERROR;
    }
    if (x < 0) {
        return BAD_INPUT;
    }
    *fact = 1;
    if (x == 0 || x == 1) {
        return OK;
    }
    for (int i = 2; i <= x; ++i) {
        if (*fact > LLONG_MAX / i) {
            return OVERFLOW_ERROR;
        }
        *fact *= i;
    }
    return OK;
}

errorCodes a(const int x, int* result) { //  сумма от 1 до х
    if (x <= 0) {
        return BAD_INPUT;
    }
    if (result == NULL) {
        return POINTER_ERROR;
    }

    *result = 0;
    for (int i = 1; i <= x; ++i) {
        if (*result > INT_MAX - i) {
            return OVERFLOW_ERROR;
        }
        *result += i;
    }
    return OK;
}