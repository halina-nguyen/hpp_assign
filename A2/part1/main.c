#include <stdio.h>
#include <stdlib.h>
#include "triang.h"

int main(int argc, char** argv) {
    int n = 5;
    if (argc > 1) n = atoi(argv[1]);
    print_triang(n);

    return 0;
}