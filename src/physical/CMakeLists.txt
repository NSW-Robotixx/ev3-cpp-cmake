add_subdirectory(portManager)

add_library(Sensor STATIC Sensor.cpp)
add_library(Motor STATIC Motor.cpp)
add_library(DeviceManager STATIC DeviceManager.cpp)

target_sources(DeviceManager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
  )

target_sources(Sensor
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Sensor.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Sensor.hpp
  )

target_sources(Motor
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Motor.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Motor.hpp
    )

target_include_directories(Sensor PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Motor PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(DeviceManager PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(DeviceManager PUBLIC Sensor Motor PortManager)