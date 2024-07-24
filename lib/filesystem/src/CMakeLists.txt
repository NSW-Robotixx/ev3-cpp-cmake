file(GLOB_RECURSE EV3_FILESYSTEM_SRC CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE EV3_FILESYSTEM_HDR CONFIGURE_DEPENDS "*.hpp")

add_library(EV3_filesystem ${EV3_FILESYSTEM_SRC})

add_library(EV3_filesystem::filesystem ALIAS EV3_filesystem)

target_sources(EV3_filesystem
    PRIVATE
        ${EV3_FILESYSTEM_SRC}
    PUBLIC
        ${EV3_FILESYSTEM_HDR}
) 

target_include_directories(EV3_filesystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EV3_filesystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(EV3_filesystem
    PUBLIC
        Logger
)

set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")