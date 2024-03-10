add_library(ButtonNotifier STATIC ButtonNotifier.cpp)

target_sources(ButtonNotifier 
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/ButtonNotifier.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ButtonNotifier.hpp
    )

target_include_directories(ButtonNotifier
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
    )