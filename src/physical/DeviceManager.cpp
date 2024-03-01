#include <physical/DeviceManager.hpp>

namespace finder
{
    namespace physical
    {
        std::shared_ptr<PortManager> DeviceManager::_portManager;
        std::shared_ptr<SensorPort> DeviceManager::_gyroSensor;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorLeft;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorRight;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorFront;
        std::shared_ptr<MotorPort> DeviceManager::_motorLeft;
        std::shared_ptr<MotorPort> DeviceManager::_motorRight;
        std::shared_ptr<MotorPort> DeviceManager::_motorShift;
        std::shared_ptr<MotorPort> DeviceManager::_motorTool;
        bool DeviceManager::_initialized = false;


        DeviceManager::DeviceManager()
        {
            if (!_initialized)
            {
                init();
            }
        }

        DeviceManager::~DeviceManager()
        {
        }

        void DeviceManager::init()
        {
            _portManager = std::make_shared<PortManager>();
            _portManager->readPorts();

            _gyroSensor = _portManager->borrowSensor(_portManager->adresses[0]);
        }
    } // namespace physical
    
} // namespace finder

