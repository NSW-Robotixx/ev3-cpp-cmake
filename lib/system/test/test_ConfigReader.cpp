#include <gtest/gtest.h>
#include <fstream>

#include "../src/ConfigReader.hpp"

TEST(ConfigReader, DefaultConstructor)
{
    // Set a predefined content of the file
    std::ofstream file(EV3_DESTINATIONS_FILE_PATH);
#if EV3_DESTINATIONS_FILE_FORMAT_YAML
    file << "destinations: \n";
    file << "  - x: 1\n";
    file << "    y: 2\n";
    file << "    z: 3\n";
    file << "  - x: 4\n";
    file << "    y: 5\n";
    file << "    z: 6\n";
    file << "  - x: 7\n";
    file << "    y: 8\n";
    file << "    z: 9\n";
    file.close();
#else
    file << "(1 2 3)\n";
    file << "(4 5 6)\n";
    file << "(7 8 9)\n";
    file.close();
#endif

    finder::system::ConfigReader configReader;
    std::vector<finder::math::Vector3> destinations = configReader.readDestinationsFromFile();

    EXPECT_EQ(destinations.size(), 3);
    EXPECT_EQ(destinations[0], (finder::math::Vector3{1, 2, 3}));
    EXPECT_EQ(destinations[1], (finder::math::Vector3{4, 5, 6}));
    EXPECT_EQ(destinations[2], (finder::math::Vector3{7, 8, 9}));
}