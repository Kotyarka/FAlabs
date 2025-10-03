#include "flags.h"

// Функция для проверки, является ли строка целым числом (посимвольно)
int isValidInteger(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    int i = 0;
    
    // Пропускаем пробелы в начале
    while (str[i] == ' ') {
        i++;
    }
    
    // Проверяем знак
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    
    // После знака должна быть хотя бы одна цифра
    if (str[i] == '\0') {
        return 0;
    }
    
    // Проверяем все символы на цифры
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    
    return 1;
}

int isValidDouble(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    int i = 0;
    int has_digit = 0;
    int has_dot = 0;
    
    while (str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            has_digit = 1; 
        }
        else if (str[i] == '.') {
            if (has_dot) {
                return 0; 
            }
            has_dot = 1;
        }
        else if (str[i] == ' ') {
            // Пропускаем пробелы в конце
            while (str[i] == ' ') {
                i++;
            }
            if (str[i] != '\0') {
                return 0;  // Пробелы в середине числа
            }
            break;
        }
        else {
            return 0;  // Недопустимый символ
        }
    }
    
    return has_digit;
}

int canFormTriangle(float a, float b, float c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

errorCodes convertStrToNum(const char* str, int* num) {
    if (str == NULL || num == NULL) {
        return POINTER_ERROR;
    }
    
    if (!isValidInteger(str)) {
        return BAD_INPUT;
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
        case 'q':
        case 'm':
        case 't':
            return OK;
        default:
            return BAD_INPUT;
    }
}

errorCodes q(double eps, double a, double b, double c, quadraticSolution* answer) {
    if (answer == NULL) {
        return POINTER_ERROR;
    }
    
    return equationSolving(eps, a, b, c, answer);
}

errorCodes equationSolving(double eps, double a, double b, double c, quadraticSolution* answer) {
    if (answer == NULL) {
        return POINTER_ERROR;
    }
    
    if (fabs(a) < eps) {
        answer->rootsCount = -1; // Не квадратное уравнение
        answer->r1 = 0;
        answer->r2 = 0;
        return OK;
    }
    
    // Вычисляем дискриминант
    double discriminant = b * b - 4 * a * c;
    
    // Проверяем различные случаи дискриминанта
    if (fabs(discriminant) < eps) {
        // Один корень (кратность 2)
        answer->rootsCount = 1;
        answer->r1 = -b / (2 * a);
        answer->r2 = answer->r1;
    }
    else if (discriminant > 0) {
        // Два различных корня
        answer->rootsCount = 2;
        answer->r1 = (-b + sqrt(discriminant)) / (2 * a);
        answer->r2 = (-b - sqrt(discriminant)) / (2 * a);
    }
    else {
        // Нет действительных корней
        answer->rootsCount = 0;
        answer->r1 = 0;
        answer->r2 = 0;
    }
    
    return OK;
}

errorCodes m(int a, int b, int* isMultiple) {
    if (isMultiple == NULL) {
        return POINTER_ERROR;
    }
    
    // Проверка на ненулевые числа
    if (a == 0 || b == 0) {
        return BAD_INPUT;
    }
    
    // Проверка кратности: первое число кратно второму, если остаток от деления равен 0
    if (a % b == 0) {
        *isMultiple = 1; // Кратно
    } else {
        *isMultiple = 0; // Не кратно
    }
    
    return OK;
}

errorCodes t(double eps, float a, float b, float c, int* isTriangle) {
    if (isTriangle == NULL) {
        return POINTER_ERROR;
    }
    
    // Проверка на положительность сторон (дополнительная проверка)
    if (a <= 0 || b <= 0 || c <= 0) {
        *isTriangle = 0;
        return OK;
    }
    
    // Проверка существования треугольника
    if (!canFormTriangle(a, b, c)) {
        *isTriangle = 0;
        return OK;
    }
    
    // Сортируем стороны по возрастанию для удобства
    float sides[3] = {a, b, c};
    
    // Пузырьковая сортировка
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (sides[j] > sides[j + 1]) {
                float temp = sides[j];
                sides[j] = sides[j + 1];
                sides[j + 1] = temp;
            }
        }
    }
    
    // Теперь sides[0] <= sides[1] <= sides[2]
    // Проверяем теорему Пифагора: квадрат гипотенузы равен сумме квадратов катетов
    double hypotenuse_sq = sides[2] * sides[2];
    double legs_sq_sum = sides[0] * sides[0] + sides[1] * sides[1];
    
    // Сравниваем с учетом точности epsilon
    if (fabs(hypotenuse_sq - legs_sq_sum) < eps) {
        *isTriangle = 1; // Может быть прямоугольным треугольником
    } else {
        *isTriangle = 0; // Не может быть прямоугольным треугольником
    }
    
    return OK;
}