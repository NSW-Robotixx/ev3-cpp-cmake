add_library(GraphicalInterface
    GraphicalInterface.cpp
    GraphicalInterface.hpp
)

target_sources(GraphicalInterface PRIVATE
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GraphicalInterface.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/GraphicalInterface.hpp
)

target_include_directories(GraphicalInterface PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(GraphicalInterface
    PUBLIC
        Logger
)