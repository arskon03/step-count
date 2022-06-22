#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "step_count.h"

// Define pointer of struct
typedef struct step_counter* StepCounter;

struct step_counter {
    long long steps;
    long long n;
    long long total;
    byte type;
    char* name;
};

StepCounter counter = NULL;

// Function that initializes a counter
StepCounter init_counter(byte type)
{
    StepCounter counter = malloc(sizeof(*counter));

    counter->steps = 0;
    counter->n = 0;
    counter->total = 0;
    counter->type = type;

    counter->name = NULL;

    return counter;
    
    //  counter->name = malloc(sizeof(char) * strlen(name));
    //  strcpy(counter->name, name);
}

// Function that uninitializes values of counter
void uninit_counter(StepCounter counter)
{
    if (counter == NULL)
        return;

    if (counter->name != NULL)
        free(counter->name);

    free(counter);
    counter = NULL;
}

// Function that sets the counter to specified values
void set_counter(StepCounter counter, long long steps, long long n, char* name)
{
    if (counter == NULL)
        return;

    counter->steps = steps;
    counter->total += steps;
    counter->n = n;

    // If the name is NULL set the counter name to NULL also
    if (name == NULL)
        counter->name = NULL;
    // Else free if possible the counter name and then allocate memory for new name
    else
    {
        if (counter->name != NULL)
            free(counter->name);
        
        counter->name = malloc(sizeof(char) * strlen(name));
        strcpy(counter->name, name);
    }
}

// Function that adds steps to a counter
void add_steps(StepCounter counter, long long steps)
{
    counter->steps += steps;
    counter->total += steps;
}

long long getter_steps(StepCounter counter)
{
    if (counter == NULL)
        return -1;

    return counter->steps;
}

long long getter_total(StepCounter counter)
{
    if (counter == NULL)
        return -1;

    return counter->total;
}

void print_counter(StepCounter counter, char* dir)
{
    if (counter == NULL)
        return;

    // Check if file is needed
    FILE* file = NULL;
    bool to_file = dir != NULL;

    // If it is
    if (to_file)
    {
        // Open at the directory provided and set the cursor at the end of the file
        file = fopen(dir, "a+");

        // If anything goes wring end function
        assert(file != NULL);
        assert(!fseek(file, 0, SEEK_END));
    }

    // Print name if needed
    if (counter->name != NULL)
    {
        if (!to_file)
            printf("(%s) ", counter->name);
        else
            fprintf(file, "(%s) ", counter->name);
    }
        

    // Print n and make sure it is not negative
    assert(counter->n >= 0);
    if (!to_file)
        printf("n(%s) = %lld,", (counter->type == STPS_AMOR) ? "executions" : "values", counter->n);
    else
        fprintf(file, "n(%s) = %lld,", (counter->type == STPS_AMOR) ? "executions" : "values", counter->n);

    // If type is amortized, make sure n>0 and print average steps
    if (counter->type == STPS_AMOR)
    {
        assert(counter->n > 0);
        if (!to_file)
            printf("%lld\n", counter->total / counter->n);
        else
            fprintf(file, "%lld\n", counter->total / counter->n);
    }
    // Else if its is real time print steps
    else
    {
        if (!to_file)
            printf("%lld\n", counter->steps);
        else
            fprintf(file, "%lld\n", counter->steps);
    }

    // Close file
    if (to_file)
        assert(fclose(file) == 0);  

}

//  ----------------
//  HEADER FUNCTIONS
//  ----------------

void start_count(byte type)
{
    counter = init_counter(type);
}

void end_count()
{
    uninit_counter(counter);
}

void set_count(char* name, long long n, long long count)
{
    set_counter(counter, count, n, name);
}

void increment_steps(long long increment)
{
    add_steps(counter, increment);
}

long long get_steps()
{
    return getter_steps(counter);
}

long long get_total()
{
    return getter_total(counter);
}

void print_counter_results(char* dir)
{
    print_counter(counter, dir);
}

void get_counter_values(StepCounter counter, long long* n, long long* steps, long long* total, byte* type, char** name)
{
    *n = counter->n;
    *steps = counter->steps;
    *total = counter->total;
    *type = counter->type;
    *name = counter->name;
}

//  --------------
//  TEST FUNCTIONS
//  --------------

// LCOV_EXCL_START

void get_debug_values(long long* n, long long* steps, long long* total, byte* type, char** name)
{
    get_counter_values(counter, n, steps, total, type, name);
}

// LCOV_EXCL_STOP