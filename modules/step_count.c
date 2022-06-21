#include <stdio.h>
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