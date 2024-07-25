
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


# message(STATUS SRC_FILES: ${SRC_FILES})

add_library(all_tests ${SRC_FILES})


target_link_libraries(all_tests
    PUBLIC    
        gtest_main
        Logger
        Vector3
        Vector2
        ButtonNotifier
        # Bitmaps
        Screen
        WindowManager
        Window
        http-server
        webComponents
        webServer
        ServerManager
        RobotMovement
        UserInterface
        Line
        # EV3_filesystem
)

target_include_directories(all_tests PUBLIC ${CMAKE_SOURCE_DIR}/lib)