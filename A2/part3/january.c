// Source: HPP Lecture - C Programming (Part 2)
//         https://www.programiz.com/dsa/linked-list-operations
//         https://www.tutorialspoint.com/delete-a-linked-list-node-at-a-given-position-in-cplusplus
//         AI (mainly for errors)

#include <stdio.h>
#include <stdlib.h>
#include "january.h"

// add day with its minimum and maximum temperature to database
void add_entry(day_t** head, int index, float min, float max) {
    day_t* new_day = (day_t*)malloc(sizeof(day_t));
    if (!new_day) {
        printf("ERROR: Memory allocation failed\n");
        return;
    }

    new_day->index = index;
    new_day->min = min;
    new_day->max = max;
    new_day->next = NULL;

    if (*head == NULL) {
        *head = new_day;
    } else if (index < (*head)->index) {
        new_day->next = *head;
        *head = new_day;
    } else {
        day_t* current = *head;
        while (current->next != NULL && current->next->index <= index) current = current->next;

        if (current->index == index) {
            current->min = min;
            current->max = max;
            free(new_day);

            //printf("Entry %d updated\n", index);
            return;
        } else {
            new_day->next = current->next;
            current->next = new_day;
        }
    }
    //printf("Entry %d added\n", index);
}

// remove day from database
void delete_entry(day_t** head, int index) {
    if (*head == NULL) {
        //printf("ERROR: No entries in database\n");
        return;
    }

    day_t* current = *head;
    day_t* previous = NULL;

    if (current->index == index) {
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->index != index) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        //printf("ERROR: Entry %d not found\n", index);
        return;
    }

    previous->next = current->next;
    free(current);
    //printf("Entry %d deleted\n", index);
}

// print database table
void print_database(day_t* head) {
    printf("day\tmin\t\tmax\n");
    while (head != NULL) {
        head->index < 10 ? printf(" %d\t", head->index) : printf("%d\t", head->index);
        printf("%f\t%f\n", head->min, head->max);
        head = head->next;
    }
}

// free memory
void free_list(day_t** head) {
    day_t* current = *head;
    while (current != NULL) {
        day_t* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}