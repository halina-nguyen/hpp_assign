// Source: AI (for improvements)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// print Pascal's Triangle
void print_triang(unsigned int rows) {
    for (unsigned int n = 0; n < rows; n++) {
        unsigned long long entry = 1;
        for (unsigned int k = 0; k <= n; k++) {
            printf("%llu ", entry);
            entry = entry * (n - k) / (k + 1);
        }
        printf("\n");
    }
}