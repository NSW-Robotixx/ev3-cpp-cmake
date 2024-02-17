cmake_minimum_required(VERSION 3.10)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Main main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/tests)
# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Main PUBLIC device_factory)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/tests)

SET_TARGET_PROPERTIES (Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")

# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)