#ifndef __FAKESYS_HPP__
#define __FAKESYS_HPP__

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>

namespace finder::physical::test
{
    /// @brief Class that represents the fakesys for testing
    class FakeSys
    {
        public:
            FakeSys();
            ~FakeSys() { };

            /// @brief init fake sys
            static void init();

            /// @brief init fake sys with base path
            /// @param basePath The base path of the fake sys
            static void init(std::string basePath) { _basePath = basePath; init(); };

            /// @brief reinit fake sys
            static void reinit() {deinit(); init();}

            /// @brief deinit fake sys and remove all files
            static void deinit() {std::filesystem::remove_all(_basePath); _initialized = false; }

            /// @brief add check for sys files
            /// @return True if all files are present
            static bool isInitialized() {return _initialized;}

            /// @brief get the base dir
            /// @return The base dir
            static std::string getWorkingDir() {return _basePath;}

            // set gyro sensor files

            /// @brief Set the gyro sensor value
            /// @param value Value to set
            /// @param index Index of the value file
            static void setGyroSensorValue(int value, int index) {writeToFile(_gyroSensorRelPath + "/value" + std::to_string(index), value);}

            /// @brief Set the gyro sensor mode
            /// @param mode Mode to set
            static void setGyroSensorMode(std::string mode) {writeToFile(_gyroSensorRelPath + "/mode", mode);} 

            /// @brief Set the gyros num values
            /// @param numValues Number of values to set
            static void setGyroSensorNumValues(int numValues) {writeToFile(_gyroSensorRelPath + "/num_values", numValues);}

            /// @brief Set the gyro sensor poll ms
            /// @param pollMs Poll ms to set
            static void setGyroSensorPollMs(int pollMs) {writeToFile(_gyroSensorRelPath + "/poll_ms", pollMs);}

            // set color sensor Left files

            /// @brief Set the color sensor left value
            /// @param value Value to set
            /// @param index Index of the value file
            static void setColorSensorLeftValue(int value, int index) {writeToFile(_colorSensorLeftRelPath + "/value" + std::to_string(index), value);}

            /// @brief Set the color sensor left mode
            /// @param mode Mode to set
            static void setColorSensorLeftMode(std::string mode) {writeToFile(_colorSensorLeftRelPath + "/mode", mode);}

            /// @brief Set the color sensor left modes file
            /// @param modes Vector of modes to set
            static void setColorSensorLeftModes(std::vector<std::string> modes) {writeToFile(_colorSensorLeftRelPath + "/modes", modes);};

            /// @brief Set the number of values for the color sensor left
            /// @param numValues Number of values to set
            static void setColorSensorLeftNumValues(int numValues) {writeToFile(_colorSensorLeftRelPath + "/num_values", numValues);}

            /// @brief Set the poll ms for the color sensor left
            /// @param pollMs Poll ms to set
            static void setColorSensorLeftPollMs(int pollMs) {writeToFile(_colorSensorLeftRelPath + "/poll_ms", pollMs);}

            // set color sensor Right files

            /// @brief Set the color sensor right value
            /// @param value Value to set
            /// @param index Index of the value file
            static void setColorSensorRightValue(int value, int index) {writeToFile(_colorSensorRightRelPath + "/value" + std::to_string(index), value);}

            /// @brief Set the color sensor right mode
            /// @param mode Mode to set
            static void setColorSensorRightMode(std::string mode) {writeToFile(_colorSensorRightRelPath + "/mode", mode);}

            /// @brief Set the color sensor right modes file
            /// @param modes Vector of modes to set
            static void setColorSensorRightModes(std::vector<std::string> modes) {writeToFile(_colorSensorRightRelPath + "/modes", modes);}

            /// @brief Set the number of values for the color sensor right
            /// @param numValues Number of values to set
            static void setColorSensorRightNumValues(int numValues) {writeToFile(_colorSensorRightRelPath + "/num_values", numValues);}

            /// @brief Set the poll ms for the color sensor right
            /// @param pollMs Poll ms to set
            static void setColorSensorRightPollMs(int pollMs) {writeToFile(_colorSensorRightRelPath + "/poll_ms", pollMs);}

            // set color sensor Front files

            /// @brief Set the color sensor front value
            /// @param value Value to set
            /// @param index Index of the value file
            static void setColorSensorFrontValue(int value, int index) {writeToFile(_colorSensorFrontRelPath + "/value" + std::to_string(index), value);}

