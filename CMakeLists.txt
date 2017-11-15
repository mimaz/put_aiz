cmake_minimum_required (VERSION 3.0)

project (put_aiz)

set (CMAKE_CXX_FLAGS "-Wall -std=c++17 -O0 -g")
set (CMAKE_EXE_LINKER_FLAGS "-lm")

add_executable (sorting.bin sorting.cpp)
