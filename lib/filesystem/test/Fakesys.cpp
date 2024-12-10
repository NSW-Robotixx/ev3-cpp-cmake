#include <Fakesys.hpp>

namespace finder::physical::test
{
    // variables
    bool FakeSys::_initialized = false;
    bool FakeSys::_initializationIsPatial = false;
    std::string FakeSys::_basePath = "./fakesys";
    std::string FakeSys::_gyroSensorRelPath = "/lego-sensor/sensor0";
    std::string FakeSys::_colorSensorLeftRelPath = "/lego-sensor/sensor1";
    std::string FakeSys::_colorSensorRightRelPath = "/lego-sensor/sensor2";
    std::string FakeSys::_colorSensorFrontRelPath = "/lego-sensor/sensor3";
    std::string FakeSys::_motorLeftRelPath = "/tacho-motor/motor0";
    std::string FakeSys::_motorRightRelPath = "/tacho-motor/motor1";
    std::string FakeSys::_motorShiftRelPath = "/tacho-motor/motor2";
    std::string FakeSys::_motorToolRelPath = "/tacho-motor/motor3";

    FakeSys::FakeSys()
    {
        init();
        std::atexit([]() { disconnectAllSensors(); });
    }

    void FakeSys::init()
    {
        // check if init is required
        if (std::filesystem::exists(_basePath)) 
        {
            _initialized = true;
            _initializationIsPatial = true;
            return;
        }

        std::filesystem::create_directory(_basePath);
        
        // sensor directories
        std::filesystem::create_directories(_basePath + _gyroSensorRelPath);
        std::filesystem::create_directories(_basePath + _colorSensorLeftRelPath);
        std::filesystem::create_directories(_basePath + _colorSensorRightRelPath);
        std::filesystem::create_directories(_basePath + _colorSensorFrontRelPath);

        // motor directories
        std::filesystem::create_directories(_basePath + _motorLeftRelPath);
        std::filesystem::create_directories(_basePath + _motorRightRelPath);
        std::filesystem::create_directories(_basePath + _motorShiftRelPath);
        std::filesystem::create_directories(_basePath + _motorToolRelPath);

        // check if directories were created
        if (!std::filesystem::exists(_basePath + _gyroSensorRelPath) ||
            !std::filesystem::exists(_basePath + _colorSensorLeftRelPath) ||
            !std::filesystem::exists(_basePath + _colorSensorRightRelPath) ||
            !std::filesystem::exists(_basePath + _colorSensorFrontRelPath) ||
            !std::filesystem::exists(_basePath + _motorLeftRelPath) ||
            !std::filesystem::exists(_basePath + _motorRightRelPath) ||
            !std::filesystem::exists(_basePath + _motorShiftRelPath) ||
            !std::filesystem::exists(_basePath + _motorToolRelPath))
        {
            throw std::runtime_error("Could not create directories in: " + _basePath);
        }

        // create gyro sensor files
        initSensor(_gyroSensorRelPath, 1);

        // create color sensor left files
        initSensor(_colorSensorLeftRelPath, 2);

        // create color sensor right files
        initSensor(_colorSensorRightRelPath, 3);

        // create color sensor front files
        initSensor(_colorSensorFrontRelPath, 4);

        // create motor left files
        initMotor(_motorLeftRelPath, 'A');

        // create motor right files
        initMotor(_motorRightRelPath, 'B');

        // create motor shift files
        initMotor(_motorShiftRelPath, 'C');

        // create motor tool files
        initMotor(_motorToolRelPath, 'D');
        
        _initializationIsPatial = false;
        _initialized = true;
    }

    boost::leaf::result<std::string> FakeSys::getWorkingDir(DevicePort port)
    {
        switch (port)
        {
        case EV3_PORT_INPUT_1:
            return FakeSys::getWorkingDir() + "/lego-sensor/sensor0";
            break;
        
        case EV3_PORT_INPUT_2:
            return FakeSys::getWorkingDir() + "/lego-sensor/sensor1";
            break;

        case EV3_PORT_INPUT_3:
            return FakeSys::getWorkingDir() + "/lego-sensor/sensor2";
            break;

        case EV3_PORT_INPUT_4:
            return FakeSys::getWorkingDir() + "/lego-sensor/sensor3";
            break;

        case EV3_PORT_OUTPUT_A:
            return FakeSys::getWorkingDir() + "/tacho-motor/motor0";
            break;

        case EV3_PORT_OUTPUT_B:
            return FakeSys::getWorkingDir() + "/tacho-motor/motor1";
            break;

        case EV3_PORT_OUTPUT_C:
            return FakeSys::getWorkingDir() + "/tacho-motor/motor2";
            break;

        case EV3_PORT_OUTPUT_D:
            return FakeSys::getWorkingDir() + "/tacho-motor/motor3";
            break;

        default:
            return boost::leaf::new_error(std::out_of_range("Requested port ist out of range: " + port));
            break;
        }

        return boost::leaf::new_error(std::invalid_argument("Exited switch without result for port: " + port));
    }

