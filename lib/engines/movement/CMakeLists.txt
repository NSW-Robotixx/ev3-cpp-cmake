add_library(MovementEngine STATIC MovementEngine.cpp)

target_sources(MovementEngine 
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/MovementEngine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MovementEngine.hpp
    )

target_link_libraries(MovementEngine
    PUBLIC
        Logger
        pf
        Vector2
        RobotMovement
    )
