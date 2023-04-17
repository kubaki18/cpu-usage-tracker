#ifndef CPU_CORES_QUEUE_H
#define CPU_CORES_QUEUE_H

#include <assert.h>

#include "cpu_info.h"
#include "queue.h"

#define MAX_CPU_CORES_QUEUE_LENGTH 5

extern Queue *cpu_snapshot_queue;

void *copy_CPUSnapshot(void *);
void destroy_CPUSnapshot(void *);
Queue *CreateQueue_CPUSnapshot();
void DeleteQueue_CPUSnapshot(void);
void Enqueue_CPUSnapshot(CoreTimes);
void Dequeue_CPUSnapshot(void);
CoreTimes *Front_CPUSnapshot(void);

#endif
