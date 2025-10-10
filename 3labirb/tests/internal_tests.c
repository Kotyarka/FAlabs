#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../include/flags.h"

void test_isValidInteger() {
    printf("Testing isValidInteger...\n");
    
    assert(isValidInteger("123") == OK);
    assert(isValidInteger("-456") == OK);
    assert(isValidInteger("0") == OK);
    assert(isValidInteger("+789") == OK);
    
    assert(isValidInteger("12a3") == BAD_INPUT);
    assert(isValidInteger("12.3") == BAD_INPUT);
    assert(isValidInteger("") == BAD_INPUT);
    assert(isValidInteger("abc") == BAD_INPUT);
    
    printf("isValidInteger tests passed!\n");
}

// Тесты для isValidDouble
void test_isValidDouble() {
    printf("Testing isValidDouble...\n");
    
    assert(isValidDouble("123.456") == OK);
    assert(isValidDouble("-78.9") == OK);
    assert(isValidDouble("0.0") == OK);
    assert(isValidDouble("+45.67") == OK);
    assert(isValidDouble("123") == OK);
    assert(isValidDouble(".5") == OK);
    
    assert(isValidDouble("12a.34") == BAD_INPUT);
    assert(isValidDouble("12.34.56") == BAD_INPUT);
    assert(isValidDouble("") == BAD_INPUT);
    assert(isValidDouble("abc") == BAD_INPUT);
    
    printf("isValidDouble tests passed!\n");
}

// Тесты для isFlagValid
void test_isFlagValid() {
    printf("Testing isFlagValid...\n");
    
    assert(isFlagValid("-q") == OK);
    assert(isFlagValid("-m") == OK);
    assert(isFlagValid("-t") == OK);
    assert(isFlagValid("/q") == OK);
    assert(isFlagValid("/m") == OK);
    assert(isFlagValid("/t") == OK);
    
    assert(isFlagValid("-a") == BAD_INPUT);
    assert(isFlagValid("-x") == BAD_INPUT);
    assert(isFlagValid("--q") == BAD_INPUT);
    assert(isFlagValid("q") == BAD_INPUT);
    assert(isFlagValid("") == BAD_INPUT);
    assert(isFlagValid(NULL) == POINTER_ERROR);
    
    printf("isFlagValid tests passed!\n");
}

// Тесты для convertStrToNum
void test_convertStrToNum() {
    printf("Testing convertStrToNum...\n");
    
    int num;
    assert(convertStrToNum("123", &num) == OK && num == 123);
    assert(convertStrToNum("-456", &num) == OK && num == -456);
    assert(convertStrToNum("0", &num) == OK && num == 0);
    
    assert(convertStrToNum("12a3", &num) == BAD_INPUT);
    assert(convertStrToNum("", &num) == BAD_INPUT);
    assert(convertStrToNum("123", NULL) == POINTER_ERROR);
    
    printf("convertStrToNum tests passed!\n");
}

// Тесты для canFormTriangle
void test_canFormTriangle() {
    printf("Testing canFormTriangle...\n");
    
    assert(canFormTriangle(3, 4, 5) == OK);
    assert(canFormTriangle(5, 5, 5) == OK);
    assert(canFormTriangle(2, 3, 4) == OK);
    
    assert(canFormTriangle(1, 2, 3) == BAD_INPUT);
    assert(canFormTriangle(1, 1, 3) == BAD_INPUT);
    assert(canFormTriangle(0, 1, 2) == BAD_INPUT);
    
    printf("canFormTriangle tests passed!\n");
}

// Тесты для функции m (multiple check)
void test_m_function() {
    printf("Testing m function...\n");
    
    int isMultiple;
    
    assert(m(10, 5, &isMultiple) == OK && isMultiple == 1);
    assert(m(15, 3, &isMultiple) == OK && isMultiple == 1);
    assert(m(10, 3, &isMultiple) == OK && isMultiple == 0);
    assert(m(7, 7, &isMultiple) == OK && isMultiple == 1);
    
    assert(m(10, 0, &isMultiple) == BAD_INPUT);
    assert(m(0, 5, &isMultiple) == BAD_INPUT);
    assert(m(10, 5, NULL) == POINTER_ERROR);
    
    printf("m function tests passed!\n");
}

// Тесты для функции t (right triangle check)
void test_t_function() {
    printf("Testing t function...\n");
    
    int isTriangle;
    double eps = 0.0001;
    
    assert(t(eps, 3, 4, 5, &isTriangle) == OK && isTriangle == 1);
    assert(t(eps, 5, 12, 13, &isTriangle) == OK && isTriangle == 1);
    assert(t(eps, 2, 3, 4, &isTriangle) == OK && isTriangle == 0);
    assert(t(eps, 1, 1, 1.4142, &isTriangle) == OK && isTriangle == 1);
    
    assert(t(eps, 0, 3, 4, &isTriangle) == OK && isTriangle == 0);
    assert(t(eps, -1, 3, 4, &isTriangle) == OK && isTriangle == 0);
    assert(t(eps, 3, 4, 5, NULL) == POINTER_ERROR);
    
    printf("t function tests passed!\n");
}

// Тесты для функции equationSolving
void test_equationSolving() {
    printf("Testing equationSolving...\n");
    
    quadraticSolution solution;
    double eps = 0.0001;
    
    // Two real roots: x^2 - 3x + 2 = 0 -> x=1, x=2
    assert(equationSolving(eps, 1, -3, 2, &solution) == OK);
    assert(solution.rootsCount == 2);
    assert(fabs(solution.r1 - 2.0) < eps || fabs(solution.r1 - 1.0) < eps);
    assert(fabs(solution.r2 - 2.0) < eps || fabs(solution.r2 - 1.0) < eps);
    
    // One real root: x^2 - 2x + 1 = 0 -> x=1
    assert(equationSolving(eps, 1, -2, 1, &solution) == OK);
    assert(solution.rootsCount == 1);
    assert(fabs(solution.r1 - 1.0) < eps);
    
    // No real roots: x^2 + 1 = 0
    assert(equationSolving(eps, 1, 0, 1, &solution) == OK);
    assert(solution.rootsCount == 0);
    
    // Not quadratic: 0x^2 + 2x + 3 = 0
    assert(equationSolving(eps, 0, 2, 3, &solution) == OK);
    assert(solution.rootsCount == -1);
    
    assert(equationSolving(eps, 1, 2, 3, NULL) == POINTER_ERROR);
    
    printf("equationSolving tests passed!\n");
}

void test_all() {
    printf("=== Starting all internal tests ===\n\n");
    
    test_isValidInteger();
    test_isValidDouble();
    test_isFlagValid();
    test_convertStrToNum();
    test_canFormTriangle();
    test_m_function();
    test_t_function();
    test_equationSolving();
    
    printf("\n=== All internal tests passed! ===\n");
}

int main() {
    test_all();
    return 0;
}