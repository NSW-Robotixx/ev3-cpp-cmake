cmake_minimum_required(VERSION 3.10)

# set the project name
project(EV3_tcp_communication)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)

# set the C++ standard required
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the FetchContent module
include(FetchContent)

# add the gtest dependency
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# set variables for the source files
set(EV3_TCP_COMMUNICATION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EV3_TCP_COMMUNICATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EV3_TCP_COMMUNICATION_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(${EV3_TCP_COMMUNICATION_SRC_DIR})
add_subdirectory(${EV3_TCP_COMMUNICATION_TEST_DIR})