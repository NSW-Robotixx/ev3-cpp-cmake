add_subdirectory(portManager)
add_subdirectory(display)
add_subdirectory(buttons)

add_library(DeviceManager STATIC 
    DeviceManager.cpp
    SensorManager.cpp
    MotorManager.cpp)

target_sources(DeviceManager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SensorManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorManager.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DeviceManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SensorManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorManager.hpp
  )

target_include_directories(DeviceManager PUBLIC ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(DeviceManager PUBLIC SensorPort MotorPort PortManager)