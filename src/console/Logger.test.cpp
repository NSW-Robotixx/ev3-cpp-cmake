#include <gtest/gtest.h>

#include "console/Logger.hpp"

TEST(Logger, log) {
    using namespace finder::console;

    Logger logger;

    logger.log(Logger::LogLevel::DEBUG, "Debug message");
    logger.log(Logger::LogLevel::INFO, "Info message");
    logger.log(Logger::LogLevel::WARN, "Warn message");
    logger.log(Logger::LogLevel::ERROR, "Error message");
}

TEST(Logger, enforceLogLevel) {
    using namespace finder::console;

    Logger logger;

    logger.enforceLogLevel(Logger::LogLevel::INFO);

    ASSERT_EQ(logger.getActiveLogLevel(), Logger::LogLevel::INFO);
    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::DEBUG);

    logger.enforceLogLevel(Logger::LogLevel::ERROR);

    ASSERT_EQ(logger.getActiveLogLevel(), Logger::LogLevel::ERROR);
    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::DEBUG);
}

TEST(Logger, setMinLevel) {
    using namespace finder::console;

    Logger logger(Logger::LogLevel::INFO);

    logger.removeLogLevelEnforcement();
    logger.setMinLevel(Logger::LogLevel::INFO);

    logger.log(Logger::LogLevel::DEBUG, logger.getActiveLogLevel());

    ASSERT_EQ(logger.getActiveLogLevel(), Logger::LogLevel::INFO);
    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::INFO);

    logger.setMinLevel(Logger::LogLevel::ERROR);

    ASSERT_EQ(logger.getActiveLogLevel(), Logger::LogLevel::ERROR);
    ASSERT_EQ(logger.getMinLevel(), Logger::LogLevel::ERROR);
}