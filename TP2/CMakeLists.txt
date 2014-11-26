project (GIFmain)
cmake_minimum_required (VERSION 2.8)

set (CMAKE_C_FLAGS "-Wall -pthread")

#file (GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
#file (GLOB_RECURSE PROJECT_SOURCES "src/*.c")

add_library (stb_image src/stb_image.c)
add_library (GIFencoder src/GIFencoder.cpp)

include_directories (include)
add_executable (GIFmain src/GIFmain.cpp)
target_link_libraries (GIFmain stb_image GIFencoder)
