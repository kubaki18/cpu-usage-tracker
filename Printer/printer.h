#ifndef PRINTER_H
#define PRINTER_H

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "float_queue.h"
#include "cpu_info.h"
#include "watchdog_message_queue.h"
#include "logger_message_queue.h"

extern volatile bool printer_running;

void *InitPrinter(void *);

#endif
