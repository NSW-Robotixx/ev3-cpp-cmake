// #include <console/Logger.hpp>
#include "Logger.hpp"

namespace finder
{
    namespace console
    {
        bool Logger::_logLevelEnforced = false;
        Logger::LogLevel Logger::_enforcedLogLevel = Logger::LogLevel::DEBUG;

        Logger::Logger(LogLevel minLogLevel) {
            _minlLevel = minLogLevel;
        }

        Logger::LogLevel Logger::getActiveLogLevel()
        {
            if (_logLevelEnforced)
            {
                return _enforcedLogLevel;
            }
            return _minlLevel;
        }

        void Logger::log(LogLevel level, const std::string& message)
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
                        std::cout << color << "[POSITIVE]" << "\033[0m " << "\033[32m";
                        break;
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

        void Logger::error(const LogLevel& message)
        {
            log(LogLevel::ERROR, message);
        }

        void Logger::warn(const std::string& message)
        {
            log(LogLevel::WARN, message);
        }

        void Logger::warn(const LogLevel& message)
        {
            log(LogLevel::WARN, message);
        }

        void Logger::info(const std::string& message)
        {
            log(LogLevel::INFO, message);
        }

        void Logger::info(const LogLevel& message)
        {
            log(LogLevel::INFO, message);
        }

        void Logger::debug(const std::string& message)
        {
            log(LogLevel::DEBUG, message);
        }

        void Logger::debug(const LogLevel& message)
        {
            log(LogLevel::DEBUG, message);
        }

        void Logger::positive(const std::string& message)
        {
            log(LogLevel::POSITIVE, message);
        }

        void Logger::positive(const LogLevel& message)
        {
            log(LogLevel::POSITIVE, message);
        }
        
        void Logger::enforceLogLevel(LogLevel level)
        {
            _logLevelEnforced = true;
            _enforcedLogLevel = level;
        }
    } // namespace console
    
} // namespace finder
