find_package(ydcpp-tcpcat REQUIRED)

set(EV3_GEARBOX_SRC
    ${EV3_GEARBOX_SRC_DIR}/EV3_Gearbox.cpp
)

set(EV3_GEARBOX_HDR
    ${EV3_GEARBOX_INCLUDE_DIR}/EV3_Gearbox.hpp
)

add_library(EV3_gearbox ${EV3_GEARBOX_SRC})

add_library(EV3_gearbox::gearbox ALIAS EV3_gearbox)

target_sources(EV3_gearbox
    PRIVATE
        ${EV3_GEARBOX_SRC}
    PUBLIC
        ${EV3_GEARBOX_HDR}
) 

target_include_directories(EV3_gearbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EV3_gearbox PUBLIC ${EV3_GEARBOX_INCLUDE_DIR})

target_link_libraries(EV3_gearbox
    PUBLIC
        Logger
)

set(ENABLE_LOGGING ON CACHE BOOL "Enable logging")