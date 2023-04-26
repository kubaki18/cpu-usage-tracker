#include "printer.h"

volatile bool printer_running = true;

void *InitPrinter(void *attr) {
    assert(NULL == attr);
    float *percentage;

    LoggerMessage log_message;

    WatchdogMessage *message = malloc(sizeof(*message));
    message->threadID = PRINTER_THREAD_ID;

    strcpy(log_message.context, "Printer: Entering while loop\n");
    Enqueue_LoggerMessage(&log_message);
    while (printer_running) {
        // Clear the screen
        printf("\033c");
        strcpy(log_message.context, "Printer: Reading from Queue...\n");
        Enqueue_LoggerMessage(&log_message);
        percentage = Front_Float();
        if (percentage == NULL) {
            usleep(100000);
            continue;
        }
        strcpy(log_message.context, "Printer: Success!\n");
        Enqueue_LoggerMessage(&log_message);
        Dequeue_Float();

        strcpy(log_message.context, "Printer: Printing results\n");
        Enqueue_LoggerMessage(&log_message);
        for (unsigned int i = 0; i < cpu_core_count; i++) {
            printf("[ CPU%d - %.2f%% ]", i, percentage[i] * 100);
        }
        printf("\n");

        strcpy(log_message.context, "Printer: Enqueuing Watchdog Message\n");
        Enqueue_LoggerMessage(&log_message);
        Enqueue_WatchdogMessage(message);
    }

    strcpy(log_message.context, "Printer: Freeing pointers\n");
    Enqueue_LoggerMessage(&log_message);
    free(percentage);
    free(message);
    return NULL;
}
