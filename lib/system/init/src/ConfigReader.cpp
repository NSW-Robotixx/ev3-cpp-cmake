#include "ConfigReader.hpp"

namespace finder::system
{
    std::vector<math::Vector3> ConfigReader::readDestinationsFromFile()
    {
        std::vector<math::Vector3> destinations;

#if EV3_DESTINATIONS_FILE_FORMAT_YAML
        YAML::Node config = YAML::LoadFile(EV3_DESTINATIONS_FILE_PATH);

        if (!config["destinations"])
        {
            spdlog::error("No destinations found in file: " + std::string(EV3_DESTINATIONS_FILE_PATH));
            spdlog::error("Make sure the file is formatted correctly.");
            spdlog::error("No destinations found, Exiting...");
            exit(-1);
            return destinations;
        }

        for (const auto &destination : config["destinations"])
        {
            math::Vector3 vec(destination["x"].as<double>(), destination["y"].as<double>(), destination["z"].as<double>());
            destinations.push_back(vec);
        }
#else
        std::ifstream file;
        file.open(EV3_DESTINATIONS_FILE_PATH);

        if (!file.is_open() || !file.good())
        {
            spdlog::error("Failed to open file, or not good: " + std::string(EV3_DESTINATIONS_FILE_PATH));
            spdlog::error("Make sure the file exists and is accessible and is good.");
            spdlog::error("No destinations found, Exiting...");
            exit(-1);
            return destinations;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            try
            {
                math::Vector3 destination(line);
                destinations.push_back(destination);
            }
            catch (const std::invalid_argument &e)
            {
                spdlog::error("Invalid destination format: " + line);
                spdlog::error("Make sure the file is formatted correctly.");
                spdlog::error("No destinations found, Exiting...");
                exit(-1);
                return destinations;
            }
        }

        file.close();

#endif

        spdlog::info("Found destinations: ");
        
        for (const auto &destination : destinations)
        {
            spdlog::info(destination.toString());
        }

        return destinations;
    }


} // namespace finder::system
