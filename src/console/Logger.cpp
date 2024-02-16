#include <console/Logger.hpp>

namespace finder
{
    namespace console
    {
        void Logger::log(LogLevel level, const std::string& message)
        {
            if (level >= _minlLevel)
            {
                std::string color;
                switch (level)
                {
                    case LogLevel::DEBUG:
                        color = "\033[3;42;30m";
                        break;
                    case LogLevel::INFO:
                        color = "\033[3;47;35m";
                        break;
                    case LogLevel::WARN:
                        color = "\033[3;43;30m";
                        break;
                    case LogLevel::ERROR:
                        color = "\033[3;41;37m";
                        break;
                    default:
                        color = "\033[3;47;35m";
                        break;
                }
                std::cout << color << message << "\033[0m" << std::endl;
            }
        }
    } // namespace console
    
} // namespace finder
