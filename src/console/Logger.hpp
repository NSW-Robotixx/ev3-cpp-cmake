#include <iostream>

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
