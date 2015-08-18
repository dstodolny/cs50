/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdlib.h>
#include "helpers.h"

#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int array[], int n)
{
    return binarySearch(value, array, 0, n - 1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{      
    int count[n + 1];
    
    for (int i = 0; i < n + 1; i++)
        count[i] = 0;
 
    for (int i = 0; i < n + 1; i++)
        (count[values[i]])++;
 
    for (int i = 0, z = 0; i <= n; i++)  
        for(int j = 0; j < count[i]; j++)
            values[z++] = i;
}

/**
 * Swaps two values
 */
void swap(int *a, int *b)
{
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

/**
 * Search for value in an array using binary method
 */
bool binarySearch(int value, int values[], int left, int right)
{
    if (left > right)
    {
        return false;
    }

    int middle = (left + right) / 2;

    if (values[middle] < value)
    {
        return binarySearch(value, values, middle + 1, right); 
    }
    else if (values[middle] > value)
    {
        return binarySearch(value, values, left, middle - 1);
    }
    else
    {
        return true;
    }
}
