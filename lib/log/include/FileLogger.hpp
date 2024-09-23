#ifndef __FILE_LOGGER_HPP__
#define __FILE_LOGGER_HPP__

#include <string>
#include <fstream>
#include <ios>
#include <Logger.hpp>

#ifndef _MSC_VER
#define DEFAULT_LOG_FILE "./logfile.log"
#else 
#define DEFAULT_LOG_FILE "C:/Users/nikla/source/repos/wandeltn/ev3-cpp-cmake/out/build/x64-Debug/logfile.log"
#endif


namespace finder::log {

    /// @brief Logger that logs messages to a file
    class FileLogger : public Logger{
        public:
            FileLogger();
            ~FileLogger() = default;

            /// @brief Lock that allows the FileLogger to log a message to the file
            struct FileLoggerLock {
                FileLoggerLock() = default;
                ~FileLoggerLock() {
                    openFile();
                    endLogFileMessage();
                }
            };


            /// @brief Log a message to the file, finish the message by letting the FileLoggerLock destructor be called.
            /// @param message to log
            void logToFile(const std::string& message);


            /// @brief Clear the log file content
            /// @warning This will delete all the content of the file, should be used with caution.
            void clear();

            /// @brief Open the file for logging
            /// @return True if the file was opened successfully, false otherwise.
            static bool openFile();

        private:
            static std::ofstream _file;
            static bool _input_finished;

            /// @brief Finish the message in the file by allowing the FileLoggerLock destructor to be called.
            /// @warning This should not be called directly, use the FileLoggerLock instead.
            static void endLogFileMessage();
    };
} // namespace finder::console

#endif // __FILE_LOGGER_HPP__