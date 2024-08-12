#ifndef __EV3_YAML_READER_HPP__
#define __EV3_YAML_READER_HPP__

#include <Logger.hpp>
#include <Vector3.hpp>
#include "../../EV3_conf.hpp"
#include <vector>
#include <fstream>

#if EV3_DESTINATIONS_FILE_FORMAT_YAML
#include <yaml-cpp/yaml.h>
#endif

namespace finder::system
{
    class ConfigReader
    {
        public:
            ConfigReader() = default;
            ~ConfigReader() = default;

            std::vector<math::Vector3> readDestinationsFromFile();
    };
} // namespace finder::system

#endif // __EV3_YAML_READER_HPP__