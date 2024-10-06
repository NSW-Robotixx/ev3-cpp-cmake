find_package(yaml-cpp REQUIRED)

set(EV3_SYSTEM_SRC
    ${EV3_SYSTEM_SRC_DIR}/EV3_System.cpp
    ${EV3_SYSTEM_SRC_DIR}/EV3_System_tcp.cpp
    ${EV3_SYSTEM_SRC_DIR}/ConfigReader.cpp
)

set(EV3_SYSTEM_HDR
    ${EV3_SYSTEM_INCLUDE_DIR}/EV3_System.hpp
    ${EV3_SYSTEM_INCLUDE_DIR}/EV3_System_tcp.hpp
    ${EV3_SYSTEM_SRC_DIR}/ConfigReader.hpp
)

add_library(EV3_system ${EV3_SYSTEM_SRC})

target_sources(EV3_system
    PRIVATE
        ${EV3_SYSTEM_SRC}
    PUBLIC
        ${EV3_SYSTEM_HDR}
)

target_include_directories(EV3_system
    PUBLIC
        ${EV3_SYSTEM_INCLUDE_DIR}
        ${EV3_SYSTEM_SRC_DIR}
)

target_link_libraries(EV3_system
    PUBLIC
        Logger
        Vector3
        EV3_compute
        yaml-cpp::yaml-cpp
)