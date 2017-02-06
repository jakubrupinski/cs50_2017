/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include "helpers.h"

/**
 * Binary search for value in an array
 */
bool binary_search(int target, int values[], int starting_point, int ending_point);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if n (size) is non-positive - return false 
    if (n < 0)
    {
        return false;
    }
    
    /*
    // search linearly for value, if found return true
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    */
    
    // search binary for value, if found return true
    if (binary_search(value, values, 0, n))
    {
        return true;
    }
    else
    {
        // if not found - return false
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int 
        max_value = 0,
        i = 0;
        
    if (n == 1)
    {
        // eprintf("1-element list is already sorted!\n");
        return;
    }
    else if (n <= 0)
    {
        // eprintf("No elements to sort!\n");
        return;
    }
    
    // find biggest value in values array of size n
    while (i < n)
    {
        if (values[i] > max_value)
        {
            max_value = values[i];
        }
        i++;
    }
    
    // initialize counting_array with index numbers from zero up to (including) max_value, each has value = 0
    int counting_array[max_value + 1];
        
    
    for (i = 0; i < max_value + 1; i++)
    {
        counting_array[i] = 0;
        // // eprintf("counting_array[%d] = %d\n", i, counting_array[i]);
    }
    
    // add 1 in counting_array for every occurence of number in values array 
    for (i = 0; i < n; i++)
    {
        // add 1 to current number's index in counting_array
        counting_array[values[i]]++;
        // eprintf("occurences of %d = %d times\n", values[i], counting_array[values[i]]);
    }

    // check every number in counting_array for positive values (occurences of number in values[])
    for (int i = 0, j = 0; i <= max_value; i++)
    {
        // if current number index is positive - keep assigning this smallest number as leftside sorted value in values[]
        while (counting_array[i] > 0)
        {
          values[j] = i;  
          // eprintf("sorted haystack[%d] = %d\n", j, values[j]);
          j++;
          counting_array[i]--;
        }
    }

    return;
}

/**
 * Binary search for target in an array
 */
bool binary_search(int target, int values[], int starting_point, int ending_point)
{
    int
    middle = (ending_point+starting_point)/2;
    // eprintf("Middle point of %d and %d = %d\n", starting_point, ending_point, middle);
    
    // SANITY CHECK - if starting point and ending point cross - target not found
    if (starting_point > ending_point)
    {
        // eprintf("Target not found in array\n");
        return false;
    }
    
    // if middle point equals target - return true
    if (values[middle] == target)
    {
        // eprintf("Middle point is the target(needle)!\n");
        return true;
    }
    else if(values[middle] > target)
    {
        // eprintf("Target %d is less than %d (middle point)!\n", target, values[middle]);
        ending_point = middle-1;
        return binary_search(target, values, starting_point, ending_point);
    }
    else if (values[middle] < target)
    {
        // eprintf("Target %d is more than %d (middle point)!\n", target, values[middle]);
        starting_point = middle + 1;
        return binary_search(target, values, starting_point, ending_point);
    }
    
    // THIS LINE BELOW IS GIVING THE WRONG OUTPUT!!!!!!!!
    return false;
}