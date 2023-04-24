#ifndef WATCHDOG_MESSAGE_QUEUE_H
#define WATCHDOG_MESSAGE_QUEUE_H

#include "queue.h"

#define MAX_WATCHDOG_MESSAGE_LENGTH 5

#define READER_THREAD_ID 1
#define ANALYZER_THREAD_ID 2
#define PRINTER_THREAD_ID 3

typedef struct {
    char threadID;
} WatchdogMessage;

extern Queue *watchdog_message_queue;

void *copy_WatchdogMessage(void *);
void destroy_WatchdogMessage(void *);
Queue *CreateQueue_WatchdogMessage(void);
void DeleteQueue_WatchdogMessage(void);
void Enqueue_WatchdogMessage(WatchdogMessage *);
void Dequeue_WatchdogMessage(void);
WatchdogMessage *Front_WatchdogMessage(void);

#endif
