#include <physical/portManager/DeviceManager.hpp>

namespace finder
{
    namespace physical
    {
        class DeviceFactory {
        public:
            static Port getDevice(DeviceManager::DeviceType type, DeviceManager::DevicePort port) {
                // switch (type) {
                //     case DeviceType::SENSOR:
                //         return getSensor(port);
                //     case DeviceType::MOTOR:
                //         return getMotor(port);
                //     default:
                //         Port ret = Port();
                //         ret.setDisabled();
                //         return ret;
                // }
                Port ret = Port();
                ret.setDisabled();
                return ret;
            };
        
        private:
            static DeviceManager _device_manager;            

        };
    } // namespace physical
    
} // namespace finder
