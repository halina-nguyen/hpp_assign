#include <stdio.h>
#include <stdlib.h>
#include "january.h"

// add day with its minimum and maximum temperature to database
void add_entry(day_t** head, int index, float min, float max) {
    day_t* new_day = (day_t*)malloc(sizeof(day_t));
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

    if ((*head)->index == index) {
        *head = (*head)->next;
    } else {
        while (current != NULL && current->index != index) {
            previous = current;
            current = current->next;
        }

        if (current == NULL) {
            //printf("ERROR: Entry %d not found\n", index);
            return;
        }

        previous->next = current->next;
    }
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
void free_list(day_t* head) {
    while (head != NULL) {
        day_t* next = head->next;
        free(head);
        head = next;
    }
    head = NULL;
}