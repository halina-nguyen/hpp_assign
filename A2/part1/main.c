// Source: template from part 2 in Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include "triang.h"

int main(int argc, char** argv) {
    unsigned int n = 30;
    if (argc > 1) n = atoi(argv[1]);
    print_triang(n);
    return 0;
}