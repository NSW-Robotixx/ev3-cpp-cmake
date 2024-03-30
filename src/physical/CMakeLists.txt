add_subdirectory(portManager)
add_subdirectory(display)
add_subdirectory(buttons)

add_library(DeviceManager STATIC DeviceManager.cpp)

target_sources(DeviceManager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
  )

target_include_directories(DeviceManager PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(DeviceManager PUBLIC SensorPort MotorPort PortManager)