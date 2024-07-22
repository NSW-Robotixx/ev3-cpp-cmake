add_subdirectory(guidanceLine)
add_subdirectory(obstacle)


add_library(pathfind
    AStar.cpp
    ObstacleManager.cpp
    SmoothPath.cpp
)

target_sources(pathfind
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AStar.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObstacleManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SmoothPath.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/AStar.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ObstacleManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SmoothPath.hpp
)   

target_link_libraries(pathfind
    PUBLIC
        Vector2
        Logger
        Line
)