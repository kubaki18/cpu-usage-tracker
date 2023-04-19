#include "analyzer.h"
#include "cpu_info.h"

bool analyzer_running = true;

void *InitAnalyzer(void *attr) {
    CoreTimes *times;
    
    unsigned long long idle[cpu_core_count], non_idle[cpu_core_count];
    unsigned long long new_idle[cpu_core_count], new_non_idle[cpu_core_count];
    unsigned long long idle_diff[cpu_core_count], non_idle_diff[cpu_core_count];
    float percentage[cpu_core_count];

    bool first_iteration = true;

    assert(NULL == attr);

    times = malloc(sizeof(CoreTimes) * cpu_core_count);

    while(analyzer_running) {
        times = Front_CPUSnapshot();
        if (times == NULL) {
            usleep(10000);
            continue;
        }
        Dequeue_CPUSnapshot();

        printf("%llu\n", times[0].idle);
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

        Enqueue_Float(percentage);
    }

    return NULL;
}
