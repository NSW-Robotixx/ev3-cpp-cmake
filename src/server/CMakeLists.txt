add_subdirectory(http_server)
add_subdirectory(webComponents)

add_library(webServer STATIC
    webServer.cpp
)

target_sources(webServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/webServer.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/webServer.hpp
)

target_link_libraries(webServer
    PRIVATE
        http_server
        webComponents
)