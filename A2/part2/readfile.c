// Source: HPP Lecture: C Programming (Part 2)

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    double d;
    char c;
    float f;

    // open binary file
    FILE* stream = fopen("little_bin_file", "rb");
    if (stream == NULL) {
        //printf("ERROR: Can't opening file");
        exit(0);
    }

    // read content from file
    fread(&i, sizeof(int), 1, stream);
    fread(&d, sizeof(double), 1, stream);
    fread(&c, sizeof(char), 1, stream);
    fread(&f, sizeof(float), 1, stream);

    // close binary file
    fclose(stream);

    // print data
    printf("%d\n", i);
    printf("%lf\n", d);
    printf("%c\n", c);
    printf("%f\n", f);

    return 0;
}