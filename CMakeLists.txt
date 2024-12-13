cmake_minimum_required(VERSION 3.24...3.24)

set(CONAN_HOST_PROFILE "default" CACHE STRING "Conan profile to use for host")

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

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -latomic")

# add cmake-modules directory
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

# build options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_INTERNAL_TCP_SERVER "Build internal tcp server" ON)

# find dependencies
find_package(GTest REQUIRED)
find_package(Doxygen)
# find_package(freetype)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(ydcpp-tcpcat REQUIRED)
find_package(spdlog REQUIRED)
find_package(boost-leaf REQUIRED)
find_package(Boost REQUIRED)

# new and untested stuff
set(BUILD_SHARED_LIBS ON)
# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wall -Werror -Wextra")
# end of new and untested stuff

# add executables
add_executable(Main src/main.cpp)
# add_executable(Test src/tests.cpp)

# set executables to be static
# SET_TARGET_PROPERTIES(Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
# add include directories
# include_directories(${CMAKE_SOURCE_DIR}/lib)
# include_directories(${CMAKE_SOURCE_DIR}/tests)

# set the list of sources for all tests
set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${CMAKE_SOURCE_DIR}/src/tests.cpp)
# set the list of libs to link to
set_property(GLOBAL PROPERTY 
EV3_TESTS_LIBS 
gtest_main 
GTest::gtest_main 
boost::leaf
boost::boost 
spdlog::spdlog
)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(deps)

if (BUILD_DOCS)
endif()
add_subdirectory(doc)


target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/deps)

target_link_libraries(Main
#   Logger
#   EV3_system
#   EV3_gearbox
boost::leaf
  boost::boost
  spdlog::spdlog
  EV3_filesystem
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
  # SET_TARGET_PROPERTIES(FullTest PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
  
  
  target_sources(FullTest
    PRIVATE
        ${EV3_TESTS_SRC}
    PUBLIC
        ${EV3_TESTS_HDR}
)

target_link_libraries(FullTest PUBLIC ${EV3_TESTS_LIBS})
target_link_libraries(FullTest PUBLIC GTest::gtest_main GTest::gtest spdlog::spdlog boost::boost)

add_dependencies(FullTest docs)
    
    
# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)
      
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")