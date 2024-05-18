#ifndef __FILE_LOGGER_HPP__
#define __FILE_LOGGER_HPP__

#include <string>
#include <fstream>
#include <ios>
#include <console/Logger.hpp>

#define DEFAULT_LOG_FILE "./logfile.log"

namespace finder::console {
    class FileLogger : public Logger{
        public:
            FileLogger();
            ~FileLogger() = default;

            struct FileLoggerLock {
                FileLoggerLock() = default;
                ~FileLoggerLock() {
                    endLogFileMessage();
                }
            };


            /// @brief Log a message to the file, finish the message by letting the FileLoggerLock destructor be called.
            /// @param message The message to log
            void logToFile(const std::string& message);

            /// @brief Finish the message in the file by allowing the FileLoggerLock destructor to be called.
            /// @warning This should not be called directly, use the FileLoggerLock instead.
            static void endLogFileMessage();

            /// @brief Clear the log file content
            /// @warning This will delete all the content of the file, should be used with caution.
            void clear();

        private:
            static std::ofstream _file;
            static bool _input_finished;
    };
} // namespace finder::console

#endif // __FILE_LOGGER_HPP__