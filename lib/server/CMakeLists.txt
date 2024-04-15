add_subdirectory(webServer)


add_library(ServerManager STATIC ServerManager.cpp)

target_sources(ServerManager
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ServerManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ServerManager.hpp
)

target_include_directories(ServerManager 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(ServerManager 
    PUBLIC
        webServer
        Logger
)