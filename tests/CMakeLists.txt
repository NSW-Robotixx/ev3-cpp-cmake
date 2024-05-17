message(STATUS CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

LIST(APPEND SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/initFiles.test.cpp)

# message(STATUS SRC_FILES: ${SRC_FILES})

add_library(all_tests STATIC ${SRC_FILES})


target_link_libraries(all_tests
    PUBLIC    
        gtest_main
        Logger
        Port
        PortManager
        Vector3
        Vector2
        DeviceManager
        ButtonNotifier
        # Bitmaps
        Screen
        WindowManager
        Window
        MotorPort
        SensorPort
        http-server
        webComponents
        webServer
        ServerManager
        RobotMovement
        UserInterface
)

target_include_directories(all_tests PUBLIC ${CMAKE_SOURCE_DIR}/lib)