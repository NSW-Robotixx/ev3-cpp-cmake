cmake_minimum_required(VERSION 3.7.2)

#set the project name
project(EV3_position C CXX)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)

# set the C++ standard to required
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(boost-leaf REQUIRED)
find_package(Eigen3 REQUIRED)

# set variables to paths of source files
set(EV3_POSITION_INCLUDE_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(EV3_POSITION_SRC_DIR              ${CMAKE_CURRENT_SOURCE_DIR}/src     CACHE INTERNAL "")
set(EV3_POSITION_TEST_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/test    CACHE INTERNAL "")

add_subdirectory(${EV3_POSITION_SRC_DIR})
add_subdirectory(${EV3_POSITION_TEST_DIR})