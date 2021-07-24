#ifndef _MERGESORT_H_
#define _MERGESORT_H_

/**
 * @file    mergesort.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    24-07-2021
 *
 */
#include <stdint.h>

/**
 * @brief Recursively sort an array in ascending order with Θ(nlogn) time complexity, where n = r-p+1 
 * 
 * @param a array to be sorted
 * @param p first index of array to be sorted
 * @param r last index of array to be sorted
 */
void mergesort(int* arr,int p,int r);

#endif