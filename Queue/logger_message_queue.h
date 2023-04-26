#ifndef LOGGER_MESSAGE_QUEUE_H
#define LOGGER_MESSAGE_QUEUE_H

#include <assert.h>

#include "queue.h"

#define MAX_LOGGER_MESSAGE_LENGTH 10

typedef struct {
    char context[1024];
} LoggerMessage;

extern Queue *logger_message_queue;

void *copy_LoggerMessage(void *);
void destroy_LoggerMessage(void *);
Queue *CreateQueue_LoggerMessage(void);
void DeleteQueue_LoggerMessage(void);
void Enqueue_LoggerMessage(LoggerMessage *);
void Dequeue_LoggerMessage(void);
LoggerMessage *Front_LoggerMessage(void);

#endif
