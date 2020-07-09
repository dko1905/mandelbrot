cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# create project
project(Mandlebrot)

# add executable
add_executable(Mandlebrot src/main.c)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
target_link_libraries (Mandlebrot ${PNG_LIBRARIES})

find_package(ZLIB REQUIRED)
target_link_libraries (Mandlebrot ZLIB::ZLIB)

# link dependencies
target_link_libraries(Mandlebrot libpng)
target_link_libraries(Mandlebrot zlib)