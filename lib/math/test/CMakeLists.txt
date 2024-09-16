find_package(GTest REQUIRED)

set(EV3_MATH_TEST_SRC
    ${EV3_MATH_TEST_DIR}/test_Vector2.cpp
    ${EV3_MATH_TEST_DIR}/test_Vector3.cpp
    ${EV3_MATH_TEST_DIR}/test_Line.cpp
)

get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)

# check if EV3_TESTS_SRC is defined
if(EV3_TESTS_SRC)
    message(STATUS "EV3_TESTS_SRC is defined")
    
    # set global property for EV3_TESTS_SRC
    set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${EV3_TESTS_SRC} ${EV3_MATH_TEST_SRC})

    # get the global property for the libs to be linked to the test
    get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
    
    # add the lib to be linked to the test
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} Line Vector2 Vector3)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()


add_executable(EV3_math_test ${EV3_MATH_TEST_SRC})

target_sources(EV3_math_test
    PRIVATE
        ${EV3_MATH_TEST_SRC}
    )

target_include_directories(EV3_math_test PUBLIC ${EV3_MATH_INCLUDE_DIR})
target_include_directories(EV3_math_test PRIVATE ${EV3_MATH_SRC_DIR})

target_link_libraries(EV3_math_test PUBLIC GTest::gtest_main Line Vector2 Vector3)

add_test(NAME EV3_math_test COMMAND EV3_math_test)