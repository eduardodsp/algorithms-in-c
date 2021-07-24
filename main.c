
#include <stdio.h>
#include "sort/mergesort.h"

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
    mergesort(array,0,n-1);
    print_array(array, n);

    return 0;
}