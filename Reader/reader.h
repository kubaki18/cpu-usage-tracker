#ifndef READER_H
#define READER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu_info.h"
#include "cpu_snapshot_queue.h"

#define PATH_TO_STAT_FILE "/proc/stat"

unsigned int CountCPUCores(void);
void *InitReader(void *);
CoreTimes ReadTimesForCurrentCore(FILE *);
void PrintCores(CoreTimes *);

#endif
