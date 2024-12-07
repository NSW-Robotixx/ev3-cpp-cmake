// NO MODIFICATIONS NEEDED HERE
// This file is used to include all the test files in the project

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

int main(int argc, char const *argv[])
{
    testing::InitGoogleTest(&argc, (char **)argv);
    return RUN_ALL_TESTS();    
}
