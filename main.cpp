#include <console/Logger.hpp>
#include <physical/portManager/PortManager.hpp>
#include <iostream>

finder::console::Logger logger = finder::console::Logger();

int main(int argc, char const *argv[])
{
    using namespace finder::physical;

    PortManager DM = PortManager{};

    DM.readPorts();

    return 0;
}
