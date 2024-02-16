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

                Logger() : _minlLevel(LogLevel::INFO) {}

                LogLevel getMinLevel() {return _minlLevel;}
                void setMinLevel(LogLevel level) {_minlLevel = level;}

                void log(LogLevel level, const std::string& message);

            private:
                LogLevel _minlLevel;
        };
    } // namespace console
} // namespace finder
