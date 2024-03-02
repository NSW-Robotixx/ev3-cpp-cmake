add_subdirectory(port)

add_library(PortManager STATIC
    ${CMAKE_CURRENT_LIST_DIR}/PortManager.cpp
    )

target_sources(PortManager 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PortManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PortManager.hpp
    )

target_link_libraries(PortManager
    PUBLIC
        Port
        Logger
        SensorPort
        MotorPort
    )

target_include_directories(PortManager PUBLIC ${CMAKE_SOURCE_DIR}/src)


#tests

add_library(PortManagerTest STATIC
    ${CMAKE_CURRENT_LIST_DIR}/PortManager.test.cpp
    )

target_link_libraries(PortManagerTest 
    PUBLIC
        PortManager
        gtest
    )