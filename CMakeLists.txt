cmake_minimum_required(VERSION 3.14)
project(SEMPALAVRAS)
set (CMAKE_CXX_STANDARD 17)
set(INPUT_DIR "${PROJECT_SOURCE_DIR}/input/")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/output/")

option(CPU_TIME  "Enable cputime build" ON)

configure_file(${PROJECT_SOURCE_DIR}/sempalavras/config.h.in ${PROJECT_SOURCE_DIR}/sempalavras/include/config.h) 
include_directories(${PROJECT_SOURCE_DIR}/sempalavras/include)

enable_testing()
add_subdirectory(sempalavras)
add_subdirectory(tests)

add_test(
    NAME testeImportacao
    COMMAND $<TARGET_FILE:test1>
    )

add_test(
    NAME testeInsercao
    COMMAND $<TARGET_FILE:test2>
    )

add_test(
    NAME testeRemocao
    COMMAND $<TARGET_FILE:test3>
    )

add_test(
    NAME testeColisoes
    COMMAND $<TARGET_FILE:test4>
    )

add_test(
    NAME testeHash
    COMMAND $<TARGET_FILE:test5>
    )

add_test(
    NAME comparaSort
    COMMAND $<TARGET_FILE:test6>
    )

add_test(
    NAME cinquentaPalavras
    COMMAND $<TARGET_FILE:test1000>
    )