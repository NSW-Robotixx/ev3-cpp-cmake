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
    /// @brief Destination struct
    struct Destination
    {
        /// @brief x coordinate
        double x;
        /// @brief y coordinate
        double y;
        /// @brief angle
        double angle;
        /// @brief gear
        int gear;
        /// @brief tool
        std::string tool;
        /// @brief wait
        int wait;

        Destination() = default;
        ~Destination() = default;

        /// @brief Construct a new Destination object
        /// @param x x coordinate
        /// @param y y coordinate
        /// @param angle angle
        /// @param gear gear
        /// @param tool tool
        /// @param wait wait
        Destination(double x, double y, double angle, int gear, std::string tool, int wait)
            : x(x), y(y), angle(angle), gear(gear), tool(tool), wait(wait) {}

        /// @brief Convert the destination to a string
        inline std::string toString()
        {
            return "x: " + std::to_string(x) + " y: " + std::to_string(y) + " angle: " + std::to_string(angle) + " gear: " + std::to_string(gear) + " tool: " + tool + " wait: " + std::to_string(wait);
        }
        
        /// @brief Compare two destinations
        bool operator==(const Destination &other) const
        {
            return x == other.x && y == other.y && angle == other.angle && gear == other.gear && tool == other.tool && wait == other.wait;
        }
    };

    /// @brief Read destinations from a file
    class ConfigReader
    {
        public:
            ConfigReader() = default;
            ~ConfigReader() = default;

            /// @brief Read the destinations from the file and return them. File format is YAML or TXT
            /// @return Vector of destinations, z is the angle
            static std::vector<Destination> readDestinationsFromFile();
    };
} // namespace finder::system

#endif // __EV3_YAML_READER_HPP__