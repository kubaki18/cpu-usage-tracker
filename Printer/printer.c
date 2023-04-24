#include "printer.h"

volatile bool printer_running = true;

void *InitPrinter(void *attr) {
    assert(NULL == attr);
    float *percentage;

    WatchdogMessage *message = malloc(sizeof(*message));
    message->threadID = PRINTER_THREAD_ID;

    while (printer_running) {
        // Clear the screen
        printf("\033c");
        percentage = Front_Float();
        if (percentage == NULL) {
            usleep(100000);
            continue;
        }
        Dequeue_Float();

        for (unsigned int i = 0; i < cpu_core_count; i++) {
            printf("[ CPU%d - %.2f%% ]", i, percentage[i] * 100);
        }
        printf("\n");
        Enqueue_WatchdogMessage(message);
    }

    free(percentage);
    free(message);
    return NULL;
}
