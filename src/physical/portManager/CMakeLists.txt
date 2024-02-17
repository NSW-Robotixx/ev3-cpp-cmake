add_subdirectory(port)

add_library(device_factory STATIC
    ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.cpp
    )

target_sources(device_factory 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.hpp
    )

target_link_libraries(device_factory 
    PUBLIC
        port
    )

target_include_directories(device_factory PUBLIC ${CMAKE_SOURCE_DIR}/src)
