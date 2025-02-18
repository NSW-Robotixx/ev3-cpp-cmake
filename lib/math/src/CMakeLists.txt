add_library(Vector2 Vector2.cpp)
add_library(Vector3 Vector3.cpp)
add_library(Line Line.cpp)

target_sources(Vector2
    PRIVATE
        ${EV3_MATH_SRC_DIR}/Vector2.cpp
    PUBLIC 
        ${EV3_MATH_INCLUDE_DIR}/Vector2.hpp
    )

target_sources(Vector3
    PRIVATE
        ${EV3_MATH_SRC_DIR}/Vector3.cpp
    PUBLIC
        ${EV3_MATH_INCLUDE_DIR}/Vector3.hpp
    )

target_sources(Line
    PRIVATE
        ${EV3_MATH_SRC_DIR}/Line.cpp
    PUBLIC
        ${EV3_MATH_INCLUDE_DIR}/Line.hpp
    )

target_include_directories(Vector2 PUBLIC ${EV3_MATH_INCLUDE_DIR})
target_include_directories(Vector3 PUBLIC ${EV3_MATH_INCLUDE_DIR})
target_include_directories(Line PUBLIC ${EV3_MATH_INCLUDE_DIR})

target_link_libraries(Line PUBLIC boost::leaf )
target_link_libraries(Vector2 PUBLIC boost::leaf)
target_link_libraries(Vector3 PUBLIC boost::leaf)

set(EV3_MATH_LIBS
    Vector2
    Vector3
    Line
    Eigen3::Eigen
    CACHE INTERNAL "List of EV3 math libraries"
)
