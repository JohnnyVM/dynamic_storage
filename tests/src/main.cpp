#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

/** For each C test group */
TEST_GROUP_C_WRAPPER(dynamic_array)
{
    TEST_GROUP_C_SETUP_WRAPPER(dynamic_array); /** optional */
    TEST_GROUP_C_TEARDOWN_WRAPPER(dynamic_array); /** optional */
};

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
