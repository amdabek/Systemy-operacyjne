#include <stdio.h>

int collatz_conjecture(int input)
{
    if (input % 2 == 0)
    {
        return input / 2;
    }
    else
    {
        return 3 * input + 1;
    }
}

int test_collatz_convergence(int input, int max_iter, int *steps)
{
    int current = input;
    for (int i = 0; i < max_iter; i++)
    {
        steps[i] = current;
        if (current == 1)
        {
            return i + 1; 
        }
        current = collatz_conjecture(current);
    }
    return 0;
}
