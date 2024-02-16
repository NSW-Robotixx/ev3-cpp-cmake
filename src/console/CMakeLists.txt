add_library(Logger STATIC Logger.cpp)

target_sources(Logger 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
)

target_include_directories(Logger
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

add_library(TestLogger STATIC Logger.test.cpp)

target_sources(TestLogger 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Logger.test.cpp
)

target_include_directories(TestLogger
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(
  TestLogger
  GTest::gtest_main
)