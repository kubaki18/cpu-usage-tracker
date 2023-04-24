#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

#include "printer.h"
#include "analyzer.h"
#include "reader.h"
#include "watchdog_message_queue.h"

void ShutDownThreads(void);
void *InitWatchdog(void *);

#endif
