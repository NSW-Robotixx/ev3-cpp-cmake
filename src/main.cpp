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

// finder::log::Logger logger = finder::log::Logger();
finder::system::System ev3_system = finder::system::System();
finder::physical::GearboxManager gearbox_manager = finder::physical::GearboxManager();

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

DEFINE_bool(v, false, "Enable debug logging");
DEFINE_bool(vv, false, "Enable trace logging");
DEFINE_bool(gearbox, false, "Calibrate gearbox");


int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << ascii_art_literal << std::endl;

    if (FLAGS_vv)
    {
        spdlog::set_level(spdlog::level::trace);
    }
    else if (FLAGS_v)
    {
        spdlog::set_level(spdlog::level::debug);
    }
    else
    {
        spdlog::set_level(spdlog::level::info);
    }

    // logger.info("Starting application...");

    spdlog::debug("Debug message");

    // ev3_system.start();

    // finder::physical::DeviceManager device_manager = finder::physical::DeviceManager("/sys/class/");
//    finder::engines::movement::MovementEngine movementEngine = finder::engines::movement::MovementEngine();
//
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
    finder::physical::MotorManager motor_manager = finder::physical::MotorManager("/sys/class");

    // gearbox_manager.calibrate();

    // finder::physical::SensorManager sensor_manager = finder::physical::SensorManager("/sys/class");

    ev3_system.read();
    ev3_system.start();

    motor_manager.stop();


    // while (true)
    // {
    //     std::cout << "Press enter to continue..." << std::endl;
    //     std::cin.get();
    //     break;
    // }

    // logger.success("Application finished.");
    return 0;
}
