find_package(ydcpp-tcpcat REQUIRED)

set(EV3_COMPUTE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/EV3_compute_tcp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EV3_compute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pf/AStar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pf/ObstacleManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pf/SmoothPath.cpp
)

set(EV3_COMPUTE_HDR
    ${EV3_COMPUTE_INCLUDE_DIR}/EV3_compute_tcp.hpp
    ${EV3_COMPUTE_INCLUDE_DIR}/EV3_compute.hpp
    ${EV3_COMPUTE_SRC_DIR}/pf/AStar.hpp
    ${EV3_COMPUTE_SRC_DIR}/pf/ObstacleManager.hpp
    ${EV3_COMPUTE_SRC_DIR}/pf/SmoothPath.hpp
)

add_library(EV3_compute ${EV3_COMPUTE_SRC})

add_library(EV3_compute::compute ALIAS EV3_compute)

target_sources(EV3_compute
    PRIVATE
        ${EV3_COMPUTE_SRC}
    PUBLIC
        ${EV3_COMPUTE_HDR}
) 

target_include_directories(EV3_compute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EV3_compute PUBLIC ${EV3_COMPUTE_INCLUDE_DIR})

target_link_libraries(EV3_compute
    PUBLIC
        Logger
        EV3_tcp_communication
        Vector2
        Line
        ydcpp-tcpcat
)

set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")