            /// @brief Set the color sensor front mode
            /// @param mode Mode to set
            static void setColorSensorFrontMode(std::string mode) {writeToFile(_colorSensorFrontRelPath + "/mode", mode);}

            /// @brief Set the color sensor front modes file
            /// @param modes Vector of modes to set
            static void setColorSensorFrontModes(std::vector<std::string> modes) {writeToFile(_colorSensorFrontRelPath + "/modes", modes);}

            /// @brief Set the number of values for the color sensor front
            /// @param numValues Number of values to set
            static void setColorSensorFrontNumValues(int numValues) {writeToFile(_colorSensorFrontRelPath + "/num_values", numValues);}

            /// @brief Set the poll ms for the color sensor front
            /// @param pollMs Poll ms to set
            static void setColorSensorFrontPollMs(int pollMs) {writeToFile(_colorSensorFrontRelPath + "/poll_ms", pollMs);}

            // set motor left files

            /// @brief Set the motor left position
            /// @param value Value to set
            static void setMotorLeftPosition(int value) {writeToFile(_motorLeftRelPath + "/position_sp", value);}

            /// @brief Set the motor left speed
            /// @param value Value to set
            static void setMotorLeftSpeed(int value) {writeToFile(_motorLeftRelPath + "/speed_sp", value);}

            /// @brief Set the motor left count per rotation
            /// @param value Value to set
            static void setMotorLeftCountPerRotation(int value) {writeToFile(_motorLeftRelPath + "/count_per_rot", value);}

            /// @brief Set the motor left duty cycle
            /// @param value Value to set
            static void setMotorLeftDutyCycle(int value) {writeToFile(_motorLeftRelPath + "/duty_cycle_sp", value);}

            /// @brief Set the motor left stop action
            /// @param value Value to set
            static void setMotorLeftStopAction(std::string value) {writeToFile(_motorLeftRelPath + "/stop_action", value);}

            /// @brief Set the motor left polarity
            /// @param value Value to set
            static void setMotorLeftPolarity(std::string value) {writeToFile(_motorLeftRelPath + "/polarity", value);}

            /// @brief Set the motor left state
            /// @param value Value to set
            static void setMotorLeftState(std::string value) {writeToFile(_motorLeftRelPath + "/state", value);}

            // set motor right files
            
            /// @brief Set the motor right position
            /// @param value Value to set
            static void setMotorRightPosition(int value) {writeToFile(_motorRightRelPath + "/position_sp", value);}

            /// @brief Set the motor right speed
            /// @param value Value to set
            static void setMotorRightSpeed(int value) {writeToFile(_motorRightRelPath + "/speed_sp", value);};

            /// @brief Set the motor right count per rotation
            /// @param value Value to set
            static void setMotorRightCountPerRotation(int value) {writeToFile(_motorRightRelPath + "/count_per_rot", value);}

            /// @brief Set the motor right duty cycle
            /// @param value Value to set
            static void setMotorRightDutyCycle(int value) {writeToFile(_motorRightRelPath + "/duty_cycle_sp", value);}

            /// @brief Set the motor right stop action
            /// @param value Value to set
            static void setMotorRightStopAction(std::string value) {writeToFile(_motorRightRelPath + "/stop_action", value);}

            /// @brief Set the motor right polarity
            /// @param value Value to set
            static void setMotorRightPolarity(std::string value) {writeToFile(_motorRightRelPath + "/polarity", value);}

            /// @brief Set the motor right state
            /// @param value Value to set
            static void setMotorRightState(std::string value) {writeToFile(_motorRightRelPath + "/state", value);};

            // set motor shift files

            /// @brief Set the motor shift position
            /// @param value Value to set
            static void setMotorShiftPosition(int value) {writeToFile(_motorShiftRelPath + "/position_sp", value);}

            /// @brief Set the motor shift speed
            /// @param value Value to set
            static void setMotorShiftSpeed(int value) {writeToFile(_motorShiftRelPath + "/speed_sp", value);}

            /// @brief Set the motor shift count per rotation
            /// @param value Value to set
            static void setMotorShiftCountPerRotation(int value) {writeToFile(_motorShiftRelPath + "/count_per_rot", value);}

            /// @brief Set the motor shift duty cycle
            /// @param value Value to set
            static void setMotorShiftDutyCycle(int value) {writeToFile(_motorShiftRelPath + "/duty_cycle_sp", value);}

