/**
 * @file    sort.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    24-07-2021
 *
 */

#ifndef _SORT_H_
#define _SORT_H_

#include <stdint.h>

/**
 * @brief Recursively sort an array in ascending order with Θ(nlogn) time complexity, where n = r-p+1 
 * 
 * @param a array to be sorted
 * @param p first index of array to be sorted
 * @param r last index of array to be sorted
 */
void mergesort(int* arr,int p,int r);

/**
 * @brief Recursively sort an array in ascending order with Θ(nlogn) time complexity
 *        using a heap data structure
 * 
 * @param a pointer to array to be sorted
 * @param n size of the array to be sorted
 */
void heapsort(int* a, int n);


/**
 * @brief Recursively sort an array in ascending order with 
 *        average time complexity Θ(nlogn) and worst case of Θ(n²)
 * 
 * @param p first index of array to be sorted
 * @param r last index of array to be sorted
 */
void quicksort(int* a, int p, int r);
#endif