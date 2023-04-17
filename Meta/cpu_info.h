#ifndef CPU_INFO_H
#define CPU_INFO_H 

#define BUFFER_SIZE 4096

typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
} CoreTimes;

extern unsigned int cpu_core_count;

#endif
