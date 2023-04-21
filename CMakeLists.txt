cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)

project(CPUUsageTracker LANGUAGES C)

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Weverything)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra)
endif()

enable_testing()

add_executable(cut)
target_sources(cut PRIVATE main.c)


target_include_directories(cut PRIVATE Meta)
target_include_directories(cut PRIVATE Queue)
target_include_directories(cut PRIVATE Reader)
target_include_directories(cut PRIVATE Analyzer)
target_include_directories(cut PRIVATE Printer)

add_subdirectory(Meta)
add_subdirectory(Queue)
add_subdirectory(Reader)
add_subdirectory(Analyzer)
add_subdirectory(Printer)

add_subdirectory(Tests)

install(TARGETS cut)
