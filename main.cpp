#include <console/Logger.hpp>

finder::console::Logger logger = finder::console::Logger();

int main(int argc, char const *argv[])
{
    logger.log(finder::console::Logger::LogLevel::WARN, "Hello, World!");
    return 0;
}
