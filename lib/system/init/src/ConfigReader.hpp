#ifndef __EV3_YAML_READER_HPP__
#define __EV3_YAML_READER_HPP__

#include <Vector3.hpp>
#include "../../EV3_conf.hpp"
#include <vector>
#include <fstream>

#include <spdlog/spdlog.h>

#if EV3_DESTINATIONS_FILE_FORMAT_YAML
#include <yaml-cpp/yaml.h>
#endif

namespace finder::system
{
    /// @brief Read destinations from a file
    class ConfigReader
    {
        public:
            ConfigReader() = default;
            ~ConfigReader() = default;

            /// @brief Read the destinations from the file and return them. File format is YAML or TXT
            /// @return Vector of destinations, z is the angle
            static std::vector<math::Vector3> readDestinationsFromFile();
    };
} // namespace finder::system

#endif // __EV3_YAML_READER_HPP__