add_subdirectory(port)

add_library(Device_factory STATIC
    ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.cpp
    )

target_sources(Device_factory 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/DeviceFactory.hpp
    )

target_link_libraries(Device_factory 
    PUBLIC
        Port
    )

target_include_directories(Device_factory PUBLIC ${CMAKE_SOURCE_DIR}/src)


#tests

add_library(DeviceManagerTest STATIC
    ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.test.cpp
    )

target_link_libraries(DeviceManagerTest 
    PUBLIC
        Device_factory
        gtest
    )