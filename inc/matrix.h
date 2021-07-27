
/**
 * @file    matrix.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    26-07-2021
 *
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdint.h>

/**
 * @brief Print a matrix from an array
 * 
 * @param a Pointer to C array containing the matrix
 * @param n Number of rows
 * @param m Number of columns
 */
void print_matrix(int* a, int n, int m);

/**
 * @brief Recursively calculate the determinant of an n x n square matrix.
 * 
 * @param a C Array containing the matrix
 * @param n Size of the square matrix
 * @return float determinante of a n x n matrix
 */
float det_sq_matrix(int* a, int n);

#endif //_MATRIX_H_
