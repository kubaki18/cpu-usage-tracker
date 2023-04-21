add_library(CPUInfo cpu_info.c cpu_info.h)
target_link_libraries(cut PRIVATE CPUInfo)
