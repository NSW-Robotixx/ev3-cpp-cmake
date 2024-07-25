# file(GLOB_RECURSE EV3_FILESYSTEM_TEST_HDR CONFIGURE_DEPENDS "*.hpp")

set(EV3_FILESYSTEM_TEST_SRC
    ${EV3_FILESYSTEM_TEST_DIR}/Fakesys.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/SensorManager.test.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/portManager/PortManager.test.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/portManager/port/MotorPort.test.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/portManager/port/Port.test.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/portManager/port/SensorPort.test.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/testDeviceManager.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/testFakesys.cpp
    ${EV3_FILESYSTEM_TEST_DIR}/testMotorManager.cpp
)

get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)
get_property(EV3_TESTS_HDR GLOBAL PROPERTY EV3_TESTS_HDR)

# check if EV3_TESTS_SRC is defined
if(EV3_TESTS_SRC)
    message(STATUS "EV3_TESTS_SRC is defined")
    
    # set global property for EV3_TESTS_SRC
    set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${EV3_TESTS_SRC} ${EV3_FILESYSTEM_TEST_SRC})
    set_property(GLOBAL PROPERTY EV3_TESTS_HDR ${EV3_TESTS_HDR} ${EV3_FILESYSTEM_INCLUDE_DIR}/Fakesys.hpp)

    # get the global property for the libs to be linked to the test
    get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
    
    # add the lib to be linked to the test
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} EV3_filesystem)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()

add_executable(EV3_filesystem_test ${EV3_FILESYSTEM_TEST_SRC})

target_sources(EV3_filesystem_test
    PRIVATE
        ${EV3_FILESYSTEM_TEST_SRC}
    PUBLIC
        ${EV3_FILESYSTEM_INCLUDE_DIR}/Fakesys.hpp
)

target_include_directories(EV3_filesystem_test PUBLIC ${EV3_FILESYSTEM_INCLUDE_DIR})
target_include_directories(EV3_filesystem_test PRIVATE ${EV3_FILESYSTEM_SRC_DIR})

target_link_libraries(EV3_filesystem_test
    PUBLIC
        GTest::gtest_main
        EV3_filesystem
        # Logger
)

add_test(NAME EV3_filesystem_test COMMAND EV3_filesystem_test)