/**
 * @file    heapsort.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    25-07-2021
 *
 */

#include <stdlib.h>

/**
 * @brief Corrects a violation of max heap where a child node 
 *        has bigger value than a parent node
 * 
 * @param a pointer to max heap array 
 * @param n heap size
 * @param i parent node index
 */
static
void fix_max_heap(int* a, int n, int i)
{
    int l = 2*i;
    int r = 2*i + 1;
    int max = i;

    if(l < n && a[l] > a[i])
        max = l;
    
    if(r < n && a[r] > a[max])
        max = r;
    
    if(max == i)
        return;

    register int aux = a[i];
    a[i] = a[max];
    a[max] = aux;

    fix_max_heap(a, n, max);
}

/**
 * @brief Transform an array into a max heap
 * 
 * @param a pointer to array
 * @param n size of array
 */
static
void build_max_heap(int* a, int n)
{
    for(int i=n/2; i >= 0; i--)
    {
        fix_max_heap(a,n,i);
    }
}

/**
 * @brief Recursively sort an array in ascending order with Θ(nlogn) time complexity
 *        using a heap data structure
 * 
 * @param a pointer to array to be sorted
 * @param n size of the array to be sorted
 */
void heapsort(int* a, int n)
{
    int aux;

    build_max_heap(a,n);

    for (int i=n-1; i > 0; i--)
    {
        aux = a[0];
        a[0] = a[i];
        a[i] = aux;
        fix_max_heap(a,i,0);
    }
}