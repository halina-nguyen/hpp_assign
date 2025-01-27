#include <stdio.h>
#include <stdlib.h>
#include "triang.h"

// calculates faculty of n
int faculty(int n) {
    if (n < 0) {
        //printf("ERROR: n must be greater than or equal to 0\n");
        exit(0);
    }

    int i, result = 1;
    for (i = 1; i <= n; i++) result *= i;
    return result;
}

// print Pascal’s triangle
void print_triang(int rows) {
    if (rows < 0) {
        //printf("ERROR: rows must be greater than or equal to 0\n");
        exit(0);
    }

    int n, k, entry;
    for (n = 0; n < rows; n++) {
        for (k = 0; k <= n; k++) {
            entry = faculty(n) / (faculty(k) * faculty(n - k));
            printf("%d ", entry);
        }
        printf("\n");
    }
}