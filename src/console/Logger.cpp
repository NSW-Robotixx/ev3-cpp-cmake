#include <console/Logger.hpp>

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
            if (_logLevelEnforced)
            {
                level = _enforcedLogLevel;
            }
            if (level >= _minlLevel)
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

        void Logger::enforceLogLevel(LogLevel level)
        {
            _logLevelEnforced = true;
            _enforcedLogLevel = level;
        }
    } // namespace console
    
} // namespace finder
