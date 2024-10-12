cmake_minimum_required(VERSION 3.24)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop2/conan_provider.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    TLS_VERIFY ON)
    endif()

set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES ${CMAKE_BINARY_DIR}/conan.cmake)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add cmake-modules directory
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

# build options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_INTERNAL_TCP_SERVER "Build internal tcp server" ON)

# find dependencies
find_package(GTest REQUIRED)
find_package(Doxygen)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(ydcpp-tcpcat REQUIRED)
find_package(freetype REQUIRED)
find_package(log4cplus REQUIRED)

# new and untested stuff
set(BUILD_SHARED_LIBS ON)
# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wall -Werror -Wextra")
# end of new and untested stuff

# add executables
add_executable(Main src/main.cpp)
# add_executable(Test src/tests.cpp)

# add include directories
# include_directories(${CMAKE_SOURCE_DIR}/lib)
# include_directories(${CMAKE_SOURCE_DIR}/tests)

# set the list of sources for all tests
set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${CMAKE_SOURCE_DIR}/src/tests.cpp)
# set the list of libs to link to
set_property(GLOBAL PROPERTY EV3_TESTS_LIBS gtest_main GTest::gtest_main)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(deps)

if (BUILD_DOCS)
endif()
add_subdirectory(doc)
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
message(STATUS EV3_TESTS_LIBS: ${EV3_TESTS_LIBS} GTest::gtest_main)



add_executable(FullTest ${EV3_TESTS_SRC})

target_sources(FullTest
    PRIVATE
        ${EV3_TESTS_SRC}
    PUBLIC
        ${EV3_TESTS_HDR}
)

target_link_libraries(FullTest PUBLIC ${EV3_TESTS_LIBS})
target_link_libraries(FullTest PUBLIC GTest::gtest_main)

add_dependencies(FullTest docs)
    
    
# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)
      
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

# SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
# SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# # code coverage
# if (CMAKE_COMPILER_IS_GNUCXX)
#     include(CodeCoverage)
#     # append_coverage_compiler_flags()

#     # we need to turn off optimization for non-skewed coverage reports
#     # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O1 -fprofile-abs-path -fprofile-arcs -ftest-coverage -fPIC --coverage")
#     target_compile_options(FullTest PUBLIC -fprofile-arcs -ftest-coverage -fPIC --coverage -O0 -g)
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
#     target_link_libraries(FullTest PUBLIC gcov)
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

#     # optional excludes - None needed here
#     # set(COVERAGE_EXCLUDES lib/*.test.cpp test_*) # this is optional if you want to exclude some directory from the report
 
#     # importantly, set the path to the gcovr executable that you downladed
#     set(GCOVR_PATH "/usr/local/bin/gcovr")
#     setup_target_for_coverage_lcov(
#         NAME coverage
#         EXECUTABLE FullTest)
# endif()