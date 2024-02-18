#include <physical/portManager/DeviceFactory.hpp>

namespace finder
{
    namespace physical
    {
        DeviceManager DeviceFactory::_device_manager = DeviceManager();
        std::vector<std::shared_ptr<Port>> DeviceFactory::_borrowed_ports = std::vector<std::shared_ptr<Port>>();

        std::shared_ptr<Port> DeviceFactory::borrowDevice(DeviceManager::DeviceType type, DeviceManager::DevicePort port)
        {
            for (auto &borrowed_port : _borrowed_ports)
            {
            }
        }

        Port DeviceFactory::returnDevice(std::shared_ptr<Port> port)
        {
        }
    } // namespace physical
    
} // namespace finder