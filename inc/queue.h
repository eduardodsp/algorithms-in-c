#include <stdlib.h>


typedef struct queue_s
{
    int size;
    int tail;
    int head;
    int ctr;

    int* ptr;
}queue_t;


void queue(queue_t* q, int size)
{
    if(q == NULL)
        return;

    q->ctr = 0;
    q->size = size;
    q->head = 0;
    q->tail = 0;

    q->ptr = (int*)malloc(size * sizeof(int));
}

void queue_delete(queue_t* q)
{
    if(q == NULL)
        return;

    free(q->ptr);
}

void enqueue(queue_t* q, int in)
{
    if(q == NULL)
        return;

    if(q->ctr == q->size)
        return;

    q->ptr[q->tail] = in;

    q->ctr++;

    q->tail = (q->tail + 1) % q->size;

}

void dequeue(queue_t* q, int* out)
{
    if(q == NULL)
        return;

    if(out == NULL)
        return;   

    if(!q->ctr)
        return;
     
     q->ctr--;

     *out = q->ptr[q->head];
     
     q->head = (q->head + 1) % q->size;


}