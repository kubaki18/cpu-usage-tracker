#include "logger_message_queue.h"

Queue *logger_message_queue;

static LoggerMessage **copied_message;

void *copy_LoggerMessage(void *input_message) {
    copied_message = realloc(NULL, sizeof(LoggerMessage *));
    *copied_message = *(LoggerMessage **)input_message;
    return copied_message;
}

void destroy_LoggerMessage(void *message) {
    free(message);
}

Queue *CreateQueue_LoggerMessage() {
    Queue *new_queue = CreateQueue(MAX_LOGGER_MESSAGE_LENGTH, 
            &copy_LoggerMessage, &destroy_LoggerMessage);
    return new_queue;
}

void DeleteQueue_LoggerMessage() {
    if (logger_message_queue->current_length != 0)
        free(copied_message);
    DeleteQueue(logger_message_queue);
}

void Enqueue_LoggerMessage(LoggerMessage *message) {
    Enqueue(logger_message_queue, &message);
}

void Dequeue_LoggerMessage() {
    Dequeue(logger_message_queue);
}

LoggerMessage *Front_LoggerMessage() {
    if (logger_message_queue->current_length > 0) {
        LoggerMessage **message = Front(logger_message_queue);
        return *message;
    }
    return NULL;
}
