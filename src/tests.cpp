// NO MODIFICATIONS NEEDED HERE
// This file is used to include all the test files in the project

#include <gtest/gtest.h>
#include <log4cplus/log4cplus.h>

int main(int argc, char const *argv[])
{
    // Initialization and deinitialization.
    log4cplus::Initializer initializer;

    log4cplus::PropertyConfigurator config{LOG4CPLUS_TEXT("")};
    config.configure();

    log4cplus::Logger logger = log4cplus::Logger::getInstance(
        LOG4CPLUS_TEXT("main"));

    log4cplus::SharedAppenderPtr _appender(new log4cplus::FileAppender(LOG4CPLUS_TEXT("test.log")));
    _appender->setName(LOG4CPLUS_TEXT("file"));
    
    log4cplus::Logger::getRoot().addAppender(_appender);

    logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);

    testing::InitGoogleTest(&argc, (char **)argv);
    return RUN_ALL_TESTS();    
}
