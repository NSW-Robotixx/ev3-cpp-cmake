set(EV3_COMPUTE_TEST_SRC
    ${EV3_COMPUTE_TEST_DIR}/test_EV3_compute.cpp
    ${EV3_COMPUTE_TEST_DIR}/test_SmoothPath.cpp
    ${EV3_COMPUTE_TEST_DIR}/pf/test_AStar.cpp
)

get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)

# check if EV3_TESTS_SRC is defined
if(EV3_TESTS_SRC)
    # set global property for EV3_TESTS_SRC
    set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${EV3_TESTS_SRC} ${EV3_COMPUTE_TEST_SRC})

    # get the global property for the libs to be linked to the test
    get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
    
    # add the lib to be linked to the test
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} EV3_compute)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()


add_executable(EV3_compute_test ${EV3_COMPUTE_TEST_SRC})

target_sources(EV3_compute_test
    PRIVATE
        ${EV3_COMPUTE_TEST_SRC}
)
target_include_directories(EV3_compute_test PRIVATE ${EV3_COMPUTE_SRC_DIR})
target_include_directories(EV3_compute_test PUBLIC ${EV3_COMPUTE_INCLUDE_DIR})

target_link_libraries(EV3_compute_test
    PUBLIC
        GTest::gtest_main
        EV3_compute
        EV3_tcp_communication
        Vector2
        Line
        # Logger
)

add_test(NAME EV3_compute_test COMMAND EV3_compute_test)