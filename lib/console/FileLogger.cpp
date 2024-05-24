#include "FileLogger.hpp"

namespace finder::console {
    std::ofstream FileLogger::_file;
    bool FileLogger::_input_finished = true;

    FileLogger::FileLogger() {
        _file.open(DEFAULT_LOG_FILE, std::ios::trunc);
        if (!_file.is_open()) {
            throw std::runtime_error("Could not open file " + std::string(DEFAULT_LOG_FILE));
        }
    }

    void FileLogger::logToFile(const std::string& message) {
        _input_finished = false;

        if (_file.bad()) {
            throw std::runtime_error("File is bad");
        }
        if (!_file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        _file << message;
    }

    void FileLogger::endLogFileMessage() {
        if (_file.bad()) {
            throw std::runtime_error("File is bad");
        }
        if (!_file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        _file << std::endl;
        _input_finished = true;
    }

    void FileLogger::clear() {
        _file.close();
        _file.open(DEFAULT_LOG_FILE, std::ios::trunc);
    }
} // namespace finder::console