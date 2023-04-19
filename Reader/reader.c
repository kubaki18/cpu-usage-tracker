#include "reader.h"

bool reader_running = true;

void *InitReader(void *attr) {
    FILE *stat_file;
    char buffer[BUFFER_SIZE];
    CoreTimes *times;

    assert(NULL == attr);

    times = malloc(sizeof(CoreTimes) * cpu_core_count);

    while (reader_running) {
        stat_file = fopen(PATH_TO_STAT_FILE, "r");
        assert(NULL != stat_file);


        // Read the first line, which contains a summary of all cores' data, 
        // to avoid reading it as one of them
        fgets(buffer, BUFFER_SIZE, stat_file);

        // Iterate through all of the cores and assign relevant values to corresponding variables
        for (unsigned int i = 0; i < cpu_core_count; i++) {
            times[i] = ReadTimesForCurrentCore(stat_file);
        }

        Enqueue_CPUSnapshot(times);

        fclose(stat_file);
        printf("%llu\n", Front_CPUSnapshot()[0].user);
        usleep(100000);
    }

    free(times);
    return NULL;
}

unsigned int CountCPUCores(void) {
    FILE *stat_file;
    unsigned int count = 0;
    char buffer[BUFFER_SIZE];

    stat_file = fopen(PATH_TO_STAT_FILE, "r");
    assert(NULL != stat_file);

    // For each entry in the file, check if the line starts with "cpu", then increase the count
    while (fgets(buffer, BUFFER_SIZE, stat_file)) {
        if (0 == strncmp(buffer, "cpu", 3)) {
            count++;
        }
    }

    // Account for the first line of /stat/proc, which is a sum of data in all cores
    count--;
    assert(count > 0);

    fclose(stat_file);
    return count;
}

CoreTimes ReadTimesForCurrentCore(FILE *stat_file) {
    CoreTimes times;
    char buffer[BUFFER_SIZE];
    int status;

    fgets(buffer, BUFFER_SIZE, stat_file);
    status = sscanf(
        buffer, "cpu%*d %llu %llu %llu %llu %llu %llu %llu %llu", 
        &times.user,   &times.nice,   &times.system,     &times.idle, 
        &times.iowait, &times.irq,    &times.softirq,    &times.steal
    );

    // sscanf() will return number of assigned values, which in this case must always be 8 if the function call was successful
    assert(8 == status);
    return times;
}
