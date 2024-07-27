#include <EV3_SensorManager.hpp>

namespace finder::physical
{
    int SensorManager::_gyroValue = 0;
    int SensorManager::_colorLeftValue = 0;
    int SensorManager::_colorRightValue = 0;
    int SensorManager::_colorFrontValue = 0;

    std::mutex SensorManager::_gyroValueMutex;
    std::mutex SensorManager::_colorLeftValueMutex;
    std::mutex SensorManager::_colorRightValueMutex;
    std::mutex SensorManager::_colorFrontValueMutex;

    std::vector<std::map<DeviceType, std::function<void(int)>>> SensorManager::_eventListeners;

    std::mutex SensorManager::_stopDispatcherMutex;
    bool SensorManager::_stopDispatcher = false;
    std::thread SensorManager::_dispatcherFuture;

#ifdef ENABLE_LOGGING
    log::Logger SensorManager::_logger;
#endif

    SensorManager::SensorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _dispatcherFuture = std::thread(Dispatcher);
    }

    SensorManager::~SensorManager()
    {
        {
            std::lock_guard<std::mutex> lock(_stopDispatcherMutex);
            _stopDispatcher = true;
        }
        _dispatcherFuture.join();
    }

    void SensorManager::readAllSensors()
    {
        readGyro();
        readColorLeft();
        readColorRight();
        readColorFront();
    }

    int SensorManager::readGyro()
    {
        _gyroValue = _gyroSensor->getValue(0);
        return _gyroValue;
    }

    int SensorManager::readColorLeft()
    {
        return -1;
    }

    int SensorManager::readColorRight()
    {
        return -1;
    }

    int SensorManager::readColorFront()
    {
        return -1;
    }
    
    void SensorManager::addEventListeners(DeviceType port, std::function<void(int)> callback, int value)
    {
        
    }

    void SensorManager::Dispatcher()
    {
    }
} // namespace finder::physical