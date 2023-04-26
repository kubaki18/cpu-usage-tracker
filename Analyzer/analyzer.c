#include "analyzer.h"

volatile bool analyzer_running = true;

void *InitAnalyzer(void *attr) {
    CoreTimes *times;
    
    unsigned long long idle[cpu_core_count], non_idle[cpu_core_count];
    unsigned long long new_idle[cpu_core_count], new_non_idle[cpu_core_count];
    unsigned long long idle_diff[cpu_core_count], non_idle_diff[cpu_core_count];
    float *percentage;

    bool first_iteration = true;

    LoggerMessage log_message;

    WatchdogMessage *message = malloc(sizeof(*message));
    message->threadID = ANALYZER_THREAD_ID;

    assert(NULL == attr);

    times = malloc(sizeof(CoreTimes) * cpu_core_count);
    percentage = malloc(sizeof(*percentage) * cpu_core_count);

    strcpy(log_message.context, "Analyzer: Entering while loop\n");
    Enqueue_LoggerMessage(&log_message);

    while(analyzer_running) {
        strcpy(log_message.context, "Analyzer: Reading from Queue...\n");
        Enqueue_LoggerMessage(&log_message);
        times = Front_CPUSnapshot();
        if (times == NULL) {
            usleep(100000);
            continue;
        }
        strcpy(log_message.context, "Analyzer: Success!\n");
        Enqueue_LoggerMessage(&log_message);
        Dequeue_CPUSnapshot();

        for (unsigned int i = 0; i < cpu_core_count; i++) {
            new_idle[i] = times[i].idle + times[i].iowait;
            new_non_idle[i] = times[i].user + times[i].nice + times[i].system + times[i].irq + times[i].softirq + times[i].steal;
        }

        if (first_iteration) {
            for (unsigned int i = 0; i < cpu_core_count; i++) {
                idle[i] = new_idle[i];
                non_idle[i] = new_non_idle[i];
            }
            first_iteration = false;
            continue;
        }

        for (unsigned int i = 0; i < cpu_core_count; i++) {
            idle_diff[i] = new_idle[i] - idle[i];
            non_idle_diff[i] = new_non_idle[i] - non_idle[i];
            percentage[i] = (float)non_idle_diff[i] / (idle_diff[i] + non_idle_diff[i]);
        }

        strcpy(log_message.context, "Analyzer: Enqueuing Float array!\n");
        Enqueue_LoggerMessage(&log_message);
        Enqueue_Float(percentage);

        strcpy(log_message.context, "Analyzer: Enqueuing Watchdog Message\n");
        Enqueue_LoggerMessage(&log_message);
        Enqueue_WatchdogMessage(message);
    }


    strcpy(log_message.context, "Analyzer: Freeing pointers\n");
    Enqueue_LoggerMessage(&log_message);
    free(times);
    free(message);
    return NULL;
}
