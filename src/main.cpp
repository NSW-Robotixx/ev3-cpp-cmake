#include "EV3_conf.hpp"

#include <spdlog/spdlog.h>
#include <gflags/gflags.h>
#include <iostream>
#include <stdio.h>
#include <chrono>

#include <EV3_System.hpp>
#include <EV3_Gearbox.hpp>
#include <DeviceManager.hpp>
#include <EV3_MotorManager.hpp>
#include <EV3_MovementCalibration.hpp>

// finder::log::Logger logger = finder::log::Logger();

constexpr auto& ascii_art_literal = R"(
  _____ _           _ _____      
 |  ___(_)_ __   __| |___ / _ __ 
 | |_  | | '_ \ / _` | |_ \| '__|
 |  _| | | | | | (_| |___) | |   
 |_|   |_|_| |_|\__,_|____/|_|   
                                     _        
  _  _      _  __   _/  /_     _     _/ _/_   
 /_//_/|/|//_'//_'/_/  /_//_/ /_'|/._//_//_'|/
/                         _/                  
)";

DEFINE_bool(v, false, "Enable info logging");
DEFINE_bool(vv, false, "Enable debug logging");
DEFINE_bool(vvv, false, "Enable trace logging");
DEFINE_bool(gearbox, false, "Calibrate gearbox");
DEFINE_bool(movement, false, "Calibrate movement");
DEFINE_bool(min_speed, false, "Set minimum speed");
DEFINE_bool(dry_run, false, "Dry run");


int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << ascii_art_literal << std::endl;

    if (FLAGS_vvv)
    {
        spdlog::set_level(spdlog::level::trace);
    }
    else if (FLAGS_vv)
    {
        spdlog::set_level(spdlog::level::debug);
    }
    else if (FLAGS_v)
    {
        spdlog::set_level(spdlog::level::info);
    }
    else
    {
        spdlog::set_level(spdlog::level::warn);
    }

    finder::system::System ev3_system = finder::system::System();
    finder::physical::GearboxManager gearbox_manager = finder::physical::GearboxManager();
    finder::position::Position position = finder::position::Position();
    // logger.info("Starting application...");

    if (FLAGS_gearbox)
    {
        gearbox_manager.calibrate();
    }

    if (FLAGS_min_speed)
    {
        finder::engines::movement::MovementCalibration movement_calibration = finder::engines::movement::MovementCalibration();
        movement_calibration.start();

        spdlog::info("Minimum speed: {}", movement_calibration.getMinSpeed());
    }
    // finder::physical::DeviceManager device_manager = finder::physical::DeviceManager("/sys/class/");
//    finder::engines::movement::MovementEngine movementEngine = finder::engines::movement::MovementEngine();
//
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
    finder::physical::MotorManager motor_manager = finder::physical::MotorManager("/sys/class");

    // finder::physical::SensorManager sensor_manager = finder::physical::SensorManager("/sys/class");

    if (!FLAGS_dry_run) 
    {        
        ev3_system.read();
        ev3_system.start();
        
        motor_manager.stop();
    }


    // while (true)
    // {
    //     std::cout << "Press enter to continue..." << std::endl;
    //     std::cin.get();
    //     break;
    // }

    // logger.success("Application finished.");
    return 0;
}
