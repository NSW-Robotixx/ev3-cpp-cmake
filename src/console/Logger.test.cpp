#include <gtest/gtest.h>

#include <console/Logger.hpp>

TEST(Logger, constructor) {
    using namespace finder::console;
    Logger logger;

    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::INFO);
}

TEST(Logger, functionsetLevel) {
    using namespace finder::console;
    Logger logger;
    logger.setMinLevel(Logger::LogLevel::ERROR);

    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::ERROR);
}