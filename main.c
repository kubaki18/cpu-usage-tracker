#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "cpu_info.h"
#include "cpu_snapshot_queue.h"
#include "float_queue.h"
#include "queue.h"
#include "string_queue.h"
#include "reader.h"
#include "analyzer.h"


int main(void) {
    pthread_t reader, analyzer;

    cpu_core_count = CountCPUCores();
    cpu_snapshot_queue = CreateQueue_CPUSnapshot();
    float_queue = CreateQueue_Float();

    pthread_create(&reader, NULL, &InitReader, NULL);

    pthread_create(&analyzer, NULL, &InitAnalyzer, NULL);

    sleep(2);

    pthread_join(reader, NULL);
    pthread_join(analyzer, NULL);

    analyzer_running = reader_running = false;

    DeleteQueue_CPUSnapshot();
    DeleteQueue_Float();
    return 0;
}
