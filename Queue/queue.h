#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <semaphore.h>

#include "cpu_info.h"

typedef struct {
    unsigned int max_length;
    unsigned int current_length;
    unsigned int rear;
    unsigned int front;
    sem_t *sem_full;
    sem_t *sem_empty;
    void **entries;
    void *(*copy)(void *);
    void (*destroy)(void *);
} Queue;

Queue * CreateQueue(unsigned int max_length, void *(*copy)(void *), void (*destroy)(void *));
void DeleteQueue(Queue *);
void Enqueue(Queue *, void *);
void Dequeue(Queue *);
void *Front(Queue *);

#endif
