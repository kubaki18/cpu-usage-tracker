#ifndef STRING_QUEUE_H
#define STRING_QUEUE_H

#include "queue.h"

#define MAX_STRING_QUEUE_LENGTH 5

extern Queue *string_queue;

void *copy_String(void *);
void destroy_String(void *);
Queue *CreateQueue_String();
void DeleteQueue_String(void);
void Enqueue_String(char *);
void Dequeue_String(void);
char *Front_String(void);

#endif
