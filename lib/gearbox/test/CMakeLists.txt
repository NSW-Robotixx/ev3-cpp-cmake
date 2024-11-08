find_package(GTest REQUIRED)
find_package(log4cplus REQUIRED)

set(EV3_GEARBOX_TEST_SRC
    ${EV3_GEARBOX_TEST_DIR}/
)

get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)
get_property(EV3_TESTS_HDR GLOBAL PROPERTY EV3_TESTS_HDR)

# check if EV3_TESTS_SRC is defined
if(EV3_TESTS_SRC)
    message(STATUS "EV3_TESTS_SRC is defined")
    
    # set global property for EV3_TESTS_SRC
    set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${EV3_TESTS_SRC} ${EV3_GEARBOX_TEST_SRC})
    set_property(GLOBAL PROPERTY EV3_TESTS_HDR ${EV3_TESTS_HDR} ${EV3_GEARBOX_INCLUDE_DIR})

    # get the global property for the libs to be linked to the test
    get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
    
    # add the lib to be linked to the test
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} EV3_gearbox log4cplus::log4cplus abseil::abseil)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()

add_executable(EV3_gearbox_test ${EV3_GEARBOX_TEST_SRC})

target_sources(EV3_gearbox_test
    PRIVATE
        ${EV3_GEARBOX_TEST_SRC}
        test.cpp
)

target_include_directories(EV3_gearbox_test PUBLIC ${EV3_GEARBOX_INCLUDE_DIR})
target_include_directories(EV3_gearbox_test PRIVATE ${EV3_GEARBOX_SRC_DIR})

target_link_libraries(EV3_gearbox_test
    PUBLIC
        GTest::gtest
        EV3_filesystem
        log4cplus::log4cplus
        abseil::abseil
        Eigen3::Eigen
        # Logger
)

add_test(NAME EV3_gearbox_test COMMAND EV3_gearbox_test)