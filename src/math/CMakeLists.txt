add_library(Vector2 STATIC Vector2.cpp)
add_library(Vector3 STATIC Vector3.cpp)

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

target_include_directories(Vector2 PUBLIC ${CMAKE_SOURCE_DIR}/src/)
target_include_directories(Vector3 PUBLIC ${CMAKE_SOURCE_DIR}/src/)

target_link_libraries(Vector2 PUBLIC)
target_link_libraries(Vector3 PUBLIC)

#testing 

add_library(Vector2Test STATIC Vector2.test.cpp)
add_library(Vector3Test STATIC Vector3.test.cpp)

target_sources(Vector2Test 
    PRIVATE
        Vector2.test.cpp    
    )

target_sources(Vector3Test
    PRIVATE
        Vector3.test.cpp
    )

target_include_directories(Vector2Test PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Vector3Test PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Vector2Test PUBLIC gtest_main Vector2)
target_link_libraries(Vector3Test PUBLIC gtest_main Vector3)