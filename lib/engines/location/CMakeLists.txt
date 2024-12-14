add_library(LocationEngine LocationEngine.cpp)

target_sources(LocationEngine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/LocationEngine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LocationEngine.hpp
    )
    
target_link_libraries(LocationEngine
    PUBLIC
        EV3_filesystem
        Vector2
        boost::boost
        spdlog::spdlog
        )