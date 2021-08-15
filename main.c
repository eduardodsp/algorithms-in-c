
#include <stdio.h>
#include "inc/sort.h"
#include "inc/matrix.h"
#include "inc/majority.h"

#define NO_TEST             0
#define MERGESORT_TEST      1
#define HEAPSORT_TEST       2
#define QUICKSORT_TEST      3

#define DETERMINANT_TEST    4 
#define MAJORITY_TEST       5

#define TEST MAJORITY_TEST

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

    int array[] = {2,6,2,1,9,2,6,4,6,2,6,2,2,11,2,2,2};
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

#if (TEST == MAJORITY_TEST)
    int major = majority(array,0,n-1);
        printf("%d is the majority\n", major);
#endif


    return 0;
}