/**
 * @file    heap.c
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    15-08-2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/heap.h"



heap_t* min_heap(int size)
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    heap->size = size;
    heap->ctr = 0;
    heap->pair = (key_value_t*)malloc(size * sizeof(key_value_t));

    for(int i=0; i < size; i++)
    {
        heap->pair[i].value = INT_MAX;
        heap->pair[i].key = 0;
    }   

    return heap;

}

/**
 * @brief Corrects a violation of min heap where a child node 
 *        has smaller value than a parent node
 * 
 * @param a pointer to min heap array 
 * @param n heap size
 * @param i parent node index
 */
void min_heapify(heap_t* heap,int i)
{
    int l = 2*i;
    int r = 2*i + 1;
    int min = i;
    int n = heap->ctr;
    key_value_t* a = heap->pair;

    if(l < n && a[l].value < a[i].value)
        min = l;
    
    if(r < n && a[r].value < a[min].value)
        min = r;
    
    if(min == i)
        return;

    key_value_t aux = a[i];
    a[i] = a[min];
    a[min] = aux;

    min_heapify(heap, min);
}

void min_insert(heap_t* heap, int k, int v)
{
    key_value_t aux;

    if (heap->size == heap->ctr)
    {
        return;
    }
  
    heap->ctr++;
    int i = heap->ctr - 1;
    heap->pair[i].key = k;
    heap->pair[i].value = v;
    
    while (i != 0 && heap->pair[(i-1)/2].value > heap->pair[i].value)
    {
        aux = heap->pair[i];
        heap->pair[i] = heap->pair[(i-1)/2];
        heap->pair[(i-1)/2] = aux;

        i = (i-1)/2;
    }

}

void min_decrease_key(heap_t* heap, int k, int v)
{
    key_value_t aux;

    for(int i=0; i < heap->ctr; i++)
    {
        if(heap->pair[i].key == k)
        {
            heap->pair[i].value = v;
            while (i != 0 && heap->pair[(i-1)/2].value > heap->pair[i].value)
            {
                aux = heap->pair[i];
                heap->pair[i] = heap->pair[(i-1)/2];
                heap->pair[(i-1)/2] = aux;

                i = (i-1)/2;
            }
            return;
        }
    }
}

int extract_min(heap_t* heap, key_value_t* pair)
{
    if (heap->ctr <= 0)
        return 0;

    if (heap->ctr == 1)
    {
        heap->ctr--;
        *pair = heap->pair[0];
        return 1;
    }

    *pair = heap->pair[0];
    heap->pair[0] = heap->pair[heap->ctr-1];
    heap->ctr--;

    min_heapify(heap, 0);
  
    return 1;
}


void test_min_heap()
{
    heap_t* heap;
    key_value_t item;

    heap = min_heap(5);

    min_insert(heap, 0, 31);
    min_insert(heap, 1, 2);
    min_insert(heap, 2, 9);
    min_insert(heap, 3, 1);
    min_insert(heap, 4, 20);

    //extract_min(heap, &item);

    for(int i=0; i<heap->ctr; i++)
        printf("min: %d %d \n", heap->pair[i].key, heap->pair[i].value);

}

