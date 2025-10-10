#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../include/functions.h"

#define TEST_EPS 1e-10

int double_equal(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

double constant_function(double x) { 
    (void)x;
    return 1.0; 
}

double linear_function(double x) { 
    return x; 
}

double square_function(double x) { 
    return x * x; 
}

void test_functions() {
    printf("Testing functions f(x)...\n");
    
    assert(double_equal(aFunction(0.0), 1.0, TEST_EPS));
    assert(double_equal(aFunction(0.5), log(1.5)/0.5, TEST_EPS));
    assert(double_equal(aFunction(1.0), log(2.0), TEST_EPS));
    printf("  aFunction: OK\n");
    
    assert(double_equal(bFunction(0.0), 1.0, TEST_EPS));
    assert(double_equal(bFunction(0.5), exp(-0.125), TEST_EPS));
    assert(double_equal(bFunction(1.0), exp(-0.5), TEST_EPS));
    printf("  bFunction: OK\n");
    
    assert(double_equal(cFunction(0.0), 0.0, TEST_EPS));
    assert(double_equal(cFunction(0.5), -log(0.5), TEST_EPS));
    assert(cFunction(0.999) > 0);
    printf("  cFunction: OK\n");
    
    assert(double_equal(dFunction(0.0), 1.0, TEST_EPS));
    assert(double_equal(dFunction(0.5), pow(0.5, 0.5), TEST_EPS));
    assert(double_equal(dFunction(1.0), 1.0, TEST_EPS));
    printf("  dFunction: OK\n");
    
    printf("All function tests passed!\n\n");
}

void test_trapezoid_process() {
    printf("Testing trapezoidProcess...\n");
    
    double result;
    
    result = trapezoidProcess(bFunction, 0, 1, 4, 0);
    assert(result > 0 && result < 1);
    printf("  trapezoidProcess with bFunction: OK\n");
    
    result = trapezoidProcess(aFunction, 0, 1, 8, 0);
    assert(result > 0);
    printf("  trapezoidProcess with aFunction: OK\n");
    
    printf("trapezoidProcess tests passed!\n\n");
}

void test_trapezoid_rule_known_values() {
    printf("Testing trapezoidRule with known values...\n");
    
    double result;
    errorCodes status;
    
    status = trapezoidRule(constant_function, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(double_equal(result, 1.0, 1e-6));
    printf("  Constant function test: OK\n");
    
    status = trapezoidRule(linear_function, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(double_equal(result, 0.5, 1e-6));
    printf("  Linear function test: OK\n");
    
    status = trapezoidRule(square_function, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(double_equal(result, 1.0/3.0, 1e-6));
    printf("  Square function test: OK\n");
    
    printf("Known values tests passed!\n\n");
}

void test_our_functions_integration() {
    printf("Testing our specific functions integration...\n");
    
    double result;
    errorCodes status;
    
    status = trapezoidRule(aFunction, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(result > 0.8 && result < 1.2);
    printf("  aFunction integration: OK\n");
    
    status = trapezoidRule(bFunction, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(result > 0.5 && result < 1.0);
    printf("  bFunction integration: OK\n");
    
    status = trapezoidRule(cFunction, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(result > 0.5);
    printf("  cFunction integration: OK\n");
    
    status = trapezoidRule(dFunction, 0, 1, 1e-8, &result);
    assert(status == OK);
    assert(result > 0.5 && result < 1.5);
    printf("  dFunction integration: OK\n");
    
    printf("Our functions integration tests passed!\n\n");
}

void test_error_handling() {
    printf("Testing error handling...\n");
    
    double result;
    errorCodes status;
    
    status = trapezoidRule(NULL, 0, 1, 1e-8, &result);
    assert(status == POINTER_ERROR);
    printf("  NULL function pointer: OK\n");
    
    status = trapezoidRule(aFunction, 0, 1, 0, &result);
    assert(status == BAD_INPUT);
    printf("  Zero epsilon: OK\n");
    
    status = trapezoidRule(aFunction, 0, 1, -1e-8, &result);
    assert(status == BAD_INPUT);
    printf("  Negative epsilon: OK\n");
    printf("Error handling tests passed!\n\n");
}

void test_convergence() {
    printf("Testing method convergence...\n");
    
    double result1, result2;
    errorCodes status;
    
    status = trapezoidRule(aFunction, 0, 1, 1e-4, &result1);
    assert(status == OK);
    
    status = trapezoidRule(aFunction, 0, 1, 1e-8, &result2);
    assert(status == OK);
    
    assert(fabs(result1 - result2) < 1e-3);
    printf("  Convergence test: OK\n");
    
    printf("Convergence tests passed!\n\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    double result;
    errorCodes status;
    
    status = trapezoidRule(aFunction, 0.5, 0.5 + 1e-10, 1e-8, &result);
    assert(status == OK);
    assert(double_equal(result, 0.0, 1e-10));
    printf("  Very small interval: OK\n");
    
    status = trapezoidRule(aFunction, 0.5, 0.5, 1e-8, &result);
    assert(status == OK);
    assert(double_equal(result, 0.0, TEST_EPS));
    printf("  Zero-length interval: OK\n");
    
    printf("Edge cases tests passed!\n\n");
}

void run_all_tests() {
    printf("=== Starting Internal Tests ===\n\n");
    
    test_functions();
    test_trapezoid_process();
    test_trapezoid_rule_known_values();
    test_our_functions_integration();
    test_error_handling();
    test_convergence();
    test_edge_cases();
    
    printf("=== All Internal Tests PASSED ===\n");
}

int main() {
    run_all_tests();
    return 0;
}