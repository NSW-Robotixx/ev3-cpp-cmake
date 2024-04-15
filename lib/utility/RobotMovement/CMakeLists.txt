add_library(RobotMovement STATIC RobotMovement.cpp)

target_sources(RobotMovement
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/RobotMovement.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RobotMovement.hpp
)

target_include_directories(RobotMovement
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(RobotMovement
    PUBLIC
        Logger
        DeviceManager
        PortManager
        MotorPort
        SensorPort
)