#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef void (* sorting_func)(int *, int, int);

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

void bubble_sort(int *array,
                 int  begin,
                 int  end)
{
    int repeat;

    do {
        repeat = 0;

        for (int i = begin + 1; i < end; i++)
        {
            if (array[i] < array[i - 1])
            {
                repeat = 1;
                swap_ints(&array[i], &array[i - 1]);
            }
        }
    } while (repeat);
}

void insertion_sort(int *array,
                    int  begin,
                    int  end)
{
    int split = begin + 1;

    while (split < end)
    {
        int value = array[split];
        int index = begin;

        while (index < split && array[index] < value)
            index++;

        for (int i = split; i > index; i--)
            array[i] = array[i - 1];

        array[index] = value;

        split++;
    }
}

void merge_sort(int *array,
                int  begin,
                int  end)
{
    int count = end - begin;

    if (count < 2)
        // array is already sorted
        return;

    int center = (begin + end) / 2;

    // go forward
    merge_sort(array, begin, center);
    merge_sort(array, center, end);

    // j - current index of left subarray
    // k - current index of right subarray
    int j = begin;
    int jend = center;
    int k = center;
    int kend = end;

    // create temporary buffer for merging
    int buff[count];
    int h = 0;

    // iterate over values
    // take the less one and push it 
    // to the buffer
    while (j != jend && k != kend)
    {
        if (array[j] < array[k])
            buff[h++] = array[j++];
        else
            buff[h++] = array[k++];
    }

    // copy remaining values from left or right side, if any
    while (j != jend)
        buff[h++] = array[j++];

    while (k != kend)
        buff[h++] = array[k++];

    // copy buffer to the original array
    for (int i = 0; i < h; i++)
        array[begin + i] = buff[i];
}

void quick_sort(int *array,
                int  begin,
                int  end)
{
    int count = end - begin;

    if (count < 2)
        // array is already sorted
        return;

    // take a pivot value
    int pivot = array[begin];

    // find the new pivot index, p, by 
    // counting items smaller than pivot value
    int p = begin;

    for (int i = begin; i < end; i++)
        if (array[i] < pivot)
            p++;

    // put pivot value on right index
    swap_ints(&array[begin], &array[p]);

    // put all values smaller than pivot to the left subarray,
    // and greater ones to the right subarray
    // j - index of left part, k - index of right part
    int j = begin;
    int k = p + 1;

    while (j < p)
    {
        if (array[p] < array[j])
        {
            // skip all values greater than pivot, which already
            // lie on right subarray
            while (pivot < array[k])
                k++;

            // here j index indicates on value bigger than pivot which
            // lies on left subarray, and k index on value smaller
            // than pivot which lies on right subarray,
            // so swap them
            swap_ints(&array[j], &array[k]);

            k++;
        }

        j++;
    }

    // go forward, excluding pivot item
    quick_sort(array, begin, p);
    quick_sort(array, p + 1, end);
}

void visual_sorting_test(const char   *name,
                         sorting_func  func)
{
    printf("visual test of %s sort\n", name);

    int count = 16;
    int arr[count];

    for (int i = 0; i < count; i++)
        arr[i] = rand() % 90 + 10;

    printf("before: ");
    print_int_array(arr, count);
    printf("\n");

    func(arr, 0, count);

    printf("after: ");
    print_int_array(arr, count);
    printf("\n\n");
}

void performance_sorting_test(const char   *name,
                              sorting_func  func)
{
    printf("performance test of %s sort\n", name);

    int count = 20000;
    int arr[count];

    for (int i = 0; i < count; i++)
        arr[i] = rand();

    time_t starttime = clock();

    func(arr, 0, count);

    time_t endtime = clock();
    time_t timeus = (endtime - starttime) * 1000000 / CLOCKS_PER_SEC;

    printf("time: %luus\n\n", timeus);
}

int main()
{
    srand(clock());

    visual_sorting_test("bubble", bubble_sort);
    visual_sorting_test("insertion", insertion_sort);
    visual_sorting_test("merge", merge_sort);
    visual_sorting_test("quick", quick_sort);

    performance_sorting_test("bubble", bubble_sort);
    performance_sorting_test("insertion", insertion_sort);
    performance_sorting_test("merge", merge_sort);
    performance_sorting_test("quick", quick_sort);

    return 0;
}
