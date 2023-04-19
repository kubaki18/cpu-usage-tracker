#include "string_queue.h"

Queue *string_queue;

static char **copied_string;

void *copy_String(void *input_string) {
    copied_string = realloc(NULL, sizeof(char *));
    *copied_string = *(char **)input_string;
    return copied_string;
}

void destroy_String(void *string) {
    free(string);
}

Queue *CreateQueue_String() {
    Queue *new_queue = CreateQueue(MAX_STRING_QUEUE_LENGTH, 
            &copy_String, &destroy_String);
    return new_queue;
}

void DeleteQueue_String() {
    DeleteQueue(string_queue);
    free(copied_string);
}

void Enqueue_String(char *input_string) {
    Enqueue(string_queue, &input_string);
}

void Dequeue_String() {
    Dequeue(string_queue);
}

char *Front_String() {
    char **string = Front(string_queue);
    return *string;
}
