#include <iostream>
#include <physical/Sensor.hpp>
#include <physical/Motor.hpp>
#include <physical/portManager/DeviceManager.hpp>

bool createDirectoriesRecursive(const std::string& path) {
    if (!std::filesystem::create_directories(path)) {
        if (std::filesystem::exists(path)) {
            return true;
        }
        return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    std::cout << "Hello, World!" << std::endl;

    const bool folderExists = createDirectoriesRecursive("./test");
    if (!folderExists) {
        std::cerr << "Could not create test folder" << std::endl;
        return 1;
    }
    finder::physical::DeviceManager deviceManager{"./test"};
    return 0;
}
