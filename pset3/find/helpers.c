/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * uses binary for recursion.
 */
bool search(int value, int values[], int n)
{
    // validate input
    if (n <= 0)
    {
        return false;
    }
    // sorts values
    sort(values, n);

    // binary search, save as 'result'
    int result = binary(value, values, 0, n);
    if (result == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Recursive Binary Search
 * adapted from the CS50 Short of the same name
 */
int binary(int key, int array[], int min, int max)
{
    // for tracking on the stack
    int result;

    if (max < min)
    {
        return -1;
    }
    else
    {
        int midpoint = min + (max - min) / 2;

        if (array[midpoint] < key)
        {
            result = binary(key, array, midpoint + 1, max);
        }
        else if (array[midpoint] > key)
        {
            result = binary(key, array, min, midpoint - 1);
        }
        else
        {
            return midpoint;
        }
    }
    return result;
}

/**
 * Swaps two int values using pointers
 */
void swap(int* first, int* second)
{
    int tmp = *second;
    *second = *first;
    *first = tmp;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort
    int num_swaps;
    do
    {
        num_swaps = 0;
        for (int i = 0; i < n; i++)
        {
            // nxt is element after i
            int nxt = i + 1;
            if (values[i] > values[nxt])
            {
                swap(&values[i], &values[nxt]);
                num_swaps++;
            } 
        }
    }
    while (num_swaps != 0);    
    return;
}

