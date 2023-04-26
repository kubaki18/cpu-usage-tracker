#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "logger_message_queue.h"

#define LOGGER_FILE_NAME "logs.txt"

extern volatile bool logger_running;

void *InitLogger(void *);

#endif
