#include "cpu_snapshot_queue.h"

Queue *cpu_snapshot_queue;

static CoreTimes *copied_snapshot;

void *copy_CPUSnapshot(void *input_snapshot) {
    copied_snapshot = realloc(NULL, sizeof(*copied_snapshot));
    *copied_snapshot = *(CoreTimes *)input_snapshot;
    return copied_snapshot;
}

void destroy_CPUSnapshot(void *snapshot) {
    free(snapshot);
}

Queue *CreateQueue_CPUSnapshot() {
    Queue *new_queue = CreateQueue(MAX_CPU_CORES_QUEUE_LENGTH, 
            &copy_CPUSnapshot, &destroy_CPUSnapshot);
    return new_queue;
}

void DeleteQueue_CPUSnapshot() {
    DeleteQueue(cpu_snapshot_queue);
    free(copied_snapshot);
}

void Enqueue_CPUSnapshot(CoreTimes snapshot) {
    Enqueue(cpu_snapshot_queue, &snapshot);
}

void Dequeue_CPUSnapshot() {
    Dequeue(cpu_snapshot_queue);
}

CoreTimes *Front_CPUSnapshot() {
    CoreTimes *times = Front(cpu_snapshot_queue);
    return times;
}
