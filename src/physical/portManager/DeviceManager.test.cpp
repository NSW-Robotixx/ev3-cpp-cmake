#include <gtest/gtest.h>

#include <physical/portManager/DeviceManager.hpp>

TEST(DeviceManagerTest, BasicAssertions) {
    using namespace finder::physical;

    DeviceManager deviceManager = DeviceManager();

    EXPECT_EQ(deviceManager.getPorts().input_1.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().input_2.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().input_3.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().input_4.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().output_A.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().output_B.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().output_C.getBasePath(), "");
    EXPECT_EQ(deviceManager.getPorts().output_D.getBasePath(), "");
}

bool createDirectoriesRecursive(const std::string& path) {
    if (!std::filesystem::create_directories(path)) {
        if (std::filesystem::exists(path)) {
            return true;
        }
        return false;
    }
    return true;
}

void writeToFile(const std::string& path, const std::string& content) {
    std::ofstream file;
    file.open(path);
    file << content;
    file.close();
}

TEST(DeviceManager, constructor) {

//     // create a random folder name
//     // da war ich zu faul um das zu ändern
//     std::string folderName = random_string(12);

    //test the constructor
    finder::physical::DeviceManager deviceManager = finder::physical::DeviceManager{"./test"};
    ASSERT_EQ(deviceManager.getSensorDir(), "./test/lego-sensor");
    ASSERT_EQ(deviceManager.getMotorDir(), "./test/tacho-motor");

    const bool folderExists = createDirectoriesRecursive("./test");
    ASSERT_EQ(folderExists, true);

    ASSERT_EQ(deviceManager.readPorts(), 0);

}

TEST(DeviceManager, functionreadPortsSingleSensor) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/lego-sensor/sensor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/lego-sensor/sensor1/address", "ev3-ports:in1");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 1);

    ASSERT_EQ(deviceManager.getPorts().input_1.getBasePath(), "./test/lego-sensor/sensor1");
}

TEST(DeviceManager, functionreadPortsMultipleSensors) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/lego-sensor/sensor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/lego-sensor/sensor1/address", "ev3-ports:in1");

    const bool folderExists2 = createDirectoriesRecursive("./test/lego-sensor/sensor2");
    ASSERT_EQ(folderExists2, true);

    writeToFile("./test/lego-sensor/sensor2/address", "ev3-ports:in2");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 2);

    ASSERT_EQ(deviceManager.getPorts().input_1.getBasePath(), "./test/lego-sensor/sensor1");
    ASSERT_EQ(deviceManager.getPorts().input_2.getBasePath(), "./test/lego-sensor/sensor2");
}

TEST(DeviceManager, functionreadPortsAllSensors) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/lego-sensor/sensor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/lego-sensor/sensor1/address", "ev3-ports:in1");

    const bool folderExists2 = createDirectoriesRecursive("./test/lego-sensor/sensor2");
    ASSERT_EQ(folderExists2, true);

    writeToFile("./test/lego-sensor/sensor2/address", "ev3-ports:in2");

    const bool folderExists3 = createDirectoriesRecursive("./test/lego-sensor/sensor3");
    ASSERT_EQ(folderExists3, true);

    writeToFile("./test/lego-sensor/sensor3/address", "ev3-ports:in3");

    const bool folderExists4 = createDirectoriesRecursive("./test/lego-sensor/sensor4");
    ASSERT_EQ(folderExists4, true);

    writeToFile("./test/lego-sensor/sensor4/address", "ev3-ports:in4");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();

    ASSERT_EQ(DeviceManager::readPorts(), 4);

    ASSERT_EQ(deviceManager.getPorts().input_1.getBasePath(), "./test/lego-sensor/sensor1");
    ASSERT_EQ(deviceManager.getPorts().input_2.getBasePath(), "./test/lego-sensor/sensor2");
    ASSERT_EQ(deviceManager.getPorts().input_3.getBasePath(), "./test/lego-sensor/sensor3");
    ASSERT_EQ(deviceManager.getPorts().input_4.getBasePath(), "./test/lego-sensor/sensor4");
}

TEST(DeviceManager, functionreadPortsSingleMotor) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/tacho-motor/motor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/tacho-motor/motor1/address", "ev3-ports:outA");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 5);

    ASSERT_EQ(deviceManager.getPorts().output_A.getBasePath(), "./test/tacho-motor/motor1");
}

TEST(DeviceManager, functionreadPortsMultipleMotors) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/tacho-motor/motor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/tacho-motor/motor1/address", "ev3-ports:outA");

    const bool folderExists2 = createDirectoriesRecursive("./test/tacho-motor/motor2");
    ASSERT_EQ(folderExists2, true);

    writeToFile("./test/tacho-motor/motor2/address", "ev3-ports:outB");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 6);

    ASSERT_EQ(deviceManager.getPorts().output_A.getBasePath(), "./test/tacho-motor/motor1");
    ASSERT_EQ(deviceManager.getPorts().output_B.getBasePath(), "./test/tacho-motor/motor2");
}

