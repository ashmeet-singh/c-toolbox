#include <stdio.h>
#define TEST_SIZE 1000000000

long int test_buffer[TEST_SIZE];

int main()
{
    long int i;

    i = 0;

    for (i = 0; i < TEST_SIZE; i++)
    {
        test_buffer[i] = i + 1;
    }

    for (i = 0; i < TEST_SIZE; i++)
    {
        if (test_buffer[i] != (i + 1))
        {
            printf("FAILED\n");
            return 0;
        }
    }

    printf("PASS\n");
    return 0;
}