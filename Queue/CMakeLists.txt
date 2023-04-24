add_library(Queue queue.c queue.h cpu_snapshot_queue.c cpu_snapshot_queue.h float_queue.c float_queue.h watchdog_message_queue.c watchdog_message_queue.h)
target_link_libraries(Queue PRIVATE CPUInfo)
target_link_libraries(cut PRIVATE Queue)
