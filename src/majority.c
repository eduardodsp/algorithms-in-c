/**
 * @file    majority.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    24-07-2021
 *
 */

#include <stdlib.h>
#include <math.h>
#include "../inc/majority.h"

/**
 * @brief Recursively find a majority element within sub-array a[p,..,r]
 * 
 * @param a Poninter to sub-array
 * @param p Index of the first element of sub-array
 * @param r Index of the last element of sub-array
 * @return index of the majority element
 */
int majority(int* a, int p, int r)
{
    if(p == r)
        return a[p];
    
    int q = (r + p)/2;

    int e = majority(a,p,q);
    int d = majority(a,q+1,r);

    if(e == d)
        return e;
    
    int ctr_e, ctr_d;
    int i = p;
    for(ctr_e=0, ctr_d=0; i <= r; i++)
    {
        if(a[e] == a[i])
            ctr_e++;
        
        if(a[d] == a[i])
            ctr_d++;
    }
    if(ctr_e > ctr_d)
        return e;

    return d;
}
