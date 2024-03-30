#include <physical/DeviceManager.hpp>
#include "DeviceManager.hpp"

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

        std::shared_ptr<SensorPort> DeviceManager::getGyroSensor()
        {
            if (!_initialized)
            {
                init();
            }
            return _gyroSensor;
        }

        std::shared_ptr<SensorPort> DeviceManager::getColorSensorLeft()
        {
            if (!_initialized)
            {
                init();
            }
            return _colorSensorLeft;
        }

        std::shared_ptr<SensorPort> DeviceManager::getColorSensorRight()
        {
            if (!_initialized)
            {
                init();
            }
            return _colorSensorRight;
        }

        std::shared_ptr<SensorPort> DeviceManager::getColorSensorFront()
        {
            if (!_initialized)
            {
                init();
            }
            return _colorSensorFront;
        }

        std::shared_ptr<MotorPort> DeviceManager::getMotorLeft()
        {
            if (!_initialized)
            {
                init();
            }
            return _motorLeft;
        }

        std::shared_ptr<MotorPort> DeviceManager::getMotorRight()
        {
            if (!_initialized)
            {
                init();
            }
            return _motorRight;
        }

        std::shared_ptr<MotorPort> DeviceManager::getMotorShift()
        {
            if (!_initialized)
            {
                init();
            }
            return _motorShift;
        }

        std::shared_ptr<MotorPort> DeviceManager::getMotorTool()
        {
            if (!_initialized)
            {
                init();
            }
            return _motorTool;
        }

        void DeviceManager::init()
        {
            _portManager = std::make_shared<PortManager>();
            _portManager->readPorts();

            _gyroSensor = _portManager->borrowSensor(_portManager->adresses[0]);
            _colorSensorLeft = _portManager->borrowSensor(_portManager->adresses[1]);
            _colorSensorRight = _portManager->borrowSensor(_portManager->adresses[2]);
            _colorSensorFront = _portManager->borrowSensor(_portManager->adresses[3]);
            _motorLeft = _portManager->borrowMotor(_portManager->adresses[4]);
            _motorRight = _portManager->borrowMotor(_portManager->adresses[5]);
            _motorShift = _portManager->borrowMotor(_portManager->adresses[6]);
            _motorTool = _portManager->borrowMotor(_portManager->adresses[7]);

            _initialized = true;
        }
    } // namespace physical
    
} // namespace finder

