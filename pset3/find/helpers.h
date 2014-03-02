/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 * uses binary for recursion.
 */
bool search(int value, int values[], int n);

/**
 * Recursive Binary Search
 * adapted from the CS50 Short of the same name
 */
int binary(int key, int array[], int min, int max);

/**
 * Swaps two int values using pointers
 */
void swap(int* a, int* b);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);
