cmake_minimum_required(VERSION 3.7.2)

# set the project name
project(EV3_tcp_communication)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)

# set the C++ standard required
set(CMAKE_CXX_STANDARD_REQUIRED True)


# set variables for the source files
set(EV3_TCP_COMMUNICATION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EV3_TCP_COMMUNICATION_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EV3_TCP_COMMUNICATION_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(${EV3_TCP_COMMUNICATION_SRC_DIR})
add_subdirectory(${EV3_TCP_COMMUNICATION_TEST_DIR})