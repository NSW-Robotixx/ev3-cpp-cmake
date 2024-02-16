add_library(port STATIC Port.cpp)

target_sources(port 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Port.cpp
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/Port.hpp
    )

target_include_directories(port PUBLIC ${CMAKE_SOURCE_DIR}/src)

#testing
add_library(TestPort STATIC Port.test.cpp)

target_include_directories(TestPort PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(TestPort PUBLIC ${CMAKE_SOURCE_DIR}/tests)

target_link_libraries(TestPort port GTest::gtest_main)