#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "cpu_info.h"
#include "cpu_snapshot_queue.h"
#include "float_queue.h"
#include "watchdog_message_queue.h"
#include "queue.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "watchdog.h"


int main(void) {
    pthread_t reader, analyzer, printer, watchdog;

    cpu_core_count = CountCPUCores();
    cpu_snapshot_queue = CreateQueue_CPUSnapshot();
    float_queue = CreateQueue_Float();
    watchdog_message_queue = CreateQueue_WatchdogMessage();


    pthread_create(&reader, NULL, &InitReader, NULL);
    pthread_create(&analyzer, NULL, &InitAnalyzer, NULL);
    pthread_create(&printer, NULL, &InitPrinter, NULL);
    pthread_create(&watchdog, NULL, &InitWatchdog, NULL);

    pthread_join(watchdog, NULL);

    DeleteQueue_CPUSnapshot();
    DeleteQueue_Float();
    return 0;
}
