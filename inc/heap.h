/**
 * @file    heap.h
 * @authors Eduardo S. Pino (edsp)
 * @version 1.0
 * @date    15-08-2021
 *
 */
#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>

#define MIN_HEAP 0
#define MAX_HEAP 1

typedef struct key_value_s
{
    int key;
    int value;

}key_value_t;


typedef struct heap_s
{
    key_value_t *pair;
    int         size; 
    int         ctr;

}heap_t;


heap_t* min_heap(int size);

void min_heapify(heap_t* heap,int i);

void min_insert(heap_t* heap, int k, int v);

void min_decrease_key(heap_t* heap, int k, int v);

int extract_min(heap_t* heap, key_value_t* pair);

void test_min_heap();

#endif