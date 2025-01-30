set(EV3_MOVEMENT_SRC
    ${EV3_MOVEMENT_SRC_DIR}/EV3_MovementEngine.cpp
    ${EV3_MOVEMENT_SRC_DIR}/MovementParser.cpp
)

set(EV3_MOVEMENT_HDR
    ${EV3_MOVEMENT_INCLUDE_DIR}/EV3_MovementEngine.hpp
    ${EV3_MOVEMENT_SRC_DIR}/MovementParser.hpp
)

add_library(MovementEngine ${EV3_MOVEMENT_SRC})

add_library(MovementEngine::movement ALIAS MovementEngine)

target_sources(MovementEngine
    PRIVATE
        ${EV3_MOVEMENT_SRC}
    PUBLIC
        ${EV3_MOVEMENT_HDR}
)

target_include_directories(MovementEngine PUBLIC ${EV3_MOVEMENT_INCLUDE_DIR})
target_include_directories(MovementEngine PUBLIC ${EV3_MOVEMENT_SRC_DIR})

target_link_libraries(MovementEngine
    PRIVATE
        spdlog::spdlog
        Eigen3::Eigen
        boost::leaf
        boost::boost
        Vector2
        Line
        EV3_compute
        EV3_position
)