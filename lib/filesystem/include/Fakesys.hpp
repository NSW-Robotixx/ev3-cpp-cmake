#ifndef __FAKESYS_HPP__
#define __FAKESYS_HPP__

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace finder::physical::test
{
    class FakeSys
    {
        friend class FakeSysTest;

        public:
            FakeSys();
            ~FakeSys() { };

            // init fake sys
            static void init();
            static void init(std::string basePath) { _basePath = basePath; init(); };
            static void reinit() {deinit(); init();}
            static void deinit() {std::filesystem::remove_all(_basePath); _initialized = false; }

            // add check for sys files
            static bool isInitialized() {return _initialized;}

            // get the base dir
            static std::string getWorkingDir() {return _basePath;}

            // set gyro sensor files
            static void setGyroSensorValue(int value, int index) {writeToFile(_gyroSensorRelPath + "/value" + std::to_string(index), value);}
            static void setGyroSensorMode(std::string mode) {writeToFile(_gyroSensorRelPath + "/mode", mode);} 
            static void setGyroSensorNumValues(int numValues) {writeToFile(_gyroSensorRelPath + "/num_values", numValues);}
            static void setGyroSensorPollMs(int pollMs) {writeToFile(_gyroSensorRelPath + "/poll_ms", pollMs);}

            // set color sensor Left files
            static void setColorSensorLeftValue(int value, int index) {writeToFile(_colorSensorLeftRelPath + "/value" + std::to_string(index), value);}
            static void setColorSensorLeftMode(std::string mode) {writeToFile(_colorSensorLeftRelPath + "/mode", mode);}
            static void setColorSensorLeftModes(std::vector<std::string> modes) {writeToFile(_colorSensorLeftRelPath + "/modes", modes);};
            static void setColorSensorLeftNumValues(int numValues) {writeToFile(_colorSensorLeftRelPath + "/num_values", numValues);}
            static void setColorSensorLeftPollMs(int pollMs) {writeToFile(_colorSensorLeftRelPath + "/poll_ms", pollMs);}

            // set color sensor Right files
            static void setColorSensorRightValue(int value, int index) {writeToFile(_colorSensorRightRelPath + "/value" + std::to_string(index), value);}
            static void setColorSensorRightMode(std::string mode) {writeToFile(_colorSensorRightRelPath + "/mode", mode);}
            static void setColorSensorRightModes(std::vector<std::string> modes) {writeToFile(_colorSensorRightRelPath + "/modes", modes);}
            static void setColorSensorRightNumValues(int numValues) {writeToFile(_colorSensorRightRelPath + "/num_values", numValues);}
            static void setColorSensorRightPollMs(int pollMs) {writeToFile(_colorSensorRightRelPath + "/poll_ms", pollMs);}

            // set color sensor Front files
            static void setColorSensorFrontValue(int value, int index) {writeToFile(_colorSensorFrontRelPath + "/value" + std::to_string(index), value);}
            static void setColorSensorFrontMode(std::string mode) {writeToFile(_colorSensorFrontRelPath + "/mode", mode);}
            static void setColorSensorFrontModes(std::vector<std::string> modes) {writeToFile(_colorSensorFrontRelPath + "/modes", modes);}
            static void setColorSensorFrontNumValues(int numValues) {writeToFile(_colorSensorFrontRelPath + "/num_values", numValues);}
            static void setColorSensorFrontPollMs(int pollMs) {writeToFile(_colorSensorFrontRelPath + "/poll_ms", pollMs);}

            // set motor left files
            static void setMotorLeftPosition(int value) {writeToFile(_motorLeftRelPath + "/position_sp", value);}
            static void setMotorLeftSpeed(int value) {writeToFile(_motorLeftRelPath + "/speed_sp", value);}
            static void setMotorLeftCountPerRotation(int value) {writeToFile(_motorLeftRelPath + "/count_per_rot", value);}
            static void setMotorLeftDutyCycle(int value) {writeToFile(_motorLeftRelPath + "/duty_cycle_sp", value);}
            static void setMotorLeftStopAction(std::string value) {writeToFile(_motorLeftRelPath + "/stop_action", value);}
            static void setMotorLeftPolarity(std::string value) {writeToFile(_motorLeftRelPath + "/polarity", value);}
            static void setMotorLeftState(std::string value) {writeToFile(_motorLeftRelPath + "/state", value);}

            // set motor right files
            static void setMotorRightPosition(int value) {writeToFile(_motorRightRelPath + "/position_sp", value);}
            static void setMotorRightSpeed(int value) {writeToFile(_motorRightRelPath + "/speed_sp", value);};
            static void setMotorRightCountPerRotation(int value) {writeToFile(_motorRightRelPath + "/count_per_rot", value);}
            static void setMotorRightDutyCycle(int value) {writeToFile(_motorRightRelPath + "/duty_cycle_sp", value);}
            static void setMotorRightStopAction(std::string value) {writeToFile(_motorRightRelPath + "/stop_action", value);}
            static void setMotorRightPolarity(std::string value) {writeToFile(_motorRightRelPath + "/polarity", value);}
            static void setMotorRightState(std::string value) {writeToFile(_motorRightRelPath + "/state", value);};

            // set motor shift files
            static void setMotorShiftPosition(int value) {writeToFile(_motorShiftRelPath + "/position_sp", value);}
            static void setMotorShiftSpeed(int value) {writeToFile(_motorShiftRelPath + "/speed_sp", value);}
            static void setMotorShiftCountPerRotation(int value) {writeToFile(_motorShiftRelPath + "/count_per_rot", value);}
            static void setMotorShiftDutyCycle(int value) {writeToFile(_motorShiftRelPath + "/duty_cycle_sp", value);}
            static void setMotorShiftStopAction(std::string value) {writeToFile(_motorShiftRelPath + "/stop_action", value);}
            static void setMotorShiftPolarity(std::string value) {writeToFile(_motorShiftRelPath + "/polarity", value);}
            static void setMotorShiftState(std::string value) {writeToFile(_motorShiftRelPath + "/state", value);}

            // set motor tool files
            static void setMotorToolPosition(int value) {writeToFile(_motorToolRelPath + "/position_sp", value);}
            static void setMotorToolSpeed(int value) {writeToFile(_motorToolRelPath + "/speed_sp", value);}
            static void setMotorToolCountPerRotation(int value) {writeToFile(_motorToolRelPath + "/count_per_rot", value);}
            static void setMotorToolDutyCycle(int value) {writeToFile(_motorToolRelPath + "/duty_cycle_sp", value);}
            static void setMotorToolStopAction(std::string value) {writeToFile(_motorToolRelPath + "/stop_action", value);}
            static void setMotorToolPolarity(std::string value) {writeToFile(_motorToolRelPath + "/polarity", value);};
            static void setMotorToolState(std::string value) {writeToFile(_motorToolRelPath + "/state", value);};

            // simulate disconnection of a sensor
            static void disconnectGyroSensor();
            static void disconnectColorSensorLeft();
            static void disconnectColorSensorRight();
            static void disconnectColorSensorFront();

            // simulate disconnection of a motor
            static void disconnectMotorLeft();
            static void disconnectMotorRight();
            static void disconnectMotorShift();
            static void disconnectMotorTool();

            // simulate disconnection of all sensors
            static void disconnectAllSensors();

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
    };    
} // namespace finder::physical::test


#endif // __FAKESYS_HPP__