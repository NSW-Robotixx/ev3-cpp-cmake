add_library(Vector2 STATIC Vector2.cpp)
add_library(Vector3 STATIC Vector3.cpp)
add_library(Line STATIC Line.cpp)

target_sources(Vector2
    PRIVATE
        Vector2.cpp    
    PUBLIC 
        Vector2.hpp
    )

target_sources(Vector3
    PRIVATE
        Vector3.cpp
    PUBLIC
        Vector3.hpp
    )

target_sources(Line
    PRIVATE
        Line.cpp
    PUBLIC
        Line.hpp
    )

target_include_directories(Vector2 PUBLIC ${CMAKE_SOURCE_DIR}/lib/)
target_include_directories(Vector3 PUBLIC ${CMAKE_SOURCE_DIR}/lib/)
target_include_directories(Line PUBLIC ${CMAKE_SOURCE_DIR}/lib/)

target_link_libraries(Vector2 PUBLIC Logger)
target_link_libraries(Vector3 PUBLIC Logger)
target_link_libraries(Line PUBLIC Logger)