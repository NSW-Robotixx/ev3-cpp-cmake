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

    /// @brief Class that represents the sensor position and handles the sensor position estimate
    class SensorPosition {
    public:
        /// @brief Constructor
        /// @param portBasePath Path to the base directory of the ports 
        SensorPosition(std::string portBasePath);

        /// @brief Update the position estimate of the robot
        /// @param port The port of the sensor
        /// @param value The value of the sensor
        static void update(DeviceID port, int value);

        /// @brief Initialize the sensor position estimate
        static void init();

        /// @brief Update the position estimate of the robot, notify the estimate of the direction change
        /// @param direction The direction the robot is turning
        static void movementDirectionChange(TurnDirection direction);

    protected:
        /// @brief Update the color sensor left position estimate
        /// @param value The value of the color sensor
        static void updateColorLeft(int value);

        /// @brief Update the color sensor position estimate
        /// @param value The value of the color sensor
        static void updateColorRight(int value);

        /// @brief Update the color sensor position estimate
        /// @param value The value of the color sensor
        static void updateColorFront(int value);

        /// @brief Update the gyro sensor position estimate
        /// @param value The value of the gyro sensor
        static void updateGyro(int value);

        /// @brief Update the general sensor position estimate
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