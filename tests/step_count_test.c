#include <stdint.h>
#include "acutest.h"

#include "step_count.h"

void get_debug_values(long long* n, long long* steps, long long* total, byte* type, char** name);

void foo(uint32_t n)
{
    STPS_FUNC_VARIA("foo(n)", n);

    for(; n!= 0; n--)
        STPS_STEP; 
}

void bar(uint32_t n)
{
    STPS_FUNC_CONST("bar(n)", n);
}

void test_start()
{
    STPS_START_REAL;

    long long n = 10;
    long long steps = 10;
    long long total = 10;
    byte type = 10;
    char* name = (char*)10;

    get_debug_values(&n, &steps, &total, &type, &name);

    TEST_ASSERT(n == 0);
    TEST_ASSERT(steps == 0);
    TEST_ASSERT(total == 0);
    TEST_ASSERT(type == STPS_REAL);
    TEST_ASSERT(name == NULL);

    STPS_END;
    STPS_START_AMOR;

    get_debug_values(&n, &steps, &total, &type, &name);

    TEST_ASSERT(type == STPS_AMOR);
    STPS_END;
}

void test_steps_foo()
{
    STPS_START_REAL;

    long long n = 0;
    long long steps = 0;
    long long total = 0;
    byte type = 0;
    char* name = NULL;

    long long sum = 0;

    for(int num = 0; num < 1001; num++)
    {
        foo(num);
        get_debug_values(&n, &steps, &total, &type, &name);
        sum += num;

        TEST_ASSERT(n == num);
        TEST_ASSERT(steps == num);
        TEST_ASSERT(total == sum);
        TEST_ASSERT(strcmp(name, "foo(n)") == 0);

        STPS_PRINT_CONSOLE;
        STPS_PRINT_DIR("out.csv");
    }
    STPS_END;

    STPS_START_REAL;
    sum = 0;
    for(int num = 0; num < 1001; num++)
    {
        bar(num);
        get_debug_values(&n, &steps, &total, &type, &name);
        sum += 1;

        TEST_ASSERT(n == num);
        TEST_ASSERT(steps == 1);
        TEST_ASSERT(total == sum);
        TEST_ASSERT(strcmp(name, "bar(n)") == 0);

        STPS_PRINT_CONSOLE;
        STPS_PRINT_DIR("out2.csv");
    }
    STPS_END;

    STPS_START_AMOR;
    sum = 0;
    for(int num = 1; num < 1001; num++)
    {
        foo(num);
        get_debug_values(&n, &steps, &total, &type, &name);
        sum += num;

        TEST_ASSERT(n == num);
        TEST_ASSERT(steps == num);
        TEST_ASSERT(total == sum);
        TEST_ASSERT(strcmp(name, "foo(n)") == 0);

        STPS_PRINT_CONSOLE;
        STPS_PRINT_DIR("out.csv");
    }
     STPS_END;

    STPS_START_REAL;
    sum = 0;
    for(int num = 1; num < 1001; num++)
    {
        bar(num);
        get_debug_values(&n, &steps, &total, &type, &name);
        sum += 1;

        TEST_ASSERT(n == num);
        TEST_ASSERT(steps == 1);
        TEST_ASSERT(total == sum);
        TEST_ASSERT(strcmp(name, "bar(n)") == 0);

        STPS_PRINT_CONSOLE;
        STPS_PRINT_DIR("out2.csv");
    }
    STPS_END;
}

TEST_LIST = {
    { "init_counter",           test_start      },
    { "counting_and_printing",  test_steps_foo  },
    { NULL, NULL }
};



