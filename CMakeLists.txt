cmake_minimum_required(VERSION 3.0)

project(put_aiz)

set(CMAKE_C_FLAGS "-Wall -std=c11 -O2")
set(CMAKE_EXE_LINKER_FLAGS "-lm")

add_executable(sorting.bin sorting.c)
add_executable(bubble2d.bin bubble2d.c)
add_executable(graphrand.bin graphrand.c)
