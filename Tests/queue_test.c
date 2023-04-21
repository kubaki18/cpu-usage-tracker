#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../Queue/queue.h"
#include "../Queue/float_queue.h"
#include "../Queue/cpu_snapshot_queue.h"

int TestFloatQueue() {
    float_queue = CreateQueue_Float();
    float *tab;
    tab = malloc(sizeof(*tab) * 3);
    tab[0] = 1.25;
    tab[1] = 9999999999.9999999;
    tab[2] = 255;
    Enqueue_Float(tab);
    sem_post(float_queue->sem_full);
    for (int i = 0; i < 6; i++)
        Enqueue_Float(tab);
    if (float_queue->current_length > 5) {
        return 1;
    }
    if (Front_Float()[0] != 1.25)
        return 2;
    sem_post(float_queue->sem_empty);
    for (int i = 0; i < 6; i++)
        Dequeue_Float();
    if (Front_Float() != NULL)
        return 3;
    DeleteQueue_Float();
    return 0;
}

int TestCPUSnapshotQueue() {
    cpu_snapshot_queue = CreateQueue_CPUSnapshot();
    CoreTimes *times;
    times = malloc(sizeof(*times));
    times->user = 100;
    times->nice = 200;
    times->system = 300;
    times->idle = 400;
    times->iowait = 500;
    times->irq = 600;
    times->softirq = 700;
    times->steal = 800;
    Enqueue_CPUSnapshot(times);
    sem_post(cpu_snapshot_queue->sem_full);
    for (int i = 0; i < 6; i++)
        Enqueue_CPUSnapshot(times);
    if (cpu_snapshot_queue->current_length > 5) {
        return 1;
    }
    if (Front_CPUSnapshot()->user != 100)
        return 2;
    sem_post(cpu_snapshot_queue->sem_empty);
    for (int i = 0; i < 6; i++)
        Dequeue_CPUSnapshot();
    if (Front_CPUSnapshot() != NULL)
        return 3;
    DeleteQueue_CPUSnapshot();
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        return 1;
    }
    switch (atoi(argv[1])) {
        case 1:
            return TestFloatQueue();
        case 2:
            return TestCPUSnapshotQueue();
        default:
            break;
    }
    return 1;
}
