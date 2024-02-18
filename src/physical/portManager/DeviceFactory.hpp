#include <physical/portManager/DeviceManager.hpp>

namespace finder
{
    namespace physical
    {
        class DeviceFactory {
        public:
            static std::shared_ptr<Port> borrowDevice(DeviceManager::DeviceType type, DeviceManager::DevicePort port);
            static Port returnDevice(std::shared_ptr<Port> port);

        private:
            static DeviceManager _device_manager;
            static std::vector<std::shared_ptr<Port>> _borrowed_ports;          

        };
    } // namespace physical
    
} // namespace finder
