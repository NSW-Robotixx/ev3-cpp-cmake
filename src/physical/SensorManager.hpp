#ifndef __SENSOR_MANAGER_HPP__
#define __SENSOR_MANAGER_HPP__

#include <physical/DeviceManager.hpp>
#include <memory>

namespace finder::physical
{
    class SensorManager : public DeviceManager
    {
        public:
            SensorManager();
            ~SensorManager();

            void readAllSensors();
            int readGyro();
            int readColorLeft();
            int readColorRight();
            int readColorFront();

            static void Dispatcher();

        private:
            static int _gyroValue;
            static int _colorLeftValue;
            static int _colorRightValue;
            static int _colorFrontValue;

    };
} // namespace finder::physical

#endif // __SENSOR_MANAGER_HPP__