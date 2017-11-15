#include <iostream>
#include <vector>

#include "utils.h"

using value_type = unsigned;
using iterator_type = typename std::vector<value_type>::iterator;
using sorting_func = void (*)(iterator_type, iterator_type);

bool compare(value_type p, value_type q)
{
    return p < q;
}

void bubble_sort(iterator_type begin,
                 iterator_type end)
{
    bool updated;

    do {
        updated = false;

        for (auto it = begin + 1; it != end; it++)
        {
            auto pr = it - 1;

            if (compare(*it, *pr))
            {
                std::swap(*it, *pr);
                updated = true;
            }
        }
    } while (updated);
}

void merge_sort(iterator_type begin,
                iterator_type end)
{
    auto count = std::distance(begin, end);

    if (count < 2)
        // array is already sorted
        return;

    // find the center iterator
    auto center = begin + count / 2;

    // go forward
    merge_sort(begin, center);
    merge_sort(center, end);

    // create iterators with limits for both subarrays
    auto left_it = begin;
    auto left_end = center;
    auto right_it = center;
    auto right_end = end;

    // create temporary buffer for merging
    std::vector<value_type> buff;

    // iterate over values until there are values
    // on both sides; take the less one and push it 
    // to the buffer
    while (left_it != left_end and right_it != right_end)
    {
        if (compare(*left_it, *right_it))
            buff.push_back(*left_it++);
        else
            buff.push_back(*right_it++);
    }

    // take remaining values from left or right side, if any
    while (left_it != left_end)
        buff.push_back(*left_it++);

    while (right_it != right_end)
        buff.push_back(*right_it++);

    // copy the buffer to the original array
    std::copy(buff.begin(), buff.end(), begin);
}

void quick_sort(iterator_type begin,
                iterator_type end)
{
    auto count = std::distance(begin, end);

    if (count < 2)
        // array is already sorted
        return;

    // find the number of elements less than pivot
    int lesscnt = 0;

    for (auto it = begin; it != end; it++)
        if (compare(*it, *begin))
            lesscnt++;

    // make pivot iterator and swap its value with first element
    auto pivot_it = begin + lesscnt;

    std::swap(*begin, *pivot_it);

    // there are two helper iterators, first for the left
    // subarray and second for the right one
    auto right_it = pivot_it + 1;

    for (auto left_it = begin; left_it != pivot_it; left_it++)
    {
        // check if pivot value is smaller than left one
        if (compare(*pivot_it, *left_it))
        {
            // skip all values greater than pivot
            while (compare(*pivot_it, *right_it))
                right_it++;

            std::swap(*left_it, *right_it);
        }
    }

    // go forward, excluding pivot item
    quick_sort(begin, pivot_it);
    quick_sort(pivot_it + 1, end);
}

void visual_sorting_test(const std::string &name,
                         sorting_func func)
{
    std::cout << "visual test of " << name << " sort" << std::endl;

    std::vector<value_type> vec;

    for (int i = 0; i < 16; i++)
        vec.push_back(rand() % 90 + 10);

    std::cout << "before: " << vec << std::endl;

    func(vec.begin(), vec.end());

    std::cout << "after: " << vec << std::endl << std::endl;
}

void performance_sorting_test(const std::string &name,
                              sorting_func func)
{
    std::cout << "performance test of " << name << " sort" << std::endl;

    std::vector<value_type> vec;

    for (int i = 0; i < 5000; i++)
        vec.push_back(rand());

    auto starttime = clock();

    func(vec.begin(), vec.end());

    auto endtime = clock();

    auto timems = (endtime - starttime) * 1000 / CLOCKS_PER_SEC;

    std::cout << "time: " << timems << "ms" << std::endl;
}

int main()
{
    visual_sorting_test("bubble", bubble_sort);
    visual_sorting_test("merge", merge_sort);
    visual_sorting_test("quick", quick_sort);

    performance_sorting_test("bubble", bubble_sort);
    performance_sorting_test("merge", merge_sort);
    performance_sorting_test("quick", quick_sort);

    return 0;
}
