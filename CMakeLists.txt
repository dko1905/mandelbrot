cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)

# create project
project(Mandlebrot)

# add executable
add_executable(Mandlebrot src/main.c)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
target_link_libraries (Mandlebrot ${PNG_LIBRARIES})

find_package(ZLIB REQUIRED)
target_link_libraries (Mandlebrot ZLIB::ZLIB)