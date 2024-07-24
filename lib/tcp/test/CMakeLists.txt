set(EV3_TCP_COMMUNICATION_TEST_SRC
    test_tcp_connection.cpp
)

include(GoogleTest)

add_executable(ev3_tcp_communication_test
    ${EV3_TCP_COMMUNICATION_TEST_SRC}
)

target_sources(ev3_tcp_communication_test
    PRIVATE
        ${EV3_TCP_CONNECTION_SRC}
)

target_include_directories(ev3_tcp_communication_test
    PRIVATE
        ${EV3_TCP_COMMUNICATION_SRC_DIR}
        ${EV3_TCP_COMMUNICATION_INCLUDE_DIR}
)


target_link_libraries(ev3_tcp_communication_test
    PRIVATE
        gtest_main
        EV3_tcp_communication
)

gtest_discover_tests(ev3_tcp_communication_test)