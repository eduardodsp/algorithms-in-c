/**
 * @file    mergesort.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    24-07-2021
 *
 */

#include <stdlib.h>


/**
 * @brief Merge two ordered sub-arrays within an array.
 * 
 * @param a array containing the two ordered sub-arrays to be merged
 * @param p first index of left most sub-array
 * @param q last index of left most sub-array
 * @param r last index of right most sub-array
 */
static
void merge(int* a, int p,int q,int r)
{

    int i, j, k;
 
    int* b = malloc ((r-p+1) * sizeof (int));

    //take the first ordered sub-array a[p,...,q]
    for(k=p, i=0; k < q+1; k++)
        b[i++] = a[k];
    
    //we invert the second ordered sub-array, a[q+1,...,r], to 
    //avoid the need of sentinel value
    for(k=r; k > q; k--)
        b[i++] = a[k];
        
    //merge    
    for (k=p, i=0, j=r-p; k <= r; k++)
    {
        if(b[i] < b[j])
            a[k] = b[i++];
        else
            a[k] = b[j--]; 
    }

    free(b);
}

/**
 * @brief Recursively sort an array in ascending order with Θ(nlogn) time complexity, where n = r-p+1 
 * 
 * @param a array to be sorted
 * @param p first index of array to be sorted
 * @param r last index of array to be sorted
 */
void mergesort(int* a, int p, int r)
{
    if(a == NULL)
        return;

    if(p < r)
    {
        int q = (r + p)/2;      //Θ(k), k is constant 
        mergesort(a,p,q);       //T(n/2)
        mergesort(a, q+1,r);    //T(n/2)
        merge(a,p,q,r);         //Θ(n)
        
        //T(n) = 2T(n/2) + Θ(n) + Θ(k)
    }
}