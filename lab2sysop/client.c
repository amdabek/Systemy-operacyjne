#include <stdio.h>
#ifdef DYNAMIC
#include <dlfcn.h>
#endif

#ifndef DYNAMIC
extern int collatz_conjecture(int input);
extern int test_collatz_convergence(int input, int max_iter, int *steps);
#endif

void display_sequence(int how_many, int sequence[])
{
    for (int i = 0; i < how_many; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

#ifdef DYNAMIC

int main()
{
    void *libHandle = dlopen("./libshared.so", RTLD_LAZY);
    if (!libHandle)
    {
        printf("Błąd: nie udało się otworzyć biblioteki!\n");
        return 0;
    }

    int (*test_func)(int, int, int *);
    test_func = dlsym(libHandle, "test_collatz_convergence");
    if (!test_func)
    {
        printf("Błąd: nie znaleziono funkcji w bibliotece!\n");
        dlclose(libHandle);
        return 0;
    }

    int test_values[] = {1, 2, 3, 1234, 1000, 9999, 837799};
    int num_values = sizeof(test_values) / sizeof(test_values[0]);

    int iteration_limit = 300; 
    int results[300];

    for (int i = 0; i < num_values; i++)
    {
        int start_value = test_values[i];
        int count_steps = test_func(start_value, iteration_limit, results);

        printf("\n===Test dla start_value = %d ===\n", start_value);

        if (count_steps > 0)
        {
            printf("Osiągnięto 1 w %d krokach.\n", count_steps);
            printf("Sekwencja:\n");
            display_sequence(count_steps, results);
        }
        else
        {
            printf("1 nie została osiągnięta w %d krokach.\n", iteration_limit);
        }
    }

    dlclose(libHandle);
    return 0;
}

#else 

int main(void)
{
    int test_values[] = {1, 2, 3, 1234, 1000, 9999, 837799};
    int num_values = sizeof(test_values) / sizeof(test_values[0]);

    int iteration_limit = 300; 
    int results[300];

    for (int i = 0; i < num_values; i++)
    {
        int start_value = test_values[i];
        int count_steps = test_collatz_convergence(start_value, iteration_limit, results);

        printf("\n===Test dla start_value = %d ===\n", start_value);

        if (count_steps > 0)
        {
            printf("Osiągnięto 1 w %d krokach.\n", count_steps);
            printf("Sekwencja:\n");
            display_sequence(count_steps, results);
        }
        else
        {
            printf("1 nie została osiągnięta w %d krokach.\n", iteration_limit);
        }
    }
    return 0;
}

#endif
