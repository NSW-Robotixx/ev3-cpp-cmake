add_library(Port STATIC Port.cpp)
add_library(MotorPort STATIC MotorPort.cpp)
add_library(SensorPort STATIC SensorPort.cpp)

target_sources(Port 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/Port.hpp
    )

target_sources(MotorPort
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MotorPort.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/MotorPort.hpp
    )

target_sources(SensorPort
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SensorPort.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/SensorPort.hpp
    )

target_include_directories(Port PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(MotorPort PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(SensorPort PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Port PUBLIC Logger)
target_link_libraries(MotorPort PUBLIC Port Logger)
target_link_libraries(SensorPort PUBLIC Port Logger)

#testing

add_library(PortTest Port.test.cpp)
add_library(MotorPortTest MotorPort.test.cpp)
add_library(SensorPortTest SensorPort.test.cpp)

target_sources(PortTest
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.test.cpp
    )

target_sources(MotorPortTest
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MotorPort.test.cpp
    )

target_sources(SensorPortTest
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SensorPort.test.cpp
    )

target_link_libraries(PortTest
    PRIVATE
        Port
        gtest_main
    )

target_link_libraries(MotorPortTest
    PRIVATE
        MotorPort
        gtest_main
    )

target_link_libraries(SensorPortTest
    PRIVATE
        SensorPort
        gtest_main
    )