/**
 * @file    majority.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    26-07-2021
 *
 */

#ifndef _MAJORITY_H_
#define _MAJORITY_H_

#include <stdbool.h>

/**
 * @brief Recursively find a majority element within sub-array a[p,..,r]
 * 
 * @param a Poninter to sub-array
 * @param p Index of the first element of sub-array
 * @param r Index of the last element of sub-array
 * @return index of the majority element
 */
int majority(int* a, int p, int r);

#endif