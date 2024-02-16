#include <physical/portManager/DeviceManager.hpp>

namespace finder
{
    namespace physical
    {
        path_port_t DeviceManager::_sensor_dir = "/sys/class/lego-sensor";
        path_port_t DeviceManager::_motor_dir = "/sys/class/tacho-motor";
        Ports DeviceManager::_ports;
        Adresses DeviceManager::_adresses;

        DeviceManager::DeviceManager() 
        {
            init();
        }

        DeviceManager::DeviceManager(path_port_t dir)
        {
            _sensor_dir = dir + "/lego-sensor";
            _motor_dir = dir + "/tacho-motor";
            init();
        }

        int DeviceManager::readPorts()
        {
            std::array<const std::string, 2> dirs = {_sensor_dir, _motor_dir};

            int foundDevices = 0;

            for (const path_port_t& sensor_type : dirs) {
                if (!std::filesystem::exists(sensor_type)) {
                    continue;
                }

                DIR *directory = opendir(sensor_type.c_str());
                struct dirent *entry;
                // entry = readdir(directory);

                while ((entry = readdir(directory)) != nullptr) {
                    // std::cout << entry->d_name << std::endl;
                    if (std::string{entry->d_name}.find(".") == std::string::npos) {
                        Port port{sensor_type + "/" + std::string{entry->d_name}};

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

                        if (line == _adresses.input_1) {_ports.input_1.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.input_2) {_ports.input_2.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.input_3) {_ports.input_3.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.input_4) {_ports.input_4.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.output_A) {_ports.output_A.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.output_B) {_ports.output_B.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.output_C) {_ports.output_C.setBasePath(port.getBasePath()); foundDevices++;}
                        else if (line == _adresses.output_D) {_ports.output_D.setBasePath(port.getBasePath()); foundDevices++;}
                        else {
                            std::cerr << "port not recognized" << std::endl;
                            // closedir(directory);
                            // throw new std::invalid_argument("sensor port not recognized");
                        }
                    }


                }
                closedir(directory);

            }
            return foundDevices;
        }

        void DeviceManager::init()
        {
            _adresses.input_1 = std::string{"ev3-ports:in1"};
            _adresses.input_2 = std::string{"ev3-ports:in2"};
            _adresses.input_3 = std::string{"ev3-ports:in3"};
            _adresses.input_4 = std::string{"ev3-ports:in4"};
            _adresses.output_A = std::string{"ev3-ports:outA"};
            _adresses.output_B = std::string{"ev3-ports:outB"};
            _adresses.output_C = std::string{"ev3-ports:outC"};
            _adresses.output_D = std::string{"ev3-ports:outD"};
        }
    } // namespace physical

} // namespace finder

