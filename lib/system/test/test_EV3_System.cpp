#include <gtest/gtest.h>

#include <EV3_System.hpp>

TEST(EV3_System, DefaultConstructor)
{
    finder::system::System system;
    EXPECT_NO_THROW(system.start());

}