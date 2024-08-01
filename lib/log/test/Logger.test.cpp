#include <gtest/gtest.h>

#include <Logger.hpp>

TEST(Logger, log) {
    using namespace finder::log;

    Logger logger;

    logger.log(LogLevel::DEBUG, "Debug message");
    logger.log(LogLevel::INFO, "Info message");
    logger.log(LogLevel::WARN, "Warn message");
    logger.log(LogLevel::ERROR, "Error message");
    logger.log(LogLevel::POSITIVE, "Positive message");
    logger.log((LogLevel)10, "Unknown level message");

    logger.debug("Debug message");
    logger.info("Info message");
    logger.warn("Warn message");
    logger.error("Error message");
    logger.positive("Positive message");

    logger.debug(LogLevel::DEBUG);
    logger.info(LogLevel::INFO);
    logger.warn(LogLevel::WARN);
    logger.error(LogLevel::ERROR);
    logger.positive(LogLevel::POSITIVE);
    logger.debug((LogLevel)10);

    ASSERT_EQ(logger.getActiveLogLevel(), LogLevel::DEBUG);
}

TEST(Logger, enforceLogLevel) {
    using namespace finder::log;

    Logger logger;

    logger.enforceLogLevel(LogLevel::INFO);

    ASSERT_EQ(logger.getActiveLogLevel(), LogLevel::INFO);
    ASSERT_EQ(logger.getMinLevel(), LogLevel::DEBUG);

    logger.enforceLogLevel(LogLevel::ERROR);

    ASSERT_EQ(logger.getActiveLogLevel(), LogLevel::ERROR);
    ASSERT_EQ(logger.getMinLevel(), LogLevel::DEBUG);
}

TEST(Logger, setMinLevel) {
    using namespace finder::log;

    Logger logger(LogLevel::INFO);

    logger.removeLogLevelEnforcement();
    logger.setMinLevel(LogLevel::INFO);

    logger.log(LogLevel::DEBUG, logger.getActiveLogLevel());

    ASSERT_EQ(logger.getActiveLogLevel(), LogLevel::INFO);
    ASSERT_EQ(logger.getMinLevel(), LogLevel::INFO);

    logger.setMinLevel(LogLevel::ERROR);

    ASSERT_EQ(logger.getActiveLogLevel(), LogLevel::ERROR);
    ASSERT_EQ(logger.getMinLevel(), LogLevel::ERROR);
}