#include <physical/portManager/PortManager.hpp>

namespace finder
{
    namespace physical
    {
        std::vector<std::shared_ptr<Port>> PortManager::_borrowed_ports = std::vector<std::shared_ptr<Port>>();
        int PortManager::_read_ports_future;
        bool PortManager::_ports_read = false;
        path_port_t PortManager::_sensor_dir = "/sys/class/lego-sensor";
        path_port_t PortManager::_motor_dir = "/sys/class/tacho-motor";
        std::vector<std::shared_ptr<Port>> PortManager::_ports;
        std::vector<std::string> PortManager::adresses;
        ::finder::console::Logger PortManager::_logger = ::finder::console::Logger{};

        PortManager::PortManager() 
        {
            init();
        }

        PortManager::PortManager(path_port_t dir)
        {
            _sensor_dir = dir + "/lego-sensor";
            _motor_dir = dir + "/tacho-motor";
            init();
        }
        
        void PortManager::readPorts() 
        {
                using namespace ::finder::console;

                std::array<const std::string, 2> dirs = {_sensor_dir, _motor_dir};

                int foundDevices = 0;

                for (const path_port_t& device_type_dir : dirs) {
                    if (!std::filesystem::exists(device_type_dir)) {
                        _logger.log(Logger::LogLevel::WARN, "Skipping directory: " + device_type_dir);
                        std::cout << "Skipping directory: " << device_type_dir << std::endl;
                        continue;
                    }

                    DIR *directory = opendir(device_type_dir.c_str());
                    struct dirent *entry;
                    // entry = readdir(directory);

                    while ((entry = readdir(directory)) != nullptr) {
                        // std::cout << entry->d_name << std::endl;
                        if (std::string{entry->d_name}.find(".") == std::string::npos) {
                            Port port{device_type_dir + "/" + std::string{entry->d_name}};
                            _logger.log(Logger::LogLevel::DEBUG, "PortBasePath:" + port.getBasePath());

                            //read file
                            std::ifstream file(port.getAddressPath());
                            std::string line;
                            std::getline(file, line);
                            file.close();

                            line.erase(std::remove_if(
                                line.begin(),
                                line.end(),
                                [](unsigned char c){
                                    return !std::isprint(c);
                                }),
                                line.end()
                            );
                            
                            for (auto &address : adresses) {
                                if (address == line) {
                                    _logger.log(Logger::LogLevel::INFO, "Port found: " + line);
                                    _ports.push_back(std::shared_ptr<Port>(new Port{port.getBasePath()}));
                                    foundDevices++;
                                    break;
                                }
                            }
                        }
                    }
                    closedir(directory);

                }
                _ports_read = true;
                _read_ports_future = foundDevices;
            // });
        }

        void PortManager::init()
        {
            adresses.clear();
            adresses.push_back(std::string{"ev3-ports:in1"});
            adresses.push_back(std::string{"ev3-ports:in2"});
            adresses.push_back(std::string{"ev3-ports:in3"});
            adresses.push_back(std::string{"ev3-ports:in4"});
            adresses.push_back(std::string{"ev3-ports:outA"});
            adresses.push_back(std::string{"ev3-ports:outB"});
            adresses.push_back(std::string{"ev3-ports:outC"});
            adresses.push_back(std::string{"ev3-ports:outD"});
        }

        std::shared_ptr<Port> PortManager::borrowRaw(std::string port_address)
        {
            return borrowDevice(DeviceType::ANY, port_address);
        }

        std::shared_ptr<Port> PortManager::borrowDevice(DeviceType type, std::string port_address)
        {
            // check if addess is valid
            for (auto &address : adresses) {
                if (address == port_address) {
                    _logger.positive("Found port: " + port_address + " (borrowDevice)");
                    // get correct port
                    for (auto &port : _ports) {
                        _logger.debug("port->getPortKey(): " + std::string{port->getPortKey()} + " port_address.back(): " + port_address.back() + " (borrowDevice)");
                        if (port->getPortKey() == port_address.back()) {
                            _logger.positive("Port key matches: " + std::string{port_address.back()} + " (borrowDevice)");
                            // set port as borrowed
                            _borrowed_ports.push_back(port);
                            if (port->getDeviceType() != type || port->getDeviceType() == DeviceType::UNKNOWN) {
                                if (type != DeviceType::ANY) {
                                    _logger.warn("Port is not of the correct type: " + port_address + " type: " + std::to_string((int)(type)) + " (borrowDevice)");

                                    // should throw an error here but not enough time to fix all the errors
                                    // throw std::logic_error("Port is not of the correct type: " + port_address + " (borrowDevice)");
                                } else {
                                    _logger.log(::finder::console::Logger::LogLevel::INFO, "Port is not of the correct type: " + port_address + " (borrowDevice)");
                                }
                            }
                            _logger.debug("Port borrowed: " + _borrowed_ports.back()->getBasePath() + " (borrowDevice)");
                            return _borrowed_ports.back();
                        }
                    }
                } else {
                    _logger.debug("address: " + address + " (borrowDevice)");
                    _logger.debug("Port not found: " + port_address + " (borrowDevice)");
                }
            }
            return std::shared_ptr<Port>(new Port{});
        }

        std::shared_ptr<SensorPort> PortManager::borrowSensor(std::string port_address)
        {
            return std::shared_ptr<SensorPort>(new SensorPort{borrowDevice(DeviceType::SENSOR, port_address)});
        }

        std::shared_ptr<MotorPort> PortManager::borrowMotor(std::string port_address)
        {
            return std::shared_ptr<MotorPort>(new MotorPort{borrowDevice(DeviceType::MOTOR, port_address)});
        }

        void PortManager::returnDevice(std::shared_ptr<Port> port)
        {
            for (auto &borrowed_port : _borrowed_ports) {
                if (borrowed_port->getPortKey() == port->getPortKey()) {
                    _borrowed_ports.erase(std::remove(_borrowed_ports.begin(), _borrowed_ports.end(), borrowed_port), _borrowed_ports.end());
                    return;
                }
            }
            throw std::logic_error("Port not found: " + port->getBasePath() + " (returnDevice)");
        }

        void PortManager::returnDevice(std::shared_ptr<SensorPort> port)
        {
            returnDevice(std::dynamic_pointer_cast<Port>(port));
        }

        void PortManager::returnDevice(std::shared_ptr<MotorPort> port)
        {
            returnDevice(std::dynamic_pointer_cast<Port>(port));
        }
    } // namespace physical

} // namespace finder

