file(GLOB_RECURSE EV3_COMPUTE_TEST_HDR CONFIGURE_DEPENDS "*.hpp")

set(EV3_COMPUTE_TEST_SRC
    ${EV3_COMPUTE_TEST_DIR}/test_EV3_compute.cpp
    ${EV3_COMPUTE_TEST_DIR}/test_SmoothPath.cpp
)

include(GoogleTest)

add_executable(EV3_compute_test ${EV3_COMPUTE_TEST_SRC})

target_sources(EV3_compute_test
    PRIVATE
        ${EV3_COMPUTE_TEST_SRC}
)
target_include_directories(EV3_compute_test PRIVATE ${EV3_COMPUTE_SRC_DIR})
target_include_directories(EV3_compute_test PRIVATE ${EV3_COMPUTE_TEST_DIR})
target_include_directories(EV3_compute_test PUBLIC ${EV3_COMPUTE_SRC_DIR}/../include)

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