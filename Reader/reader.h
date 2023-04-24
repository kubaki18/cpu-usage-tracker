#ifndef READER_H
#define READER_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "cpu_info.h"
#include "cpu_snapshot_queue.h"
#include "watchdog_message_queue.h"

#define PATH_TO_STAT_FILE "/proc/stat"

extern volatile bool reader_running;

unsigned int CountCPUCores(void);
void *InitReader(void *);
CoreTimes ReadTimesForCurrentCore(FILE *);

#endif
