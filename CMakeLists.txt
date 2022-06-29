cmake_minimum_required(VERSION 3.14)
project(SEMPALAVRAS)
set (CMAKE_CXX_STANDARD 17)
set(INPUT_DIR "${PROJECT_SOURCE_DIR}/input/")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/output/")

option(CPU_TIME  "Enable cputime build" ON)

configure_file(${PROJECT_SOURCE_DIR}/estruturas/config.h.in ${PROJECT_SOURCE_DIR}/estruturas/include/config.h) 
include_directories(${PROJECT_SOURCE_DIR}/estruturas/include)

enable_testing()
add_subdirectory(estruturas)
add_subdirectory(tests)

add_test(
    NAME SplayTree
    COMMAND $<TARGET_FILE:splay>
    )