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
#include <Eigen/Dense>
#include <spdlog/spdlog.h>

namespace finder::position {
    // not recommended to do this 
    using namespace finder::physical;

    /// @brief Class that represents the sensor position and handles the sensor position estimate
    class SensorPosition : public DeviceManager {
    public:
        /// @brief Constructor
        /// @param portBasePath Path to the base directory of the ports 
        SensorPosition(std::string portBasePath);

        /// @brief Destructor
        ~SensorPosition();

        /// @brief Update the position estimate of the robot
        /// @param port The port of the sensor
        /// @param value The value of the sensor
        static void update(DeviceID port, int value);

        /// @brief Initialize the sensor position estimate
        static void init();

        /// @brief Update the position estimate of the robot, notify the estimate of the direction change
        /// @param direction The direction the robot is turning
        static void movementDirectionChange(TurnDirection direction);

        /// @brief Get the current position of the robot
        /// @return The current position estimate of the robot
        static inline Eigen::Vector2d getPosition() { return _sensorPosition; }

        /// @brief Get the current angle of the robot
        /// @return The current angle estimate of the robot
        static inline float getAngle() { return _gyroSensor->getValue(0).value(); }

        /// @brief Update the general sensor position estimate
        static void updatePosition();

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


    private:
        static Eigen::Vector2d _sensorPosition;
        static float _angle;

        // stores the previous color values of the sensors as svg
        
        #if EV3_COLOR_SENSOR_USE_RGB_MODE
            static std::deque<Eigen::Vector3i> _prev_color_values_front;
            static std::deque<Eigen::Vector3i> _prev_color_values_left;
            static std::deque<Eigen::Vector3i> _prev_color_values_right;
            static std::deque<int> _prev_gyro_values;
        #else
            static std::array<unsigned short int, 3> _prev_color_values;
        #endif

        // stores the order of the last recognized lines from the sensors (last in the queue is the most recent)
        static std::deque<Eigen::Vector3d> _sensorLineOrder;

        static const Eigen::Vector2d EV3_SENSOR_COLOR_RIGHT_OFFSET_VECTOR;
        static const Eigen::Vector2d EV3_SENSOR_COLOR_LEFT_OFFSET_VECTOR;
        static const Eigen::Vector2d EV3_SENSOR_COLOR_FRONT_OFFSET_VECTOR;
        
        static TurnDirection _lastDirection;
        
        /// @brief Get Position from detected lines
        void LineDetectionParser();
    };
}