            /// @brief Set the motor shift stop action
            /// @param value Value to set
            static void setMotorShiftStopAction(std::string value) {writeToFile(_motorShiftRelPath + "/stop_action", value);}

            /// @brief Set the motor shift polarity
            /// @param value Value to set
            static void setMotorShiftPolarity(std::string value) {writeToFile(_motorShiftRelPath + "/polarity", value);}

            /// @brief Set the motor shift state
            /// @param value Value to set
            static void setMotorShiftState(std::string value) {writeToFile(_motorShiftRelPath + "/state", value);}

            // set motor tool files

            /// @brief Set the motor tool position
            /// @param value Value to set
            static void setMotorToolPosition(int value) {writeToFile(_motorToolRelPath + "/position_sp", value);}

            /// @brief Set the motor tool speed
            /// @param value Value to set
            static void setMotorToolSpeed(int value) {writeToFile(_motorToolRelPath + "/speed_sp", value);}

            /// @brief Set the motor tool count per rotation
            /// @param value Value to set
            static void setMotorToolCountPerRotation(int value) {writeToFile(_motorToolRelPath + "/count_per_rot", value);}

            /// @brief Set the motor tool duty cycle
            /// @param value Value to set
            static void setMotorToolDutyCycle(int value) {writeToFile(_motorToolRelPath + "/duty_cycle_sp", value);}

            /// @brief Set the motor tool stop action
            /// @param value Value to set
            static void setMotorToolStopAction(std::string value) {writeToFile(_motorToolRelPath + "/stop_action", value);}

            /// @brief Set the motor tool polarity
            /// @param value Value to set
            static void setMotorToolPolarity(std::string value) {writeToFile(_motorToolRelPath + "/polarity", value);};

            /// @brief Set the motor tool state
            /// @param value Value to set
            static void setMotorToolState(std::string value) {writeToFile(_motorToolRelPath + "/state", value);};

            // simulate disconnection of a sensor

            /// @brief simulate disconnection of a gyro sensor
            static void disconnectGyroSensor();

            /// @brief simulate disconnection of a color sensor left
            static void disconnectColorSensorLeft();

            /// @brief simulate disconnection of a color sensor right
            static void disconnectColorSensorRight();

            /// @brief simulate disconnection of a color sensor front
            static void disconnectColorSensorFront();

            // simulate disconnection of a motor

            /// @brief simulate disconnection of a motor left
            static void disconnectMotorLeft();

            /// @brief simulate disconnection of a motor right
            static void disconnectMotorRight();

            /// @brief simulate disconnection of a motor shift
            static void disconnectMotorShift();

            /// @brief simulate disconnection of a motor tool
            static void disconnectMotorTool();

            // simulate disconnection of all sensors

            /// @brief simulate disconnection of all sensors
            static void disconnectAllSensors();

            /// @brief Simulate motor movement for testing
            /// @param relPath Path to the motor
            /// @param position End position of the motor
            /// @param speed Speed of the motor during movement
            /// @param dutyCycle Duty cycle of the motor during movement
            /// @param stopAction Stop action of the motor
            /// @param polarity Polarity of the motor
            /// @param state State of the motor after movement
            static void emulateMotorMovement(std::string relPath, int position, int speed, int dutyCycle, std::string stopAction, std::string polarity, std::string state);

        private:
            static bool _initialized;
            static bool _initializationIsPatial;
            static std::string _basePath;
            static std::string _gyroSensorRelPath;
            static std::string _colorSensorLeftRelPath;
            static std::string _colorSensorRightRelPath;
            static std::string _colorSensorFrontRelPath;
            static std::string _motorLeftRelPath;
            static std::string _motorRightRelPath;
            static std::string _motorShiftRelPath;
            static std::string _motorToolRelPath;

            static void initSensor(std::string relPath, int index);
            static void initMotor(std::string relPath, char index);

            static void writeToFile(std::string relPath, std::string value, bool init = false);
            static void writeToFile(std::string relPath, int value, bool init = false);
            static void writeToFile(std::string relPath, std::vector<std::string> values, bool init = false);
            static void writeToFile(std::string relPath, std::vector<int> values, bool init = false);
            
            static void readFromFile(std::string relPath, std::string value);
            static void readFromFile(std::string relPath, int value);
            static void readFromFile(std::string relPath, std::vector<std::string> values);
            static void readFromFile(std::string relPath, std::vector<int> values);
    };    
} // namespace finder::physical::test


#endif // __FAKESYS_HPP__