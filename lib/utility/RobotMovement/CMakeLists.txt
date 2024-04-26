add_library(RobotMovement STATIC RobotMovement.cpp MovementAction.cpp)

target_sources(RobotMovement
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/RobotMovement.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MovementAction.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RobotMovement.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MovementAction.cpp
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