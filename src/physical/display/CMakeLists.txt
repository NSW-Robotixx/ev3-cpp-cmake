add_subdirectory(bitmaps)

#screen
add_library(Screen STATIC Screen.cpp)

target_sources(Screen
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Screen.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Screen.hpp
)

target_include_directories(Screen
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Screen
    PUBLIC
        Logger
)

#WindowManager
add_library(WindowManager STATIC WindowManager.cpp)

target_sources(WindowManager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/WindowManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WindowManager.hpp
)

target_include_directories(WindowManager
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(WindowManager
    PUBLIC
        Screen
        Logger
)

#window
add_library(Window STATIC Window.cpp)

target_sources(Window
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Window.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Window.hpp
)

target_include_directories(Window
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Window
    PUBLIC
        Logger
        Bitmaps
)

#tests

add_executable(ScreenTest Screen.test.cpp)

target_sources(ScreenTest
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Screen.test.cpp
)

target_link_libraries(ScreenTest
    PRIVATE
        Screen
        gtest_main
)

target_include_directories(ScreenTest
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)