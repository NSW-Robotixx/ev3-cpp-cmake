#include <iostream>
#include <string>
#include <spdlog/spdlog.h>

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
        
        /// @brief Class for logging messages to the console
        class Logger {
            public:


                Logger();

                /// @brief Construct a new Logger object
                /// @param minLogLevel The minimum log level to display
                Logger(LogLevel minLogLevel) { _minlLevel = minLogLevel; };

                /// @brief Get the minimum log level
                /// @return LogLevel The minimum log level                
                LogLevel getMinLevel() { return _minlLevel; }

                /// @brief Get the active log level
                /// @return LogLevel The active log level
                /// @bug This function has no purpose
                static LogLevel getActiveLogLevel();

                /// @brief Set the minimum log level
                /// @param level The minimum log level
                void setMinLevel(LogLevel level) {_minlLevel = level;}

                /// @brief Log a message to the console at debug level
                /// @param message The message to log
                /// @return Logger& The logger object                
                Logger& operator<<(const std::string& message);

                /// @brief Log a message to the console at the specified level
                /// @param level The log level
                /// @param message The message to log
                static void log(LogLevel level, const std::string& message);

                /// @brief Log a message to the console at the specified level
                /// @param level The log level
                /// @param message The message to log
                static void log(LogLevel level, const LogLevel& message);

                /// @brief Log an error message to the console
                /// @details The message should be displayed in red
                /// @param message The error message to log
                static void error(const std::string& message);

                /// @brief Log a warning message to the console
                /// @details The message should be displayed in yellow
                /// @param message The warning message to log
                static void warn(const std::string& message);

                /// @brief Log an info message to the console
                /// @details The message should be displayed in blue
                /// @param message The info message to log
                static void info(const std::string& message);

                /// @brief Log a debug message to the console
                /// @details The message should be displayed in white
                /// @param message The debug message to log
                static void debug(const std::string& message);

                /// @brief Log a positive message to the console
                /// @details The message should be displayed in green
                /// @param message The positive message to log
                static void positive(const std::string& message);

                /// @brief Log a success message to the console
                /// @details The message should be displayed in green
                /// @param message The success message to log
                static void success(const std::string& message) { Logger::positive(message); };


            private:
                static LogLevel _minlLevel;
        };
    } // namespace log
} // namespace finder

#endif // __LOGGER_HPP__