#include "../include/numbers.h"

int main() {
    int base;
    long long maxAbsValue;
    char maxOriginalStr[1024];
    
    errorCodes baseResult = readBase(&base);
    if (baseResult != OK) {
        return baseResult;
    }
    
    errorCodes processResult = processNumbers(base, &maxAbsValue, maxOriginalStr, sizeof(maxOriginalStr));
    if (processResult != OK) {
        return processResult;
    }
    
    errorCodes printResult = printResults(maxAbsValue, maxOriginalStr);
    if (printResult != OK) {
        return printResult;
    }
    
    return OK;
}