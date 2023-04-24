#ifndef FLOAT_QUEUE_H 
#define FLOAT_QUEUE_H

#include "queue.h"

#define MAX_FLOAT_QUEUE_LENGTH 5

extern Queue *float_queue;

void *copy_Float(void *);
void destroy_Float(void *);
Queue *CreateQueue_Float(void);
void DeleteQueue_Float(void);
void Enqueue_Float(float*);
void Dequeue_Float(void);
float *Front_Float(void);

#endif
