// database structure
typedef struct day {
    int index;
    float min;
    float max;
    struct day* next;
} day_t;

// add day with its minimum and maximum temperature to database
void add_entry(day_t** head, int index, float min, float max);

// remove day from database
void delete_entry(day_t** head, int index);

// print database table
void print_database(day_t* head);

// free memory
void free_list(day_t* head);