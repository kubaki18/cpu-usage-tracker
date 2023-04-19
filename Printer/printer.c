#include "printer.h"

bool printer_running = true;

void *InitPrinter(void *attr) {
    assert(NULL == attr);
    float *percentage;

    while (printer_running) {
        printf("\033c");
        percentage = Front_Float();
        if (percentage == NULL) {
            usleep(100000);
            continue;
        }
        Dequeue_Float();

        for (unsigned int i = 0; i < cpu_core_count; i++) {
            printf("[ CPU%d - %.2f%% ]", i, percentage[i]);
        }
        printf("\n");
    }

    return NULL;
}
