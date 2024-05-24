add_subdirectory(guidanceLine)
add_subdirectory(obstacle)


add_library(pathfinder 
    AStar.cpp
    ObstacleManager.cpp
    SmoothPath.cpp
)

target_sources(pathfinder
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AStar.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObstacleManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SmoothPath.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/AStar.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ObstacleManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SmoothPath.hpp
)   

target_link_libraries(pathfinder 
    PUBLIC
        Vector2
        Logger
        Line
)