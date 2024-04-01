#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

TEST(initFiles, createFilesMotor0)
{
    std::filesystem::create_directories("./test/motor0");

    std::ofstream fs_address("./test/motor0/address");
    std::ofstream fs_command("./test/motor0/command");
    std::ofstream fs_commands("./test/motor0/commands");
    std::ofstream fs_speed("./test/motor0/speed_sp");   
    std::ofstream fs_position_sp("./test/motor0/position_sp");
    std::ofstream fs_duty_cycle("./test/motor0/duty_cycle_sp");
    std::ofstream fs_state("./test/motor0/state");
    std::ofstream fs_polarity("./test/motor0/polarity");
    std::ofstream fs_stop_action("./test/motor0/stop_action");
    std::ofstream fs_count_per_rotation("./test/motor0/count_per_rot");

    ASSERT_TRUE(fs_address.is_open());
    ASSERT_TRUE(fs_command.is_open());
    ASSERT_TRUE(fs_commands.is_open());
    ASSERT_TRUE(fs_speed.is_open());
    ASSERT_TRUE(fs_position_sp.is_open());
    ASSERT_TRUE(fs_duty_cycle.is_open());
    ASSERT_TRUE(fs_state.is_open());
    ASSERT_TRUE(fs_polarity.is_open());
    ASSERT_TRUE(fs_stop_action.is_open());
    ASSERT_TRUE(fs_count_per_rotation.is_open());


    

    fs_address << "ev3-ports:outA";
    fs_command << "run-forever";
    fs_commands << "run-forever run-to-abs-pos run-to-rel-pos run-timed run-direct stop reset";
    fs_speed << "";
    fs_position_sp << "100";
    fs_duty_cycle << "100";
    fs_state << "0";
    fs_polarity << "0";
    fs_stop_action << "0";
    fs_count_per_rotation << "360";

    fs_address.close();
    fs_command.close();
    fs_commands.close();
    fs_speed.close();
    fs_position_sp.close();
    fs_duty_cycle.close();
    fs_state.close();
    fs_polarity.close();
    fs_stop_action.close();
    fs_count_per_rotation.close();
}

TEST(initFiles, createFilesSensor0)
{
    std::filesystem::create_directories("./test/sensor0");

    std::ofstream fs_address("./test/sensor0/address");
    std::ofstream fs_mode("./test/sensor0/mode");
    std::ofstream fs_modes("./test/sensor0/modes");
    std::ofstream fs_num_values("./test/sensor0/num_values");
    std::ofstream fs_poll_ms("./test/sensor0/poll_ms");
    std::ofstream fs_value0("./test/sensor0/value0");

    ASSERT_TRUE(fs_address.is_open());
    ASSERT_TRUE(fs_mode.is_open());
    ASSERT_TRUE(fs_modes.is_open());
    ASSERT_TRUE(fs_num_values.is_open());
    ASSERT_TRUE(fs_poll_ms.is_open());
    ASSERT_TRUE(fs_value0.is_open());

    fs_address << "ev3-ports:in1";
    fs_mode << "EV3-ULTRASONIC";
    fs_modes << "EV3-ULTRASONIC EV3-GYRO EV3-COLOR EV3-IR-PROX EV3-TOUCH";
    fs_num_values << "1";
    fs_poll_ms << "100";
    fs_value0 << "42";

    fs_address.close();
    fs_mode.close();
    fs_modes.close();
    fs_num_values.close();
    fs_poll_ms.close();
    fs_value0.close();
}