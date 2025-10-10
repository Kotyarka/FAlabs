#include <stdio.h>
#include <stdlib.h>
#include "../include/numbers.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments! type only epsilon");
        return BAD_INPUT;
    }

    char *typedEpsilon;
    double eps = strtod(argv[1], &typedEpsilon);
    if (*typedEpsilon != '\0' || eps <= 0) {
        printf("Type correct epsilon!");
        return BAD_INPUT;
    }

    double result;
    errorCodes errorCode;

    errorCode = eRow(eps, &result);
    if (errorCode == OK) printf("e by row  %.15f\n", result);
    else printf("e by row  ERROR: %d\n", errorCode);

    errorCode = eLimit(eps, &result);
    if (errorCode == OK) printf("e by limit %.15f\n", result);
    else printf("e by limit ERROR: %d\n", errorCode);

    errorCode = eEquation(eps, &result);
    if (errorCode == OK) printf("e by equation %.15f\n", result);
    else printf("e by equation ERROR: %d\n", errorCode);

    errorCode = lnLimit(eps, &result);
    if (errorCode == OK) printf("ln2 by limit %.15f\n", result);
    else printf("ln2 by limit ERROR: %d\n", errorCode);

    errorCode = lnRow(eps, &result);
    if (errorCode == OK) printf("ln2 by row %.15f\n", result);
    else printf("ln2 by row ERROR: %d\n", errorCode);

    errorCode = lnEquation(eps, &result);
    if (errorCode == OK) printf("ln2 by equation %.15f\n", result);
    else printf("ln2 by equation ERROR: %d\n", errorCode);

    errorCode = sqrtRow(eps, &result);
    if (errorCode == OK) printf("sqrt(2) by row %.15f\n", result);
    else printf("sqrt(2) by row ERROR: %d\n", errorCode);

    errorCode = sqrtEquation(eps, &result);
    if (errorCode == OK) printf("sqrt(2) by equation %.15f\n", result);
    else printf("sqrt(2) by equation ERROR: %d\n", errorCode);

    errorCode = sqrtLimit(eps, &result);
    if (errorCode == OK) printf("sqrt(2) by limit %.15f\n", result);
    else printf("sqrt(2) by limitERROR: %d\n", errorCode);

    errorCode = piRow(eps, &result);
    if (errorCode == OK) printf("Pi by row %.15f\n", result);
    else printf("Pi by row ERROR: %d\n", errorCode);

    errorCode = piLimit(eps, &result);
    if (errorCode == OK) printf("Pi by limit %.15f\n", result);
    else printf("Pi by limitERROR: %d\n", errorCode);

    errorCode = piEquation(eps, &result);
    if (errorCode == OK) printf("Pi by equation%.15f\n", result);
    else printf("Pi by equation ERROR: %d\n", errorCode);

    errorCode = gammaLimit(eps, &result);
    if (errorCode == OK) printf("y by limit %.15f\n", result);
    else printf("y by limit ERROR: %d\n", errorCode);

    errorCode = gammaRow(eps, &result);
    if (errorCode == OK) printf("y by row %.15f\n", result);
    else printf("y by row ERROR: %d\n", errorCode);

    errorCode = gammaEquation(eps, &result);
    if (errorCode == OK) printf("y by equation %.15f\n", result);
    else printf("y by equation ERROR: %d\n", errorCode);

    return 0;
}