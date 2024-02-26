#include <physical/portManager/port/Port.hpp>
#include "Port.hpp"

namespace finder
{
    namespace physical
    {
        ::finder::console::Logger Port::_logger = ::finder::console::Logger{};

        Port::Port()
        {
            _f_enabled = std::async(std::launch::async, [this]{return initFiles();});
        }

        Port::Port(const path_port_t &port)
        {
            setBasePath(port);
        }

        Port::Port(std::shared_ptr<Port> port)
        {
            setBasePath(port->getBasePath());
        }

        void Port::setBasePath(const path_port_t &path)
        {
            _path = path;
            _f_enabled = std::async(std::launch::async, [this]{return initFiles();});
        }

        char Port::getPortKey()
        {
            if (isEnabled())
            {
                return _path.back();
            } else {
                return '-';
            }
        }
        
        path_port_t Port::getBasePath()
        {
            if (isEnabled()) {
                return _path;
            } else {
                return "";
            }
        }

        path_address_t Port::getAddressPath()
        {
            if (isEnabled()) {
                return _path + "/address";
            } else {
                return "";
            }
        }

        path_value_t Port::getValuePath()
        {
            if (isEnabled()) {
                return _path + "/value0";
            } else {
                return "";
            }
        }

        path_mode_t Port::getModePath()
        {
            if (isEnabled()) {
                return _path + "/mode";
            } else {
                return "";
            }
        }

        bool Port::initFiles()
        {
            using namespace ::finder::console;

            if (
                std::filesystem::exists(getAddressPath()) == false ||
                std::filesystem::exists(getValuePath()) == false ||
                std::filesystem::exists(getModePath()) == false
            ) {
                _logger.log(
                    Logger::LogLevel::DEBUG, 
                    "Port files not found at: " + getAddressPath()
                );
            } else {
                _file_address_path = std::make_shared<std::ifstream>();
                _file_value_path = std::make_shared<std::ifstream>();
                _file_mode_path = std::make_shared<std::ifstream>();

                _file_address_path->open(getAddressPath());
                _file_value_path->open(getValuePath());
                _file_mode_path->open(getModePath());
                if (
                    _file_address_path->is_open() == false ||
                    _file_value_path->is_open() == false ||
                    _file_mode_path->is_open() == false
                ) {
                _logger.log(
                        Logger::LogLevel::WARN, 
                        "Failed to open port files at: " + getAddressPath()
                    ); 
                } else {
                    return true;
                }
            }
            return false;
        }

        bool Port::isEnabled()
        {
            if (_f_enabled.valid()) {
                _f_enabled.wait();
            }
            return _f_enabled.get();
        }
    } // namespace physical
} // namespace finder
