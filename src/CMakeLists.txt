add_subdirectory(physical)
add_subdirectory(console)


# testing
add_library(TestSrc STATIC src.test.cpp)

target_include_directories(TestSrc PUBLIC ${PROJECT_SOURCE_DIR}/tests)
target_include_directories(TestSrc PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(
  TestSrc
  device_factory
  GTest::gtest_main
)