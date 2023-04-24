#include "watchdog_message_queue.h"

Queue *watchdog_message_queue;

static WatchdogMessage **copied_message;

void *copy_WatchdogMessage(void *input_message) {
    copied_message = realloc(NULL, sizeof(WatchdogMessage *));
    *copied_message = *(WatchdogMessage **)input_message;
    return copied_message;
}

void destroy_WatchdogMessage(void *message) {
    free(message);
}

Queue *CreateQueue_WatchdogMessage() {
    Queue *new_queue = CreateQueue(MAX_WATCHDOG_MESSAGE_LENGTH, 
            &copy_WatchdogMessage, &destroy_WatchdogMessage);
    return new_queue;
}

void DeleteQueue_WatchdogMessage() {
    if (watchdog_message_queue->current_length != 0)
        free(copied_message);
    DeleteQueue(watchdog_message_queue);
}

void Enqueue_WatchdogMessage(WatchdogMessage *message) {
    Enqueue(watchdog_message_queue, &message);
}

void Dequeue_WatchdogMessage() {
    Dequeue(watchdog_message_queue);
}

WatchdogMessage *Front_WatchdogMessage() {
    if (watchdog_message_queue->current_length > 0) {
        WatchdogMessage **message = Front(watchdog_message_queue);
        return *message;
    }
    return NULL;
}
