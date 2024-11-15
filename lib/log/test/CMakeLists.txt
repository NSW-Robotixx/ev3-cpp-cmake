# file(GLOB_RECURSE EV3_FILESYSTEM_TEST_HDR CONFIGURE_DEPENDS "*.hpp")

find_package(log4cplus REQUIRED)

set(EV3_LOGGER_TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.test.cpp
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
    set_property(GLOBAL PROPERTY EV3_TESTS_LIBS ${EV3_TESTS_LIBS} Logger log4cplus::log4cplus)
else()
    message(STATUS "EV3_TESTS_SRC is not defined")
endif()
