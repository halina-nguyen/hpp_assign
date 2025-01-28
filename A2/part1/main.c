// Source: template from part 2 in Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include "triang.h"
#include <time.h>

int main(int argc, char** argv) {
    clock_t start_time = clock();
    int n = 5;
    if (argc > 1) n = atoi(argv[1]);
    print_triang(n);
    clock_t end_time = clock();
    return 0;
}