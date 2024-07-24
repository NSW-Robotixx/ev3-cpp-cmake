file(GLOB_RECURSE EV3_FILESYSTEM_TEST_HDR CONFIGURE_DEPENDS "*.hpp")

set(EV3_FILESYSTEM_TEST_SRC
    Fakesys.cpp
    SensorManager.test.cpp
    portManager/PortManager.test.cpp
    portManager/port/MotorPort.test.cpp
    portManager/port/Port.test.cpp
    portManager/port/SensorPort.test.cpp
    testDeviceManager.cpp
    testFakesys.cpp
    testMotorManager.cpp
)

include(GoogleTest)

add_executable(EV3_filesystem_test ${EV3_FILESYSTEM_TEST_SRC})

# add alias of lib to be used in tests (not needed for executable)
# add_library(EV3_filesystem::test ALIAS EV3_filesystem_test)

target_sources(EV3_filesystem_test
    PRIVATE
        ${EV3_FILESYSTEM_TEST_SRC}
    PUBLIC
        ${EV3_FILESYSTEM_TEST_HDR}
)
target_include_directories(EV3_filesystem_test PUBLIC ${EV3_FILESYSTEM_SRC_DIR})
target_include_directories(EV3_filesystem_test PUBLIC ${EV3_FILESYSTEM_TEST_DIR})
target_include_directories(EV3_filesystem_test PRIVATE ${EV3_FILESYSTEM_SRC_DIR}/../include)

target_link_libraries(EV3_filesystem_test
    PUBLIC
        GTest::gtest_main
        EV3_filesystem
        # Logger
)

add_test(NAME EV3_filesystem_test COMMAND EV3_filesystem_test)