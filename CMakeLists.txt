cmake_minimum_required(VERSION 3.7.2)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compiler flags for coverage
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# add cmake-modules directory
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

# new and untested stuff
set(BUILD_SHARED_LIBS ON)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wall -Werror -Wextra")
# end of new and untested stuff

# add executables
add_executable(Main src/main.cpp)
add_executable(Test ${PROJECT_SOURCE_DIR}/src/test.cpp)

# add include directories
# include_directories(${CMAKE_SOURCE_DIR}/lib)
# include_directories(${CMAKE_SOURCE_DIR}/tests)

# set the list of sources for all tests
set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${CMAKE_SOURCE_DIR}/src/tests.cpp)
# set the list of libs to link to
set_property(GLOBAL PROPERTY EV3_TESTS_LIBS gtest_main)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(deps)
# add_subdirectory(doc)

# set executables to be static
# SET_TARGET_PROPERTIES(Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
# SET_TARGET_PROPERTIES(Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")

# find dependencies
find_package(Eigen3 REQUIRED)


# # lvgl display library
# # Specify path to own LVGL config header
#   message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}/lib/lv_conf.h")
#   
#   set(LV_CONF_PATH
#       ${CMAKE_CURRENT_SOURCE_DIR}/lib/lv_conf.h
#       CACHE STRING "" FORCE)
#   
#   message(STATUS "LV_CONF_PATH: ${LV_CONF_PATH}")
#   
#   # # Fetch LVGL from GitHub
#   FetchContent_Declare(lvgl GIT_REPOSITORY  https://github.com/lvgl/lvgl.git)
#   FetchContent_MakeAvailable(lvgl)

include(FetchContent)

# google test
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/tests)
target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/deps)
    
target_link_libraries(Main 
  Logger
  EV3_system
)    
  

# add all tests executable

# get global property EV3_TESTS_SRC
get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)
message(STATUS EV3_TESTS_SRC: ${EV3_TESTS_SRC})

# get global property EV3_TESTS_HDR
get_property(EV3_TESTS_HDR GLOBAL PROPERTY EV3_TESTS_HDR)
message(STATUS EV3_TESTS_HDR: ${EV3_TESTS_HDR})

# get global property EV3_TESTS_LIBS
get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
message(STATUS EV3_TESTS_LIBS: ${EV3_TESTS_LIBS})



add_executable(FullTest ${EV3_TESTS_SRC})

target_sources(FullTest
    PRIVATE
        ${EV3_TESTS_SRC}
    PUBLIC
        ${EV3_TESTS_HDR}
)

target_link_libraries(FullTest PUBLIC ${EV3_TESTS_LIBS})
    
    
# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)
    
    
    # enable testing
    # include(CTest)
    # enable_testing()
    
    target_link_libraries(
      Test
      gtest_main
      Logger
      Vector3
      Vector2
      RobotMovement
      webServer
      webComponents
      WindowManager
      LocationEngine
      # EV3_filesystem_test
      )
      
      
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")


if(CMAKE_C_COMPILER STREQUAL "/usr/bin/arm-linux-gnueabi-gcc")
# SET_TARGET_PROPERTIES (Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
else()
include(GoogleTest)
gtest_discover_tests(Test) # just needed for ctest to discover gtests
endif()


# # code coverage
# if (CMAKE_COMPILER_IS_GNUCXX)
#     include(CodeCoverage)
#     append_coverage_compiler_flags()

#     # we need to turn off optimization for non-skewed coverage reports
#     set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

#     # optional excludes - None needed here
#     set(COVERAGE_EXCLUDES build/* lib/*.test.cpp) # this is optional if you want to exclude some directory from the report

#     # importantly, set the path to the gcovr executable that you downladed
#     set(GCOVR_PATH "/home/niklas/.local/bin/gcovr")
#     # Works
#     setup_target_for_coverage_gcovr_xml(
#             NAME TestDoMathCoverageXml
#             EXECUTABLE Test
#     )
#     # Works
#     setup_target_for_coverage_gcovr_html(
#             NAME TestDoMathCoverageHtml
#             EXECUTABLE Test
#     )
# endif()
