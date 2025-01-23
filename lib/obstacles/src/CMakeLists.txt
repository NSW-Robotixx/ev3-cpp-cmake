find_package(ydcpp-tcpcat REQUIRED)
find_package(boost-leaf)

set(EV3_OBSTACLE_SRC
    ${EV3_OBSTACLE_SRC_DIR}/EV3_ObstacleManager.cpp
)

set(EV3_OBSTACLE_HDR
    ${EV3_OBSTACLE_INCLUDE_DIR}/EV3_ObstacleManager.hpp
)

add_library(EV3_obstacle ${EV3_OBSTACLE_SRC})

add_library(EV3_obstacle::obstacle ALIAS EV3_obstacle)

target_sources(EV3_obstacle
    PRIVATE
        ${EV3_OBSTACLE_SRC}
    PUBLIC
        ${EV3_OBSTACLE_HDR}
) 

target_include_directories(EV3_obstacle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EV3_obstacle PUBLIC ${EV3_OBSTACLE_INCLUDE_DIR})

target_link_libraries(EV3_obstacle
    PUBLIC
        EV3_filesystem
        EV3_filesystem_fakesys
        spdlog::spdlog
        boost::leaf
        boost::boost
        Eigen3::Eigen
        yaml-cpp::yaml-cpp
)

set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")