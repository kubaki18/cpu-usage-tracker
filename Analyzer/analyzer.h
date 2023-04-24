#ifndef ANALYZER_H
#define ANALYZER_H

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "cpu_snapshot_queue.h"
#include "float_queue.h"
#include "watchdog_message_queue.h"
#include "cpu_info.h"

extern volatile bool analyzer_running;

void *InitAnalyzer(void *);

#endif
