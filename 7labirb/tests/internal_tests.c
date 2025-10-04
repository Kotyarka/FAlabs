#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "numbers.h"

int strings_equal(const char* actual, const char* expected) {
    if (actual == NULL && expected == NULL) return 1;
    if (actual == NULL || expected == NULL) return 0;
    return strcmp(actual, expected) == 0;
}

void test_baseParsing() {
    int base = 0;
    
    errorCodes status = baseParsing("16", &base);
    assert(status == OK);
    assert(base == 16);
    
    status = baseParsing("2", &base);
    assert(status == OK);
    assert(base == 2);
    
    status = baseParsing("36", &base);
    assert(status == OK);
    assert(base == 36);
    
    status = baseParsing("1", &base);
    assert(status == INVALID_BASE);
    
    status = baseParsing("37", &base);
    assert(status == INVALID_BASE);
    
    status = baseParsing("abc", &base);
    assert(status == WRONG_ARGUMENTS);
    
    status = baseParsing("12a", &base);
    assert(status == WRONG_ARGUMENTS);
    
    printf("test_baseParsing: OK\n");
}

void test_numChecker() {
    int isMinus = 1;
    int base = 16;
    
    errorCodes status = numChecker("FF", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == 1);
    
    status = numChecker("-1A", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == -1);
    
    status = numChecker("+2B", &base, &isMinus);
    assert(status == OK);
    assert(isMinus == 1);
    
    base = 10;
    status = numChecker("12A", &base, &isMinus);
    assert(status == INVALID_DIGIT);
    
    status = numChecker("12$3", &base, &isMinus);
    assert(status == WRONG_ARGUMENTS);
    
    status = numChecker("-", &base, &isMinus);
    assert(status == EMPTY_INPUT);
    
    printf("test_numChecker: OK\n");
}

void test_toDecInt() {
    long num = 0;
    
    errorCodes status = toDecInt("FF", 16, &num);
    assert(status == OK);
    assert(num == 255);
    
    status = toDecInt("-1A", 16, &num);
    assert(status == OK);
    assert(num == -26);
    
    status = toDecInt("1010", 2, &num);
    assert(status == OK);
    assert(num == 10);
    
    status = toDecInt("77", 8, &num);
    assert(status == OK);
    assert(num == 63);
    
    status = toDecInt("0", 10, &num);
    assert(status == OK);
    assert(num == 0);
    
    status = toDecInt("12A", 10, &num);
    assert(status == INVALID_DIGIT);
    
    printf("test_toDecInt: OK\n");
}

void test_toNsystem() {
    char buffer[BUFSIZ];
    long num = 0;
    
    num = 255;
    errorCodes status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "FF"));
    
    num = -26;
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "-1A"));
    
    num = 0;
    status = toNsystem(buffer, 16, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "0"));
    
    num = 10;
    status = toNsystem(buffer, 2, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "1010"));
    
    num = 35;
    status = toNsystem(buffer, 36, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "Z"));
    
    printf("test_toNsystem: OK\n");
}

void test_removeLeadingZeros() {
    char buffer[1024];
    
    strcpy(buffer, "00123");
    errorCodes status = removeLeadingZeros(buffer);
    assert(status == OK);
    assert(strings_equal(buffer, "123"));
    
    strcpy(buffer, "000");
    status = removeLeadingZeros(buffer);
    assert(status == OK);
    assert(strings_equal(buffer, "0"));
    
    strcpy(buffer, "-00123");
    status = removeLeadingZeros(buffer);
    assert(status == OK);
    assert(strings_equal(buffer, "-123"));
    
    strcpy(buffer, "+00123");
    status = removeLeadingZeros(buffer);
    assert(status == OK);
    assert(strings_equal(buffer, "123"));
    
    strcpy(buffer, "123");
    status = removeLeadingZeros(buffer);
    assert(status == OK);
    assert(strings_equal(buffer, "123"));
    
    printf("test_removeLeadingZeros: OK\n");
}

void test_findMinBase() {
    int minBase;
    
    errorCodes status = findMinBase("101", &minBase);
    assert(status == OK);
    assert(minBase == 2);
    
    status = findMinBase("FF", &minBase);
    assert(status == OK);
    assert(minBase == 16);
    
    status = findMinBase("Z", &minBase);
    assert(status == OK);
    assert(minBase == 36);
    
    status = findMinBase("0", &minBase);
    assert(status == OK);
    assert(minBase == 2);
    
    status = findMinBase("-1A", &minBase);
    assert(status == OK);
    assert(minBase == 11);
    
    status = findMinBase("12$3", &minBase);
    assert(status == INVALID_NUMBER);
    
    status = findMinBase("", &minBase);
    assert(status == INVALID_NUMBER);
    
    printf("test_findMinBase: OK\n");
}

void test_integration() {
    char buffer[BUFSIZ];
    long num = 0;
    int minBase;
    
    errorCodes status = findMinBase("FF", &minBase);
    assert(status == OK);
    assert(minBase == 16);
    
    status = toDecInt("FF", minBase, &num);
    assert(status == OK);
    assert(num == 255);
    
    status = toNsystem(buffer, 10, &num);
    assert(status == OK);
    assert(strings_equal(buffer, "255"));
    
    status = findMinBase("1010", &minBase);
    assert(status == OK);
    assert(minBase == 2);
    
    status = toDecInt("1010", minBase, &num);
    assert(status == OK);
    assert(num == 10);
    
    printf("test_integration: OK\n");
}

void test_all() {
    test_baseParsing();
    test_numChecker();
    test_toDecInt();
    test_toNsystem();
    test_removeLeadingZeros();
    test_findMinBase();
    test_integration();
    printf("All internal tests passed!\n");
}

int main() {
    test_all();
    return 0;
}