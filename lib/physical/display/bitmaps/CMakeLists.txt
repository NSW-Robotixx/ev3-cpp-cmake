add_library(Bitmaps STATIC Bitmaps.cpp)

target_sources(Bitmaps
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Bitmaps.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Bitmaps.hpp
    )   

target_include_directories(Bitmaps
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
    )