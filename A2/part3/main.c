// Source: HPP Lecture - C Programming (Part 2)
//         AI (mainly for errors)

#include <stdio.h>
#include <stdlib.h>
#include "january.h"

int main() {
    char command;
    int index;
    float min, max;
    day_t* head = NULL;

    while (1) {
        // read input command
        printf("Enter command: ");
        if (scanf(" %c", &command) != 1) {
            //printf("Invalid input\n");
            while (getchar() != '\n');
        }

        switch (command) {
            // A index min max
            case 'A':
                if (scanf(" %d %f %f", &index, &min, &max) != 3 || index < 1 || index > 31) {
                    //printf("Invalid input\n");
                    while (getchar() != '\n');
                } else {
                    char leftover;
                    if (scanf("%c", &leftover) == 1 && leftover != '\n') {
                        //printf("Invalid input\n");
                        while (getchar() != '\n');
                    } else {
                        add_entry(&head, index, min, max);
                    }
                }
                break;
            // D index
            case 'D':
                if (scanf(" %d", &index) != 1 || index < 1 || index > 31) {
                    //printf("Invalid input\n");
                    while (getchar() != '\n');
                } else {
                    char leftover;
                    if (scanf("%c", &leftover) == 1 && leftover != '\n') {
                        //printf("Invalid input\n");
                        while (getchar() != '\n');
                    } else {
                        delete_entry(&head, index);
                    }
                }
                break;
            // P
            case 'P':
                print_database(head);
                break;
            // Q
            case 'Q':
                free_list(head);
                //printf("Database will be closed\n");
                return 0;
            // not defined command
            default:
                printf("Invalid command\n");
                while (getchar() != '\n');
        }
    }

    // free memory
    free_list(head);
    return 0;
}
