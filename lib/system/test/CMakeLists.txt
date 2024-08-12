# file(GLOB_RECURSE EV3_FILESYSTEM_TEST_HDR CONFIGURE_DEPENDS "*.hpp")

set(EV3_LOGGER_TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/test_EV3_System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ConfigReader.cpp
)

get_property(EV3_TESTS_SRC GLOBAL PROPERTY EV3_TESTS_SRC)
get_property(EV3_TESTS_HDR GLOBAL PROPERTY EV3_TESTS_HDR)

# check if EV3_TESTS_SRC is defined
if(EV3_TESTS_SRC)
    # set global property for EV3_TESTS_SRC
    set_property(GLOBAL PROPERTY EV3_TESTS_SRC ${EV3_TESTS_SRC} ${EV3_LOGGER_TEST_SRC})

    # get the global property for the libs to be linked to the test
    get_property(EV3_TESTS_LIBS GLOBAL PROPERTY EV3_TESTS_LIBS)
    
    # add the lib to be linked to the test
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} EV3_system)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()
