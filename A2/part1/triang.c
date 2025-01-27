// Source: template from part 2 in Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include "triang.h"

// calculates faculty of n
unsigned int faculty(unsigned int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) res *= i;
    return res;
}

// print Pascal’s triangle
void print_triang(unsigned int rows) {
    unsigned int n, k, entry;
    for (n = 0; n < rows; n++) {
        for (k = 0; k <= n; k++) {
            entry = faculty(n) / (faculty(k) * faculty(n - k));
            printf("%d ", entry);
        }
        printf("\n");
    }
}