#include "YamlReader.hpp"

namespace finder::system
{
    std::vector<math::Vector3> readDestinationsFromFile()
    {
        std::vector<math::Vector3> destinations;

        YAML::Node config = YAML::LoadFile(EV3_DESTINATIONS_FILE_PATH);

        for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
        {
            math::Vector3 destination;
            destination.x = it->first.as<float>();
            destination.y = it->second.as<float>();

            destinations.push_back(destination);
        }

        return destinations;
    }

} // namespace finder::system
