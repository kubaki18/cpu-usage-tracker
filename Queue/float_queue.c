#include "float_queue.h"

Queue *float_queue;

static float **copied_float;

void *copy_Float(void *input) {
    copied_float = realloc(NULL, sizeof(float *));
    *copied_float = *(float **)input;
    return copied_float;
}

void destroy_Float(void *target) {
    free(target);
}

Queue *CreateQueue_Float() {
    Queue *new_queue = CreateQueue(MAX_FLOAT_QUEUE_LENGTH, 
            &copy_Float, &destroy_Float);
    return new_queue;
}

void DeleteQueue_Float() {
    DeleteQueue(float_queue);
    free(copied_float);
}

void Enqueue_Float(float *input) {
    Enqueue(float_queue, &input);
}

void Dequeue_Float() {
    Dequeue(float_queue);
}

float *Front_Float() {
    float *front = Front(float_queue);
    return front;
}
