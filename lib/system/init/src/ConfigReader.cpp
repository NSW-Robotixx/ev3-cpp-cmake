#include "ConfigReader.hpp"

namespace finder::system
{
    std::vector<Destination> ConfigReader::readDestinationsFromFile()
    {
        std::vector<Destination> destinations;

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
            Destination vec;
            vec.x = destination["x"].as<double>();
            vec.y = destination["y"].as<double>();
            try
            {
                vec.angle = destination["angle"].as<double>();
            }
            catch(const std::exception& e)
            {
                spdlog::debug("No angle found in destination, setting to -1");
                vec.angle = -1;
            }
            
            try
            {
                vec.gear = destination["gear"].as<int>();
            }
            catch(const std::exception& e)
            {
                spdlog::debug("No gear found in destination, setting to 0");
                vec.gear = 0;
            }

            try
            {
                vec.tool = destination["tool"].as<std::string>();
            }
            catch(const std::exception& e)
            {
                spdlog::debug("No tool found in destination, setting to empty string");
                vec.tool = "";
            }            

            try
            {
                vec.wait = destination["wait"].as<int>();
            }
            catch(const std::exception& e)
            {
                spdlog::debug("No wait found in destination, setting to 0");
                vec.wait = 0;
            }

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
            spdlog::info("x: " + std::to_string(destination.x) + " y: " + std::to_string(destination.y) + " angle: " + std::to_string(destination.angle) + " gear: " + std::to_string(destination.gear) + " tool: " + destination.tool + " wait: " + std::to_string(destination.wait));
        }

        return destinations;
    }


} // namespace finder::system
