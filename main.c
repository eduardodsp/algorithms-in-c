
#include <stdio.h>
#include "inc/sort.h"
#include "inc/matrix.h"

#define NO_TEST             0
#define MERGESORT_TEST      1
#define HEAPSORT_TEST       2
#define QUICKSORT_TEST      3

#define DETERMINANT_TEST    4 

#define TEST DETERMINANT_TEST

void print_array(int* arr, int size)
{
    for (int i=0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
     printf("\n");
}

int main ()
{

    int array[] = {8,3,7,6,9,1,5,4,11,25,0}; 
    size_t n = sizeof(array)/sizeof(array[0]);

#if (TEST == MERGESORT_TEST)
    mergesort(array,0,n-1);
    print_array(array, n);
#endif

#if (TEST == HEAPSORT_TEST)
    heapsort(array,n);
    print_array(array, n);
#endif    

#if (TEST == QUICKSORT_TEST)
    quicksort(array,0,n-1);
    print_array(array, n);
#endif

#if (TEST == DETERMINANT_TEST)
    int matrix[] = {8,3,7,6,9,1,5,4,11}; 
    float det = det_sq_matrix(matrix,3);
    print_matrix(matrix,3,3);
    printf("det = %f \n", det);
#endif


    return 0;
}