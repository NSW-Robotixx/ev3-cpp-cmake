#include <gtest/gtest.h>

#include <EV3_System.hpp>

TEST(EV3_System, DefaultConstructor)
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

    finder::system::System system;
    EXPECT_NO_THROW(system.start());

}