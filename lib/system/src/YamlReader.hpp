#ifndef __EV3_YAML_READER_HPP__
#define __EV3_YAML_READER_HPP__

#include <Logger.hpp>
#include <Vector3.hpp>
#include "../../EV3_conf.hpp"
#include <vector>
#include <yaml-cpp/yaml.h>

namespace finder::system
{
    class YamlReader
    {
        public:
            YamlReader() = default;
            ~YamlReader() = default;

            std::vector<math::Vector3> readDestinationsFromFile();
    };
} // namespace finder::system

#endif // __EV3_YAML_READER_HPP__