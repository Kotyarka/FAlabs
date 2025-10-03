#include "../include/numbers.h"

#define MAX_NUMBER_LENGTH 1000

errorCodes process_numbers(FILE* input, FILE* output) {
    if (input == NULL || output == NULL) {
        return POINTER_ERROR;
    }

    char* token = NULL;
    errorCodes result_code = OK;
    
    while (result_code == OK && (result_code = read_next_token(input, &token)) == OK && token != NULL) {
        char* cleaned_number = NULL;
        errorCodes clean_result = remove_leading_zeros(token, &cleaned_number);
        
        if (clean_result != OK) {
            free(token);
            return clean_result;
        }
        
        int min_base;
        errorCodes base_result = find_min_base(cleaned_number, &min_base);
        
        if (base_result == OK) {
            long long decimal_value;
            errorCodes convert_result = convert_to_decimal(cleaned_number, min_base, &decimal_value);
            
            if (convert_result == OK) {
                fprintf(output, "%s %d %lld\n", cleaned_number, min_base, decimal_value);
            } else if (convert_result == OVERFLOW_ERROR) {
                fprintf(output, "%s %d overflow\n", cleaned_number, min_base);
                result_code = OK; 
            } else {
                result_code = convert_result;
            }
        } else {
            fprintf(stderr, "Error: number '%s' cannot be represented in base 2-36\n", cleaned_number);
            result_code = OK;
        }
        
        free(cleaned_number);
        free(token);
        token = NULL;
    }
    
    if (result_code == OK && token == NULL) {
        return OK;
    }
    
    if (token != NULL) {
        free(token);
    }
    
    return result_code;
}

errorCodes read_next_token(FILE* file, char** result) {
    if (file == NULL || result == NULL) {
        return POINTER_ERROR;
    }

    char* buffer = malloc(MAX_NUMBER_LENGTH);
    if (buffer == NULL) {
        return MALLOC_ERROR;
    }
    
    int c;
    int index = 0;
    while ((c = fgetc(file)) != EOF && isspace(c));
    
    if (c == EOF) {
        free(buffer);
        *result = NULL;
        return OK; 
    }
    
    buffer[index++] = c;
    while ((c = fgetc(file)) != EOF && !isspace(c) && index < MAX_NUMBER_LENGTH - 1) {
        buffer[index++] = c;
    }
    buffer[index] = '\0';
    
    // Если мы прочитали разделитель, возвращаем его в поток
    if (c != EOF && isspace(c)) {
        ungetc(c, file);
    }
    
    *result = buffer;
    return OK;
}

errorCodes find_min_base(const char* number, int* result_base) {
    if (number == NULL || result_base == NULL) {
        return POINTER_ERROR;
    }

    if (strlen(number) == 0) {
        return BAD_INPUT;
    }

    int min_base = 2;
    
    for (int i = 0; number[i] != '\0'; i++) {
        char c = number[i];
        int digit_value;
        
        if (isdigit(c)) {
            digit_value = c - '0';
        } else if (isalpha(c)) {
            digit_value = tolower(c) - 'a' + 10;
        } else {
            return INVALID_NUMBER_ERROR;
        }
        
        if (digit_value + 1 > min_base) {
            min_base = digit_value + 1;
        }
        
        if (min_base > 36) {
            return INVALID_NUMBER_ERROR;
        }
    }
    
    *result_base = min_base;
    return OK;
}

errorCodes convert_to_decimal(const char* number, int base, long long* result) {
    if (number == NULL || result == NULL) {
        return POINTER_ERROR;
    }

    if (base < 2 || base > 36) {
        return BAD_INPUT;
    }

    long long res = 0;
    
    for (int i = 0; number[i] != '\0'; i++) {
        char c = number[i];
        int digit_value;
        
        if (isdigit(c)) {
            digit_value = c - '0';
        } else {
            digit_value = tolower(c) - 'a' + 10;
        }

        // Проверка что цифра допустима для данного основания
        if (digit_value >= base) {
            return INVALID_NUMBER_ERROR;
        }
        
        // Проверка на переполнение
        if (res > (LLONG_MAX - digit_value) / base) {
            *result = LLONG_MAX;
            return OVERFLOW_ERROR;
        }
        
        res = res * base + digit_value;
    }
    
    *result = res;
    return OK;
}

errorCodes remove_leading_zeros(const char* number, char** result) {
    if (number == NULL || result == NULL) {
        return POINTER_ERROR;
    }

    const char* ptr = number;
    
    // Пропускаем ведущие нули, но оставляем один ноль если число состоит только из нулей
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    char* res = malloc(strlen(ptr) + 1);
    if (res == NULL) {
        return MALLOC_ERROR;
    }
    
    strcpy(res, ptr);
    *result = res;
    return OK;
}