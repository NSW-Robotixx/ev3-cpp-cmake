add_library(Screen Screen.cpp)

target_sources(Screen
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Screen.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Screen.hpp
)

target_include_directories(Screen
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#tests

add_executable(ScreenTest Screen.test.cpp)

target_sources(ScreenTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Screen.test.cpp
)

target_link_libraries(ScreenTest
    PRIVATE
        Screen
        gtest
)