TEST(DeviceManager, functionreadPortsAllMotors) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/tacho-motor/motor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/tacho-motor/motor1/address", "ev3-ports:outA");

    const bool folderExists2 = createDirectoriesRecursive("./test/tacho-motor/motor2");
    ASSERT_EQ(folderExists2, true);

    writeToFile("./test/tacho-motor/motor2/address", "ev3-ports:outB");

    const bool folderExists3 = createDirectoriesRecursive("./test/tacho-motor/motor3");
    ASSERT_EQ(folderExists3, true);

    writeToFile("./test/tacho-motor/motor3/address", "ev3-ports:outC");

    const bool folderExists4 = createDirectoriesRecursive("./test/tacho-motor/motor4");
    ASSERT_EQ(folderExists4, true);

    writeToFile("./test/tacho-motor/motor4/address", "ev3-ports:outD");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 8);

    ASSERT_EQ(deviceManager.getPorts().output_A.getBasePath(), "./test/tacho-motor/motor1");
    ASSERT_EQ(deviceManager.getPorts().output_B.getBasePath(), "./test/tacho-motor/motor2");
    ASSERT_EQ(deviceManager.getPorts().output_C.getBasePath(), "./test/tacho-motor/motor3");
    ASSERT_EQ(deviceManager.getPorts().output_D.getBasePath(), "./test/tacho-motor/motor4");
}

TEST(DeviceManager, functionreadPortsAllDevices) {
    using namespace finder::physical;

    const bool folderExists = createDirectoriesRecursive("./test/lego-sensor/sensor1");
    ASSERT_EQ(folderExists, true);

    writeToFile("./test/lego-sensor/sensor1/address", "ev3-ports:in1");

    const bool folderExists2 = createDirectoriesRecursive("./test/lego-sensor/sensor2");
    ASSERT_EQ(folderExists2, true);

    writeToFile("./test/lego-sensor/sensor2/address", "ev3-ports:in2");

    const bool folderExists3 = createDirectoriesRecursive("./test/lego-sensor/sensor3");
    ASSERT_EQ(folderExists3, true);

    writeToFile("./test/lego-sensor/sensor3/address", "ev3-ports:in3");

    const bool folderExists4 = createDirectoriesRecursive("./test/lego-sensor/sensor4");
    ASSERT_EQ(folderExists4, true);

    writeToFile("./test/lego-sensor/sensor4/address", "ev3-ports:in4");

    const bool folderExists5 = createDirectoriesRecursive("./test/tacho-motor/motor1");
    ASSERT_EQ(folderExists5, true);

    writeToFile("./test/tacho-motor/motor1/address", "ev3-ports:outA");

    const bool folderExists6 = createDirectoriesRecursive("./test/tacho-motor/motor2");
    ASSERT_EQ(folderExists6, true);

    writeToFile("./test/tacho-motor/motor2/address", "ev3-ports:outB");
    
    const bool folderExists7 = createDirectoriesRecursive("./test/tacho-motor/motor3");
    ASSERT_EQ(folderExists7, true);

    writeToFile("./test/tacho-motor/motor3/address", "ev3-ports:outC");

    const bool folderExists8 = createDirectoriesRecursive("./test/tacho-motor/motor4");
    ASSERT_EQ(folderExists8, true);

    writeToFile("./test/tacho-motor/motor4/address", "ev3-ports:outD");

    DeviceManager deviceManager{"./test"};

    int discoveredDevices = DeviceManager::readPorts();
    ASSERT_EQ(DeviceManager::readPorts(), 8);

    ASSERT_EQ(deviceManager.getPorts().input_1.getBasePath(), "./test/lego-sensor/sensor1");
    ASSERT_EQ(deviceManager.getPorts().input_2.getBasePath(), "./test/lego-sensor/sensor2");
    ASSERT_EQ(deviceManager.getPorts().input_3.getBasePath(), "./test/lego-sensor/sensor3");
    ASSERT_EQ(deviceManager.getPorts().input_4.getBasePath(), "./test/lego-sensor/sensor4");
    ASSERT_EQ(deviceManager.getPorts().output_A.getBasePath(), "./test/tacho-motor/motor1");
    ASSERT_EQ(deviceManager.getPorts().output_B.getBasePath(), "./test/tacho-motor/motor2");
    ASSERT_EQ(deviceManager.getPorts().output_C.getBasePath(), "./test/tacho-motor/motor3");
    ASSERT_EQ(deviceManager.getPorts().output_D.getBasePath(), "./test/tacho-motor/motor4");
}

// cleanup

TEST(DeviceManager, cleanup) {
    std::filesystem::remove_all("./test");
    ASSERT_FALSE(std::filesystem::exists("./test"));
}