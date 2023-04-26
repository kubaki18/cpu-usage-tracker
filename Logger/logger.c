#include "logger.h"
#include <stdio.h>

volatile bool logger_running = true;

void *InitLogger(void *attr) {
    LoggerMessage *message = NULL;
    FILE *output_file;
    assert(NULL == attr);
    output_file = fopen(LOGGER_FILE_NAME, "w");
    while (logger_running) {
        message = Front_LoggerMessage();
        if (NULL == message) {
            usleep(100000);
            continue;
        }
        Dequeue_LoggerMessage();
        fputs(message->context, output_file);
    }
    fclose(output_file);
    return NULL;
}
