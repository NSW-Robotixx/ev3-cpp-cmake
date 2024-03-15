add_library(webComponents 
    STATIC
        WebComponentBase.cpp
        ComponentFullBody.cpp
)

target_sources(webComponents
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/WebComponentBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ComponentFullBody.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WebComponentBase.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ComponentFullBody.hpp
)

target_include_directories(webComponents
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(webComponents
    PUBLIC
        Logger
)
