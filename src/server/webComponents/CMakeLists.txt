add_library(webComponents 
    STATIC
        WebComponentBase.cpp
)

target_sources(webComponents
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/WebComponentBase.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WebComponentBase.hpp
)

target_include_directories(webComponents
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)