cmake_minimum_required(VERSION 3.14)

project(robotixx-ev3dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compiler flags for coverage
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# add cmake-modules directory
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

# new and untested stuff
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# end of new and untested stuff

# add executables
add_executable(Main src/main.cpp)
add_executable(Test ${PROJECT_SOURCE_DIR}/src/test.cpp)

# add include directories
# include_directories(${CMAKE_SOURCE_DIR}/lib)
# include_directories(${CMAKE_SOURCE_DIR}/tests)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(deps)
# add_subdirectory(doc)

# set executables to be static
SET_TARGET_PROPERTIES(Main PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
SET_TARGET_PROPERTIES(Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")

# fetch dependencies
include(FetchContent)

# yaml parser 
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)

FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

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

# google test
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# if (FALSE)
# message(STATUS "Enabling VCPKG for dependencies")
# 
# ##################
# #  VCPKG CONFIG  #
# ##################
# 
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake"
#   CACHE STRING "Vcpkg toolchain file")
# 
# ##################
# # VCPKG PACKAGES #
# ##################
# 
# # find SDL2
# find_package(SDL2 CONFIG REQUIRED)
# target_link_libraries(Main
#     PRIVATE
#     $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#     $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
# )
# endif()

# SDL2
#  if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#      set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )
#      set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME} )
#      set_property( TARGET Main PROPERTY WIN32_EXECUTABLE true )
#  endif()

target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/tests)
target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/deps)
    
target_link_libraries(Main 
  WindowManager
  Logger
  Window
  webServer
  webComponents
  RobotMovement
  Vector2
  MovementEngine
  lvgl::lvgl
  # yaml-cpp::yaml-cpp
)
    
    
    
    
# make cmake not print the commands it runs
set(CMAKE_VERBOSE_MAKEFILE OFF)
    
    
    # enable testing
    # include(CTest)
    # enable_testing()
    
    target_link_libraries(
      Test
      gtest_main
      Logger
      Port
      PortManager
      Vector3
      Vector2
      pathfinder
      MovementEngine
      RobotMovement
      webServer
      webComponents
      WindowManager
      yaml-cpp::yaml-cpp
      LocationEngine
      )
      
      
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")


if(CMAKE_C_COMPILER STREQUAL "/usr/bin/arm-linux-gnueabi-gcc")
SET_TARGET_PROPERTIES (Test PROPERTIES LINK_FLAGS "-static -lc -lm -L/usr/local/lib/")
else()
include(GoogleTest)
# gtest_discover_tests(Test) # just needed for ctest to discover gtests
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