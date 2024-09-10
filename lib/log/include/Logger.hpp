#include <iostream>
#include <string>

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

namespace finder
{
    namespace log
    {
        enum class LogLevel {
            DEBUG = 0,
            INFO = 1,
            POSITIVE = 2,
            WARN = 3,
            ERROR = 4,
            SILENT = 5
        };
        
        class Logger {
            public:


                Logger() = default;
                Logger(LogLevel minLogLevel) { _minlLevel = minLogLevel; };

                LogLevel getMinLevel() { return _minlLevel; }
                static LogLevel getActiveLogLevel();

                void setMinLevel(LogLevel level) {_minlLevel = level;}

                Logger& operator<<(const std::string& message);

                static void log(LogLevel level, const std::string& message);
                static void log(LogLevel level, const LogLevel& message);

                static void error(const std::string& message);
                static void error(const LogLevel& message);

                static void warn(const std::string& message);
                static void warn(const LogLevel& message);

                static void info(const std::string& message);
                static void info(const LogLevel& message);

                static void debug(const std::string& message);
                static void debug(const LogLevel& message);

                static void positive(const std::string& message);
                static void positive(const LogLevel& message);
                static void success(const std::string& message) { Logger::positive(message); };


            private:
                static LogLevel _minlLevel;
        };
    } // namespace log
} // namespace finder

#endif // __LOGGER_HPP__