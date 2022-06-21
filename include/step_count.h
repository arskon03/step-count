#pragma once

typedef char byte;

//  -------------
//  MACROS TO USE
//  -------------

// Constants that signify the type of complexity
#define STPS_REAL 0
#define STPS_AMOR 1

// This should be used to start the counting in main before functions using the below macros are called
// Type signifies if we are calculating amortized or real time complexity
#define STPS_START(type) start_count(type)

// This should be used to after the counting has stopped in main so memory is freed
// Type signifies if we are calculating amortized or real time complexity
#define STPS_END() end_count()

// This should be used at the start of a function that has constant time (aka O(1): no loops, loops w/constant limits etc.)
// n >= 0 if used or < 0 to remain unused, name == NULL to remain unused
#define STPS_FUNC_CONST(name, n) set_count(name, n, 1)

// This should be used at the start of a function that has operations which depend on a variable (aka O(f(n)) loops etc.)
// n >= 0 if used or < 0 to remain unused, name == NULL to remain unused
#define STPS_FUNC_VARIA(name, n) set_count(name, n, 0)

// This is a step. Should be added inside loops and NOT in functions that initialized with the "STPS_FUNC" macro
#define STPS_STEP increment_steps(1)

// This gets the amount of steps completed at the moment
#define STPS_GET_STEPS get_steps()

// This gets the amount of total steps completed since init
#define STPS_GET_TOTAL get_total()

//  --------------------
//  UNDERLYING FUNCTIONS
//  --------------------

// Function that starts the counting of the steps of each action. Should be used in main before using functions that need to be counted
void start_count(byte type);

// Function that ends the counting of the steps of each action. Clears memory and should be used if the counting has stopped
void end_count();

// Function that resets the step_count for a new function to begin
void set_count(char* name, long long n, long long count);

// Function that increments the amount of steps made (can take negative values)
void increment_steps(long long increment);

// Function that returns the counted steps of the counter
long long get_steps();

// Function that returns the total steps of the counter
long long get_total();



