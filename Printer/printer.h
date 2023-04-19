#ifndef PRINTER_H
#define PRINTER_H

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "float_queue.h"
#include "cpu_info.h"

extern bool printer_running;

void *InitPrinter(void *);

#endif
