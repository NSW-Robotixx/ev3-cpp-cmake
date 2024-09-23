// #include <log/Logger.hpp>
#include "Logger.hpp"

namespace finder
{
    namespace log
    {
        LogLevel Logger::_minlLevel = LogLevel::DEBUG;

        LogLevel Logger::getActiveLogLevel()
        {
            return _minlLevel;
        }

        Logger& Logger::operator<<(const std::string &message)
        {
            debug(message);
            return *this;
        }

        void Logger::log(LogLevel level, const std::string &message)
        {
            if (level >= getActiveLogLevel())
            {
                std::string color;
                switch (level)
                {
                    case LogLevel::DEBUG:
                        color = "";
                        std::cout << color << "[DEBUG] ";
                        break;
                    case LogLevel::INFO:
                        color = "\033[3;44;30m";
                        std::cout << color << "[INFO]" << "\033[0m " << "\033[34m";
                        break;
                    case LogLevel::WARN:
                        color = "\033[3;43;30m";
                        std::cout << color << "[WARN]" << "\033[0m " << "\033[33m";
                        break;
                    case LogLevel::ERROR:
                        color = "\033[3;41;30m";
                        std::cout << color << "[ERROR]" << "\033[0m " << "\033[31m";
                        break;
                    case LogLevel::POSITIVE:
                        color = "\033[3;42;30m";
                        std::cout << color << "[SUCCESS]" << "\033[0m " << "\033[32m";
                        break;
                    case LogLevel::SILENT:
                        return;
                    default:
                        color = "\033[3;47;35m";
                        break;
                }
                std::cout << message << "\033[0m" << std::endl;
            }

        }

        void Logger::log(LogLevel level, const LogLevel& message)
        {
            log(level, std::to_string(static_cast<int>(message)));
        }

        void Logger::error(const std::string& message)
        {
            log(LogLevel::ERROR, message);
        }

        void Logger::warn(const std::string& message)
        {
            log(LogLevel::WARN, message);
        }

        void Logger::info(const std::string& message)
        {
            log(LogLevel::INFO, message);
        }

        void Logger::debug(const std::string& message)
        {
            log(LogLevel::DEBUG, message);
        }

        void Logger::positive(const std::string& message)
        {
            log(LogLevel::POSITIVE, message);
        }
    } // namespace log
    
} // namespace finder
