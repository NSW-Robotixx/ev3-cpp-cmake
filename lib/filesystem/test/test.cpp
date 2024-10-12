#include <gtest/gtest.h>
#include <log4cplus/log4cplus.h>

int main(int argc, char **argv)
{
    // Initialization and deinitialization.
    log4cplus::Initializer initializer;

    log4cplus::BasicConfigurator config;
    config.configure();

    log4cplus::Logger logger = log4cplus::Logger::getInstance(
        LOG4CPLUS_TEXT("main"));
    LOG4CPLUS_WARN(logger, LOG4CPLUS_TEXT("Hello, World!"));

    log4cplus::SharedAppenderPtr _appender(new log4cplus::FileAppender(LOG4CPLUS_TEXT("test.log")));
    _appender->setName(LOG4CPLUS_TEXT("file"));
    logger.addAppender(_appender);

    logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}