#include <iostream>
#include <console/Logger.hpp>

int main(int argc, char const *argv[])
{
    using namespace finder::console;

    Logger logger = Logger(Logger::LogLevel::DEBUG);

    logger.log(Logger::LogLevel::DEBUG, "DEBUG message");
    logger.log(Logger::LogLevel::INFO, "INFO message");
    logger.log(Logger::LogLevel::WARN, "WARN message");
    logger.log(Logger::LogLevel::ERROR, "ERROR message");


    return 0;
}
