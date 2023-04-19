#include "queue.h"

Queue *CreateQueue(unsigned int max_length, 
        void *(*copy)(void *), 
        void (*destroy)(void *)) {
    Queue *new_queue;
    new_queue = malloc(sizeof(*new_queue));

    new_queue->max_length = max_length;
    new_queue->current_length = 0;
    new_queue->front = 0;
    new_queue->rear = max_length - 1;

    new_queue->sem_full = malloc(sizeof(*new_queue->sem_full));
    new_queue->sem_empty = malloc(sizeof(*new_queue->sem_empty));


    sem_init(new_queue->sem_full, 0, max_length);
    sem_init(new_queue->sem_empty, 0, 0);

    new_queue->entries = malloc(sizeof(*new_queue->entries) * max_length);

    new_queue->copy = copy;
    new_queue->destroy = destroy;

    return new_queue;
}

void DeleteQueue(Queue * queue) {
    sem_destroy(queue->sem_full);
    sem_destroy(queue->sem_empty);
    free(queue->entries);
    free(queue);
}

void Enqueue(Queue *queue, void *entry) {
    sem_wait(queue->sem_full);
    if (queue->current_length != queue->max_length) {
        queue->current_length++;
        queue->rear++;
        if (queue->rear == queue->max_length) {
            queue->rear = 0;
        }
        queue->entries[queue->rear] = queue->copy(entry);
        sem_post(queue->sem_empty);
    } else {
        sem_post(queue->sem_full);
    }
}

void Dequeue(Queue *queue) {
    sem_wait(queue->sem_empty);
    if (queue->current_length != 0) {
        queue->destroy(queue->entries[queue->front]);
        queue->current_length--;
        queue->front++;
        if (queue->front == queue->max_length) {
            queue->front = 0;
        }
        sem_post(queue->sem_full);
    } else {
        sem_post(queue->sem_empty);
    }
}

void *Front(Queue *queue) {
    if (queue->current_length == 0) {
        return NULL;
    }
    return queue->entries[queue->front];
}
