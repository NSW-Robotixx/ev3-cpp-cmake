add_subdirectory(port)
add_subdirectory(portManager)

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


# DeviceManager tests
add_library(DeviceManagerTests STATIC
    ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.test.cpp
)

target_include_directories(DeviceManagerTests PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_sources(DeviceManagerTests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.test.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
    )

target_link_libraries(DeviceManagerTests
    PUBLIC
        device_factory
        GTest::gtest_main
    )

# Portstests
add_library(TestPorts STATIC
    ${CMAKE_CURRENT_LIST_DIR}/ports.test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.test.cpp
)

target_include_directories(TestPorts PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(TestPorts PUBLIC ${CMAKE_SOURCE_DIR}/tests)
target_include_directories(TestPorts PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_sources(TestPorts
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ports.test.cpp
)

target_link_libraries(TestPorts
    PUBLIC
        device_factory
        DeviceManagerTests
        GTest::gtest_main
    )