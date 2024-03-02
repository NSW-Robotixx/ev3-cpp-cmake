cmake_minimum_required(VERSION 3.14)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Main main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/tests)
# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Main 
PUBLIC 
PortManager
Logger
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/tests)

SET_TARGET_PROPERTIES (Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")

# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)

# google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable testing
# include(CTest)
# enable_testing()

set(TEST_SOURCES ${CMAKE_SOURCE_DIR}/test.cpp)
# file(GLOB_RECURSE TEST_SOURCES "*test.cpp")
add_executable(Test ${TEST_SOURCES})

target_link_libraries(
  Test
  gtest_main
  Logger
  Port
  PortManager
  Vector3
  Vector2
  )
  
  target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/src)
  
  # throws compiler error, but works. Can be removed
    
include(GoogleTest)
gtest_discover_tests(Test)
if(CMAKE_C_COMPILER STREQUAL "/usr/bin/arm-linux-gnueabi-gcc")
  SET_TARGET_PROPERTIES (Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
else()
endif()