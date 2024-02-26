#include <iostream>

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

namespace finder
{
    namespace console
    {
        class Logger {
            public:
                enum class LogLevel {
                    DEBUG = 0,
                    INFO = 1,
                    WARN = 2,
                    ERROR = 3
                };

                Logger() : _minlLevel(LogLevel::DEBUG) {}
                Logger(LogLevel minLogLevel);

                LogLevel getMinLevel() {return _minlLevel;}
                LogLevel getActiveLogLevel();

                void setMinLevel(LogLevel level) {_minlLevel = level;}

                void log(LogLevel level, const std::string& message);
                void log(LogLevel level, const LogLevel& message);

                void error(const std::string& message);
                void error(const LogLevel& message);

                void warn(const std::string& message);
                void warn(const LogLevel& message);

                void info(const std::string& message);
                void info(const LogLevel& message);

                void debug(const std::string& message);
                void debug(const LogLevel& message);

                static void enforceLogLevel(LogLevel level);
                static void removeLogLevelEnforcement() {_logLevelEnforced = false;}
                static bool isLogLevelEnforced() {return _logLevelEnforced;}

            private:
                LogLevel _minlLevel;
                static bool _logLevelEnforced;
                static LogLevel _enforcedLogLevel;
        };
    } // namespace console
} // namespace finder

#endif // __LOGGER_HPP__