add_library(http-server STATIC http_server.cc)

target_sources(http-server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/http_server.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/http_message.cc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/http_server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/http_message.h
        ${CMAKE_CURRENT_SOURCE_DIR}/uri.h
)

target_include_directories(http-server
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)