
#include <stdio.h>
#include "inc/sort.h"

#define MERGESORT_TEST 1
#define HEAPSORT_TEST  2
#define QUICKSORT_TEST 3

#define SORT_TEST QUICKSORT_TEST

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

#if (SORT_TEST == MERGESORT_TEST)
    mergesort(array,0,n-1);
#endif

#if (SORT_TEST == HEAPSORT_TEST)
    heapsort(array,n);
#endif    

#if (SORT_TEST == QUICKSORT_TEST)
    quicksort(array,0,n-1);
#endif

    print_array(array, n);

    return 0;
}