set(EV3_FILESYSTEM_SRC
    ${EV3_FILESYSTEM_SRC_DIR}/DeviceManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/EV3_MotorManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/EV3_SensorManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/PortManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/MotorPort.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/Port.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/SensorPort.cpp
)

set(EV3_FILESYSTEM_HDR
    ${EV3_FILESYSTEM_INCLUDE_DIR}/EV3_MotorManager.hpp
    ${EV3_FILESYSTEM_INCLUDE_DIR}/EV3_SensorManager.hpp
    ${EV3_FILESYSTEM_SRC_DIR}/DeviceManager.hpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/PortManager.hpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/MotorPort.hpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/Port.hpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/SensorPort.hpp
)

add_library(EV3_filesystem ${EV3_FILESYSTEM_SRC})

add_library(EV3_filesystem::filesystem ALIAS EV3_filesystem)

target_sources(EV3_filesystem
    PRIVATE
        ${EV3_FILESYSTEM_SRC}
    PUBLIC
        ${EV3_FILESYSTEM_HDR}
) 

target_include_directories(EV3_filesystem PUBLIC ${EV3_FILESYSTEM_INCLUDE_DIR})
target_include_directories(EV3_filesystem PUBLIC ${EV3_FILESYSTEM_SRC_DIR})

target_link_libraries(EV3_filesystem
    PUBLIC
        Logger
)

# set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")