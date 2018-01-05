cmake_minimum_required (VERSION 2.6)
set(PROJECT test_fork)
set(CMAKE_C_FLAGS "-std=c99 -Wall -O3 -D_POSIX_C_SOURCE")

set(SOURCES main.c)

add_executable(${PROJECT} ${SOURCES})