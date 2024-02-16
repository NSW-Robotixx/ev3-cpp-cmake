add_library(
  testTest
  test2.cpp
)

target_link_libraries(
  testTest
  GTest::gtest_main
)