add_library(LocationEngine STATIC LocationEngine.cpp)

target_sources(LocationEngine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/LocationEngine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LocationEngine.hpp
    )
    
target_link_libraries(LocationEngine
    PUBLIC
        Logger
        DeviceManager
        Vector2
        )