#include <stdio.h>

#include "utils.h"

void print_int_array(int *arr, int length)
{
    printf("[");

    for (int i = 0; i < length; i++)
    {
        if (i > 0)
            printf(", ");

        printf("%d", arr[i]);
    }

    printf("]");
}

void swap_ints(int *p, int *q)
{
    int t = *p;

    *p = *q;
    *q = t;
}
