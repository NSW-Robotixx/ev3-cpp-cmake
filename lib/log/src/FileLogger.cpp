#include "FileLogger.hpp"
#include "FileLogger.hpp"

namespace finder::log {
    std::ofstream FileLogger::_file;
    bool FileLogger::_input_finished = true;

    FileLogger::FileLogger() {
        _file.open(DEFAULT_LOG_FILE, std::ios::trunc);
        if (_file.bad()) {
			throw std::runtime_error("File is bad");
		}
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
            if (!openFile())
            {
                throw std::runtime_error("File is not open");
            }
        }
        _file << message;
        _file.flush();
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

    bool finder::log::FileLogger::openFile()
    {
        if (!_file.is_open()) {
            _file.open(DEFAULT_LOG_FILE, std::ios::trunc);
        }
		if (_file.bad()) {
            return false;
		}
		if (!_file.is_open()) {
            return false;
		}
		return true;
    }
} // namespace finder::log