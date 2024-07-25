file(GLOB_RECURSE EV3_FILESYSTEM_HDR CONFIGURE_DEPENDS "*.hpp")

set(EV3_FILESYSTEM_SRC
    ${EV3_FILESYSTEM_SRC_DIR}/DeviceManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/MotorManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/SensorManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/PortManager.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/MotorPort.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/Port.cpp
    ${EV3_FILESYSTEM_SRC_DIR}/portManager/port/SensorPort.cpp
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
target_include_directories(EV3_filesystem PRIVATE ${EV3_FILESYSTEM_SRC_DIR})

target_link_libraries(EV3_filesystem
    PUBLIC
        Logger
)

set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")