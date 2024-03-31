#include <gtest/gtest.h>

#include "console/Logger.hpp"

TEST(Logger, log) {
    using namespace finder::console;

    Logger logger;

    logger.log(Logger::LogLevel::DEBUG, "Debug message");
    logger.log(Logger::LogLevel::INFO, "Info message");
    logger.log(Logger::LogLevel::WARN, "Warn message");
    logger.log(Logger::LogLevel::ERROR, "Error message");
    logger.log(Logger::LogLevel::POSITIVE, "Positive message");
    logger.log((Logger::LogLevel)10, "Unknown level message");

    logger.debug("Debug message");
    logger.info("Info message");
    logger.warn("Warn message");
    logger.error("Error message");
    logger.positive("Positive message");

    logger.debug(Logger::LogLevel::DEBUG);
    logger.info(Logger::LogLevel::INFO);
    logger.warn(Logger::LogLevel::WARN);
    logger.error(Logger::LogLevel::ERROR);
    logger.positive(Logger::LogLevel::POSITIVE);

    ASSERT_EQ(logger.getActiveLogLevel(), Logger::LogLevel::DEBUG);
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