add_subdirectory(bitmaps)

find_package(freetype REQUIRED)

#screen
add_library(Screen Screen.cpp)

target_sources(Screen
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Screen.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Screen.hpp
)

target_include_directories(Screen
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(Screen
    PUBLIC
        Logger
)

#WindowManager
add_library(WindowManager WindowManager.cpp)

target_sources(WindowManager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/WindowManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WindowManager.hpp
)

target_include_directories(WindowManager
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(WindowManager
    PUBLIC
        Screen
        Logger
)

#window
add_library(Window Window.cpp)

target_sources(Window
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Window.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Window.hpp
)

target_include_directories(Window
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(Window
    PUBLIC
        Logger
        Bitmaps
        Freetype::Freetype
)




