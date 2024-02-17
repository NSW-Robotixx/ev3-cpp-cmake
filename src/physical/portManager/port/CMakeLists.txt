add_library(port STATIC Port.cpp)

target_sources(port 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/Port.hpp
    )

target_include_directories(port PUBLIC ${CMAKE_SOURCE_DIR}/src)

#testing