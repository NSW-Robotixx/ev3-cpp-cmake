#include "../../EV3_conf.hpp"
#include "MotorPosition.hpp"
#include <EV3_SensorManager.hpp>
#include <EV3_MotorManager.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>
#include <queue>


namespace finder::position {
    // not recommended to do this 
    using namespace finder::physical;

    class SensorPosition {
    public:
        SensorPosition(std::string portBasePath);

        static void update(DeviceID port, int value);

        static void init();

        static void movementDirectionChange(TurnDirection direction);

    protected:
        static void updateColorLeft(int value);
        static void updateColorRight(int value);
        static void updateColorFront(int value);
        static void updateGyro(int value);

        static void updatePosition();

    private:
        static SensorManager sensorManager;

        static math::Vector2 _sensorPosition;
        static float _angle;

        // stores the order of the last recognized lines from the sensors (last in the queue is the most recent)
        static std::deque<math::Vector3> _sensorLineOrder;

        static TurnDirection _lastDirection;
    };
}