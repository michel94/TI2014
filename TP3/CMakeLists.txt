project (DES)
cmake_minimum_required (VERSION 2.8)

set (CMAKE_C_FLAGS "-Wall")

add_library (DES DES.c)

add_executable (main main.c)
target_link_libraries (main DES)