    void FakeSys::disconnectGyroSensor()
    {
        std::filesystem::remove_all(_basePath + _gyroSensorRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _gyroSensorRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _gyroSensorRelPath);
        }
    }

    void FakeSys::disconnectColorSensorLeft()
    {
        std::filesystem::remove_all(_basePath + _colorSensorLeftRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _colorSensorLeftRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _colorSensorLeftRelPath);
        }
    }

    void FakeSys::disconnectColorSensorRight()
    {
        std::filesystem::remove_all(_basePath + _colorSensorRightRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _colorSensorRightRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _colorSensorRightRelPath);
        }
    }

    void FakeSys::disconnectColorSensorFront()
    {
        std::filesystem::remove_all(_basePath + _colorSensorFrontRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _colorSensorFrontRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _colorSensorFrontRelPath);
        }
    }

    void FakeSys::disconnectMotorLeft()
    {
        std::filesystem::remove_all(_basePath + _motorLeftRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _motorLeftRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _motorLeftRelPath);
        }
    }

    void FakeSys::disconnectMotorRight()
    {
        std::filesystem::remove_all(_basePath + _motorRightRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _motorRightRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _motorRightRelPath);
        }
    }

    void FakeSys::disconnectMotorShift()
    {
        std::filesystem::remove_all(_basePath + _motorShiftRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _motorShiftRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _motorShiftRelPath);
        }
    }

    void FakeSys::disconnectMotorTool()
    {
        std::filesystem::remove_all(_basePath + _motorToolRelPath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath + _motorToolRelPath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath + _motorToolRelPath);
        }
    }

    void FakeSys::disconnectAllSensors()
    {
        std::filesystem::remove_all(_basePath);

        // check if directory was deleted
        if (std::filesystem::exists(_basePath))
        {
            throw std::runtime_error("Could not delete directory: " + _basePath);
        }
    }


    void FakeSys::initSensor(std::string relPath, int index)
    {
        // write default values to files
        writeToFile(relPath + "/address", "ev3-ports:in" + std::to_string(index));
        writeToFile(relPath + "/mode", "COL-COLOR");
        writeToFile(relPath + "/modes", {{"COL-COLOR"}, {"COL-REFLECT"}, {"COL-AMBIENT"}, {"COL-COLOR"}, {"RAW"}, {"RGB"}, {"RAW"}});
        writeToFile(relPath + "/num_values", 1);
        writeToFile(relPath + "/poll_ms", 10);
        writeToFile(relPath + "/command", "");
        writeToFile(relPath + "/commands", {});


        // create files
        std::ofstream addressFile(_basePath + relPath + "/address");
        std::ofstream modeFile(_basePath + relPath + "/mode");
        std::ofstream modesFile(_basePath + relPath + "/modes");
        std::ofstream numValuesFile(_basePath + relPath + "/num_values");
        std::ofstream pollMsFile(_basePath + relPath + "/poll_ms");
        std::ofstream commandFile(_basePath + relPath + "/command");
        std::ofstream commandsFile(_basePath + relPath + "/commands");

        addressFile << "ev3-ports:in" + std::to_string(index);
        modeFile << "GYRO-ANG";
        modesFile << "GYRO-ANG GYRO-RATE GYRO-FAS";
        numValuesFile << "1";
        pollMsFile << "10";
        commandFile << "";
        commandsFile << "GYRO-ANG GYRO-RATE GYRO-FAS GYRO-G&A GYRO-CAL";

        // close files
        addressFile.close();
        modeFile.close();
        modesFile.close();
        numValuesFile.close();
        pollMsFile.close();
        commandFile.close();
        commandsFile.close();

        // create the value files last
        for (int i = 0; i < 10; i++)
        {
            std::ofstream valueFile(_basePath + relPath + "/value" + std::to_string(i));
            valueFile << "0";
            valueFile.close();
        }

    }

    void FakeSys::initMotor(std::string relPath, char index)
    {
        // write default values to files
        writeToFile(relPath + "/address", "ev3-ports:out" + std::string(1, index));
        writeToFile(relPath + "/command", "");
        writeToFile(relPath + "/commands", {"run-forever", "run-to-abs-pos", "run-to-rel-pos", "run-timed", "run-direct", "stop", "reset"});
        writeToFile(relPath + "/count_per_rot", 360);
        writeToFile(relPath + "/duty_cycle", 0);
        writeToFile(relPath + "/duty_cycle_sp", 0);
        writeToFile(relPath + "/polarity", "normal");
        writeToFile(relPath + "/position", 0);
        writeToFile(relPath + "/position_sp", 0);
        writeToFile(relPath + "/max_speed", 1050);
        writeToFile(relPath + "/speed", 0);
        writeToFile(relPath + "/speed_sp", 0);
        writeToFile(relPath + "/ramp_up_sp", 0);
        writeToFile(relPath + "/ramp_down_sp", 0);
        writeToFile(relPath + "/state", "running");
        writeToFile(relPath + "/stop_action", "hold");
        writeToFile(relPath + "/stop_actions", {"coast", "brake", "hold"});
        writeToFile(relPath + "/time_sp", 0);
    }

    void FakeSys::writeToFile(std::string relPath, std::string value, bool init, bool append)
    {
        if (init) {
            // check if file exists
            std::filesystem::path filePath(_basePath + relPath);
            if (!std::filesystem::exists(filePath))
            {
                throw std::runtime_error("File does not exist: " + filePath.string());
            }
        }

        std::ofstream file;
        if (append)
        {
            file.open(_basePath + relPath, std::ios_base::app);
        }
        else
        {
            file.open(_basePath + relPath, std::ios_base::trunc);
        }
        file << value;
        file.close();

        // check if file was written
        std::ifstream fileCheck(_basePath + relPath);
        if (fileCheck.is_open())
        {
            std::string fileContent;
            std::getline(fileCheck, fileContent);
            if (fileContent != value)
            {
                throw std::runtime_error("Could not write to file: " + _basePath + relPath);
            }
            fileCheck.close();
        }
        else
        {
            throw std::runtime_error("Could not write to file: " + relPath);
        }

        return;
    }

    void FakeSys::writeToFile(std::string relPath, int value, bool init, bool append)
    {
        writeToFile(relPath, std::to_string(value), init);
    }

    void FakeSys::writeToFile(std::string relPath, std::vector<std::string> values, bool init, bool append)
    {
        std::string value;
        for (auto v : values)
        {
            value += v + " ";
        }
        writeToFile(relPath, value, init);
    }

    void FakeSys::writeToFile(std::string relPath, std::vector<int> values, bool init, bool append)
    {
        std::string value;
        for (auto v : values)
        {
            value += std::to_string(v) + " ";
        }
        writeToFile(relPath, value, init);
    }

    void FakeSys::readFromFile(std::string relPath, std::string value)
    {
        std::ifstream file(_basePath + relPath);
        if (file.is_open())
        {
            std::string fileContent;
            std::getline(file, fileContent);
            if (fileContent != value)
            {
                throw std::runtime_error("Could not read from file: " + _basePath + relPath);
            }
            file.close();
        }
        else
        {
            throw std::runtime_error("Could not read from file: " + relPath);
        }
    }

    void FakeSys::readFromFile(std::string relPath, int value)
    {
        readFromFile(relPath, std::to_string(value));
    }

    void FakeSys::readFromFile(std::string relPath, std::vector<std::string> values)
    {
        std::string value;
        for (auto v : values)
        {
            value += v + " ";
        }
        readFromFile(relPath, value);
    }

    void FakeSys::readFromFile(std::string relPath, std::vector<int> values)
    {
        std::string value;
        for (auto v : values)
        {
            value += std::to_string(v) + " ";
        }
        readFromFile(relPath, value);
    }

    void FakeSys::simulateMotorLeftMovement(char motor, std::string endState, std::function<void()> callback)
    {
        std::string command, destination, position;
        std::ifstream fcommand, fdestination, fposition;

        fcommand.open(_motorLeftRelPath + "/command");
        fdestination.open(_motorLeftRelPath + "/position_sp");
        fposition.open(_motorLeftRelPath + "/position_sp");

        if (!fcommand.is_open()) {
            throw new std::runtime_error("[Fakesys]: Failed to open command file of motor " + motor);
        }

        if (!fdestination.is_open()) {
            throw new std::runtime_error("[Fakesys]: Failed to open destination file of motor " + motor);
        }

        if (!fposition.is_open()) {
            throw new std::runtime_error("[Fakesys]: Failed to open position file of motor " + motor);
        }

        fcommand >> command;
        fdestination >> destination;
        fposition >> position;

        if (command == "run-to-abs-pos") {
            // simulate movement
            int pos = std::stoi(position);
            while (pos < std::stoi(destination)) {
                pos++;
                writeToFile(_motorLeftRelPath + "/position", pos);
            }
            writeToFile(_motorLeftRelPath + "/state", endState);
            callback();
        }
    }

} // namespace finder::physical::test
