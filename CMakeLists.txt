cmake_minimum_required(VERSION 3.14)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# new and untested stuff
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# end of new and untested stuff

# fetch dependencies
include(FetchContent) 

# yaml parser -> NO INTERNET
# FetchContent_Declare(
#   yaml-cpp
#   GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#   GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
# )
# FetchContent_GetProperties(yaml-cpp)

# if(NOT yaml-cpp_POPULATED)
#   message(STATUS "Fetching yaml-cpp...")
#   FetchContent_Populate(yaml-cpp)
#   add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
# endif()

# google test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  
# find_package(yaml-cpp)

add_executable(Main main.cpp)
  
add_subdirectory(src)
add_subdirectory(tests)

# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/tests)
# target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/src)
  
target_link_libraries(Main 
PUBLIC
WindowManager
Logger
Window
webServer
webComponents
RobotMovement
# yaml-cpp::yaml-cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/tests)

SET_TARGET_PROPERTIES (Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")

# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)


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

message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")

if(CMAKE_C_COMPILER STREQUAL "/usr/bin/arm-linux-gnueabi-gcc")
  SET_TARGET_PROPERTIES (Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
else()
  include(GoogleTest)
  # gtest_discover_tests(Test)
endif()