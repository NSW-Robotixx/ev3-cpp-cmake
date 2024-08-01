set(EV3_POSITION_SRC
    ${EV3_POSITION_SRC_DIR}/PositionManager.cpp
    ${EV3_POSITION_SRC_DIR}/Position.cpp
    ${EV3_POSITION_SRC_DIR}/SensorPosition.cpp
    ${EV3_POSITION_SRC_DIR}/MotorPosition.cpp
    )

set(EV3_POSITION_HDR
    ${EV3_POSITION_INCLUDE_DIR}/Position.hpp
    ${EV3_POSITION_SRC_DIR}/PositionManager.hpp
    ${EV3_POSITION_SRC_DIR}/SensorPosition.hpp
    ${EV3_POSITION_SRC_DIR}/MotorPosition.hpp
    )

add_library(EV3_position ${EV3_POSITION_SRC})

add_library(EV3_position::position ALIAS EV3_position)

target_sources(EV3_position
    PRIVATE
        ${EV3_POSITION_SRC}
    PUBLIC
        ${EV3_POSITION_HDR}
)

target_include_directories(EV3_position PUBLIC ${EV3_POSITION_INCLUDE_DIR})
target_include_directories(EV3_position PUBLIC ${EV3_POSITION_SRC_DIR})

target_link_libraries(EV3_position
    PUBLIC
        Logger
        EV3_filesystem
        Vector2
        Vector3
)
