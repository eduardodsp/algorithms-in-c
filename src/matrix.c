/**
 * @file matrix.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    26-07-2021
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief Print a matrix from an array
 * 
 * @param a Pointer to C array containing the matrix
 * @param n Number of rows
 * @param m Number of columns
 */
void print_matrix(int* a, int n, int m)
{
    for(int i=0; i < n; i++)
    {
        printf("| ");
        for(int j=0; j < m; j++)
        {
             printf("%2d ", *((a+i*n) + j));
        }
        printf(" | \n");
    }
}

/**
 * @brief Make a square submatrix from a source nxn matrix 
 *        by elimintaing 1 row and 1 column
 * 
 * @param dst Pointer to c array to store the new matrix
 * @param src Pointer to a c array containing the new matrix
 * @param n   Size of the source square matrix
 * @param r   Row to eliminate
 * @param c   Column to eliminate
 */
static
void sub_matrix(int* dst , int* src, int n, int r, int c)
{
    int i,j,x,y;
    int s = n-1;

    for(i=0,x=0; i < n; i++)
    {
        if(i != r)
        {
            for(j=0,y=0; j < n; j++)
            {
                if(j != c)
                    *((dst+x*s) + y++) = *((src+i*n) + j);                       
            }
            x++;
        }
    }
}

/**
 * @brief Recursively calculate the determinant of an n x n square matrix.
 * 
 * @param a C Array containing the matrix
 * @param n Size of the square matrix
 * @return float determinante of a n x n matrix
 */
float det_sq_matrix(int* a, int n)
{
    //base case is a 1x1 matrix where the determinante of matrix a is a[0][0]
    if(n == 1)
        return (float)*a;

    float  sum = 0.0;

    //make a c array to hold a (n-1)x(n-1) matrix
    int  b_size = pow(n-1,2);
    int* b = malloc ((b_size) * sizeof (int)); 

    //auxiliary variable to hold a[0][j]
    int a0j = 0;

    for (int j=0; j < n; j++)
    {
        sub_matrix(b,a,n,0,j);
        a0j = (*((a+0*n) + j));

        //recursively solve a smaller problem
        sum += pow(-1,2+j) * a0j * det_sq_matrix(b,n-1);
    }

    free(b);
    return sum;
}