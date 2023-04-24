#include "watchdog.h"
#include <time.h>

void ShutDownThreads(void) {
    printer_running = false;
    analyzer_running = false;
    reader_running = false;
}

void *InitWatchdog(void *attr) {
    clock_t seconds_t, printer_t = clock(), analyzer_t = clock(), reader_t = clock();
    char which_thread = 0;
    bool watchdog_running = true;
    assert(NULL == attr);
    while (watchdog_running) {
        usleep(100000);
        if (Front_WatchdogMessage() != NULL) {
            which_thread = Front_WatchdogMessage()->threadID;
            Dequeue_WatchdogMessage();
        } else {
            which_thread = 0;
        }
        switch (which_thread) {
            case 1:
                reader_t = clock();
                break;
            case 2:
                analyzer_t = clock();
                break;
            case 3:
                printer_t = clock();
                break;
            default:
                break;
        }
        seconds_t = clock();
        if ((seconds_t - reader_t) * 1000 / (double)CLOCKS_PER_SEC >= 2
                || (seconds_t - analyzer_t) * 1000 / (double)CLOCKS_PER_SEC >= 2
                || (seconds_t - printer_t) * 1000 / (double)CLOCKS_PER_SEC >= 2) {
            ShutDownThreads();
            watchdog_running = false;
        }
    }
    return NULL;
}
