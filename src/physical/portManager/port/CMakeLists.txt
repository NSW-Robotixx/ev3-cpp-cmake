add_library(Port STATIC Port.cpp)

target_sources(Port 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/Port.hpp
    )

target_include_directories(Port PUBLIC ${CMAKE_SOURCE_DIR}/src)

#testing

add_executable(PortTest Port.test.cpp)

target_sources(PortTest
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.test.cpp
    )

target_link_libraries(PortTest
    PRIVATE
        Port
        gtest_main
    )

