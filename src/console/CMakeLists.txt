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

# testing
add_library(LoggerTest STATIC Logger.test.cpp)

target_link_libraries(LoggerTest
    PUBLIC
        Logger
        gtest
)