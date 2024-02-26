#include <physical/portManager/port/Port.hpp>

namespace finder
{
    namespace physical
    {
        class MotorPort : Port {
            public:
                MotorPort();

            private:
                std::shared_ptr<std::ifstream> _file_command_path;
                std::shared_ptr<std::ifstream> _file_speed_path;
                std::shared_ptr<std::ifstream> _file_position_sp_path;
                std::shared_ptr<std::ifstream> _file_duty_cycle_path;
                std::shared_ptr<std::ifstream> _file_state_path;
                std::shared_ptr<std::ifstream> _file_polarity_path;
                std::shared_ptr<std::ifstream> _file_stop_action_path;
                std::shared_ptr<std::ifstream> _file_count_per_rotation_path;
        };
    } // namespace physical
} // namespace finder
