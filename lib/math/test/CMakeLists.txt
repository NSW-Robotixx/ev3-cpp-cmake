set(EV3_MATH_TEST_SRC
    ${EV3_MATH_TEST_DIR}/test_Vector2.cpp
    ${EV3_MATH_TEST_DIR}/test_Vector3.cpp
    ${EV3_MATH_TEST_DIR}/test_Line.cpp
)

# check if the variable exists
if(DEFINED EV3_TESTS_SRC)
  message(STATUS "EV3_TESTS_SRC is defined")
    # add all test files to the test executable
    LIST(APPEND EV3_TESTS_SRC ${EV3_MATH_TEST_SRC})
else()
  message(STATUS "EV3_TESTS_SRC is not defined")
endif()

add_executable(EV3_math_test ${EV3_TESTS_SRC})

target_sources(EV3_math_test
    PRIVATE
        ${EV3_MATH_TEST_SRC}
    )

target_include_directories(EV3_math_test PUBLIC ${EV3_MATH_INCLUDE_DIR})
target_include_directories(EV3_math_test PRIVATE ${EV3_MATH_SRC_DIR})

target_link_libraries(EV3_math_test PUBLIC gtest_main Line Vector2 Vector3)