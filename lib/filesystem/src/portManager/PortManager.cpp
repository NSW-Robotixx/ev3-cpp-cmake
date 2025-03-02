#include "PortManager.hpp"

namespace finder
{
    namespace physical
    {
        std::vector<std::shared_ptr<Port>> PortManager::_borrowed_ports = std::vector<std::shared_ptr<Port>>();
        int PortManager::_read_ports_future;
        bool PortManager::_ports_read = false;
        path_port_t PortManager::_sensor_dir = "/sys/class/lego-sensor";
        path_port_t PortManager::_motor_dir = "/sys/class/tacho-motor";
        std::vector<std::string> PortManager::adresses;
        std::array<std::shared_ptr<SensorPort>, MAX_SENSORS> PortManager::_sensor_ports;
        std::array<std::shared_ptr<MotorPort>, MAX_MOTORS> PortManager::_motor_ports;

        PortManager::PortManager() 
        {
            spdlog::trace("PortManager::PortManager()");
            init();
        }

        PortManager::PortManager(path_port_t dir)
        {
            spdlog::trace("PortManager::PortManager(path_port_t dir)");
            _sensor_dir = dir + "/lego-sensor";
            _motor_dir = dir + "/tacho-motor";
            init();
        }

        PortManager::~PortManager()
        {
        }

        void PortManager::readPorts() 
        {
            spdlog::trace("PortManager::readPorts()");

                std::array<const std::string, 2> dirs = {_sensor_dir, _motor_dir};

                int foundDevices = 0;

                for (const path_port_t& device_type_dir : dirs) {
                    if (!std::filesystem::exists(device_type_dir)) {
                        spdlog::error("Directory not found: {} invalid path", device_type_dir.c_str());
                        // throw std::logic_error("Directory not found: " + device_type_dir + " invalid path");
                        continue;
                    }

                    std::filesystem::path path = device_type_dir;

                    std::filesystem::directory_iterator directory(path);
                    // entry = readdir(directory);

                    for (const auto& dir_entry : std::filesystem::directory_iterator{ path }) {
                        // std::cout << entry->d_name << std::endl;
                        // Port port{device_type_dir + "/" + std::string{entry->d_name}};

                        boost::leaf::result<path_address_t> port = Port::getAddressPath(dir_entry.path().string());
                        if (!port) {
                            spdlog::error("Error getting port address");
                            continue;
                        }
                        spdlog::debug("Checking port: %s", port.value().c_str());
                        //read file
                        std::ifstream file(port.value());
                        std::string line;
                        std::getline(file, line);
                        file.close();

                        line.erase(std::remove_if(
                            line.begin(),
                            line.end(),
                            [](unsigned char c) {
                                return !std::isprint(c);
                            }),
                            line.end()
                        );

                        for (auto& address : adresses) {
                            if (address == line) {
                                spdlog::debug("Found device: %s", address.c_str());
                                if (device_type_dir == _sensor_dir) {
                                    _sensor_ports[address.back() - '1'] = std::make_shared<SensorPort>(dir_entry.path().string());
                                } else {
                                    _motor_ports[address.back() - 'A'] = std::make_shared<MotorPort>(dir_entry.path().string());
                                }
                                foundDevices++;
                                break;
                            }
                        }
                    }

                }
                _ports_read = true;
                _read_ports_future = foundDevices;
                if (foundDevices > 8) {
                    throw std::logic_error("Too many devices found: " + std::to_string(foundDevices));
                }
            // });
        }

        void PortManager::init()
        {
            spdlog::trace("PortManager::init()");

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


        

        std::shared_ptr<Port> PortManager::borrowDevice(DevicePort port_address)
        {
            spdlog::trace("PortManager::borrowDevice(DevicePort port_address)");

            if (!_ports_read) {
                readPorts();
            }

            // check if requested device is a sensor or motor
            if (port_address >= EV3_PORT_INPUT_1 && port_address <= EV3_PORT_INPUT_4) {
                return std::shared_ptr<Port>(new Port{_sensor_ports[port_address - '1']});
            } else if (port_address >= EV3_PORT_OUTPUT_A && port_address <= EV3_PORT_OUTPUT_D) {
                return std::shared_ptr<Port>(new Port{_motor_ports[static_cast<char>(port_address) - 'A']});
            } else {
                throw std::logic_error("Port not found: " + std::to_string(static_cast<char>(port_address)) + " (borrowDevice)");
            }
        }

        std::shared_ptr<SensorPort> PortManager::borrowSensor(DevicePort port_address)
        {
            spdlog::trace("PortManager::borrowSensor(DevicePort port_address)");

            return _sensor_ports[static_cast<char>(port_address) - '1'];
        }

        std::shared_ptr<SensorPort> PortManager::borrowSensor(DeviceID port)
        {
            spdlog::trace("PortManager::borrowSensor(DeviceID port)");

            return borrowSensor(static_cast<DevicePort>(port));
        }

        std::shared_ptr<MotorPort> PortManager::borrowMotor(DevicePort port)
        {
            spdlog::trace("PortManager::borrowMotor(DevicePort port)");

            try
            {
                return _motor_ports[static_cast<char>(port) - 'A'];
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return std::shared_ptr<MotorPort>(new MotorPort(""));
            }
        }

        std::shared_ptr<MotorPort> PortManager::borrowMotor(DeviceID port_address)
        {
            spdlog::trace("PortManager::borrowMotor(DeviceID port_address)");
            
            return borrowMotor(static_cast<char>(port_address));
        }

    } // namespace physical

} // namespace finder

