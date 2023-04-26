#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

#include "printer.h"
#include "analyzer.h"
#include "reader.h"
#include "logger.h"
#include "watchdog_message_queue.h"
#include "logger_message_queue.h"

void ShutDownThreads(void);
void *InitWatchdog(void *);

#endif
