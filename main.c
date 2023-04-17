#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "cpu_info.h"
#include "cpu_snapshot_queue.h"
#include "reader.h"


int main(void) {
    pthread_t reader;

    cpu_snapshot_queue = CreateQueue_CPUSnapshot();
    cpu_core_count = CountCPUCores();

    pthread_create(&reader, NULL, &InitReader, NULL);
    pthread_join(reader, NULL);

    usleep(500);

    PrintCores(Front_CPUSnapshot());

    DeleteQueue(cpu_snapshot_queue);
    return 0;
}
