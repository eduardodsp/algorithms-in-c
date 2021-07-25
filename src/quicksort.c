/**
 * @file    quicksort.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    25-07-2021
 *
 */

#include <stdlib.h>

/**
 * @brief Swaps 2 elements of an array
 * 
 * @param a array containing the elements to be swaped
 * @param i index of first element
 * @param j index of second element
 */
void swap(int* a, int i, int j)
{
    register int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

/**
 * @brief Partition an array between elements smaller and bigger 
 *        than an arbitrary pivot value within the array.
 * 
 * @param a Pointer to the array to be partitioned
 * @param p first index of array
 * @param r last index of array
 * @return the pivot new position
 */
static
int partition(int* a, int p, int r)
{
    int i, j;
    int q = a[r];

    for (i=p-1, j=p; j < r; j++)
    {
        if (a[j] < q)
        {
            i++;
            swap(a,j,i);
        }
    }

    swap(a, i+1, r);

    return i+1;
}

/**
 * @brief Partition an array between elements smaller and bigger 
 *        than an arbitrary pivot value within the array.
 * 
 * @param a Pointer to the array to be partitioned
 * @param p first index of array
 * @param r last index of array
 * @return the pivot new position
 */
static
int rand_partition(int* a, int p, int r)
{
    int i = rand() % (r-p) + p;

    swap(a,i,r);

    return partition(a,p,r);;
}

/**
 * @brief Recursively sort an array in ascending order with 
 *        average time complexity Θ(nlogn) and worst case of Θ(n²)
 * 
 * @param p first index of array to be sorted
 * @param r last index of array to be sorted
 */
void quicksort(int* a, int p, int r)
{
    if(p < r)
    {
        int q = rand_partition(a,p,r);
        quicksort(a,p, q-1);
        quicksort(a,q+1,r);
    }
}