#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

TEST(initFiles, createFilesMotor0)
{
    std::filesystem::create_directories("./test/tacho-motor/motor0");
    std::filesystem::create_directories("./test/tacho-motor/motor1");

    std::ofstream fs_address_0("./test/tacho-motor/motor0/address");
    std::ofstream fs_command_0("./test/tacho-motor/motor0/command");
    std::ofstream fs_commands_0("./test/tacho-motor/motor0/commands");
    std::ofstream fs_speed_0("./test/tacho-motor/motor0/speed_sp");   
    std::ofstream fs_position_sp_0("./test/tacho-motor/motor0/position_sp");
    std::ofstream fs_duty_cycle_0("./test/tacho-motor/motor0/duty_cycle_sp");
    std::ofstream fs_state_0("./test/tacho-motor/motor0/state");
    std::ofstream fs_polarity_0("./test/tacho-motor/motor0/polarity");
    std::ofstream fs_stop_action_0("./test/tacho-motor/motor0/stop_action");
    std::ofstream fs_count_per_rotation_0("./test/tacho-motor/motor0/count_per_rot");

    std::ofstream fs_address_1("./test/tacho-motor/motor1/address");
    std::ofstream fs_command_1("./test/tacho-motor/motor1/command");
    std::ofstream fs_commands_1("./test/tacho-motor/motor1/commands");
    std::ofstream fs_speed_1("./test/tacho-motor/motor1/speed_sp");   
    std::ofstream fs_position_sp_1("./test/tacho-motor/motor1/position_sp");
    std::ofstream fs_duty_cycle_1("./test/tacho-motor/motor1/duty_cycle_sp");
    std::ofstream fs_state_1("./test/tacho-motor/motor1/state");
    std::ofstream fs_polarity_1("./test/tacho-motor/motor1/polarity");
    std::ofstream fs_stop_action_1("./test/tacho-motor/motor1/stop_action");
    std::ofstream fs_count_per_rotation_1("./test/tacho-motor/motor1/count_per_rot");


    ASSERT_TRUE(fs_address_0.is_open());
    ASSERT_TRUE(fs_command_0.is_open());
    ASSERT_TRUE(fs_commands_0.is_open());
    ASSERT_TRUE(fs_speed_0.is_open());
    ASSERT_TRUE(fs_position_sp_0.is_open());
    ASSERT_TRUE(fs_duty_cycle_0.is_open());
    ASSERT_TRUE(fs_state_0.is_open());
    ASSERT_TRUE(fs_polarity_0.is_open());
    ASSERT_TRUE(fs_stop_action_0.is_open());
    ASSERT_TRUE(fs_count_per_rotation_0.is_open());

    ASSERT_TRUE(fs_address_1.is_open());
    ASSERT_TRUE(fs_command_1.is_open());
    ASSERT_TRUE(fs_commands_1.is_open());
    ASSERT_TRUE(fs_speed_1.is_open());
    ASSERT_TRUE(fs_position_sp_1.is_open());
    ASSERT_TRUE(fs_duty_cycle_1.is_open());
    ASSERT_TRUE(fs_state_1.is_open());
    ASSERT_TRUE(fs_polarity_1.is_open());
    ASSERT_TRUE(fs_stop_action_1.is_open());
    ASSERT_TRUE(fs_count_per_rotation_1.is_open());
    

    fs_address_0 << "ev3-ports:outA";
    fs_command_0 << "run-forever";
    fs_commands_0 << "run-forever run-to-abs-pos run-to-rel-pos run-timed run-direct stop reset";
    fs_speed_0 << "0";
    fs_position_sp_0 << "100";
    fs_duty_cycle_0 << "100";
    fs_state_0 << "0";
    fs_polarity_0 << "0";
    fs_stop_action_0 << "0";
    fs_count_per_rotation_0 << "360";

    fs_address_1 << "ev3-ports:outB";
    fs_command_1 << "run-forever";
    fs_commands_1 << "run-forever run-to-abs-pos run-to-rel-pos run-timed run-direct stop reset";
    fs_speed_1 << "0";
    fs_position_sp_1 << "100";
    fs_duty_cycle_1 << "100";
    fs_state_1 << "0";
    fs_polarity_1 << "0";
    fs_stop_action_1 << "0";
    fs_count_per_rotation_1 << "360";


    fs_address_0.close();
    fs_command_0.close();
    fs_commands_0.close();
    fs_speed_0.close();
    fs_position_sp_0.close();
    fs_duty_cycle_0.close();
    fs_state_0.close();
    fs_polarity_0.close();
    fs_stop_action_0.close();
    fs_count_per_rotation_0.close();

    fs_address_1.close();
    fs_command_1.close();
    fs_commands_1.close();
    fs_speed_1.close();
    fs_position_sp_1.close();
    fs_duty_cycle_1.close();
    fs_state_1.close();
    fs_polarity_1.close();
    fs_stop_action_1.close();
    fs_count_per_rotation_1.close();

}

TEST(initFiles, createFilesSensor0)
{
    std::filesystem::create_directories("./test/lego-sensor/sensor0");
    std::filesystem::create_directories("./test/lego-sensor/sensor1");

    std::ofstream fs_address_0("./test/lego-sensor/sensor0/address");
    std::ofstream fs_mode_0("./test/lego-sensor/sensor0/mode");
    std::ofstream fs_modes_0("./test/lego-sensor/sensor0/modes");
    std::ofstream fs_num_values_0("./test/lego-sensor/sensor0/num_values");
    std::ofstream fs_poll_ms_0("./test/lego-sensor/sensor0/poll_ms");
    std::ofstream fs_value0_0("./test/lego-sensor/sensor0/value0");
    std::ofstream fs_command_0("./test/lego-sensor/sensor0/command");
    std::ofstream fs_commands_0("./test/lego-sensor/sensor0/commands");

    std::ofstream fs_address_1("./test/lego-sensor/sensor1/address");
    std::ofstream fs_mode_1("./test/lego-sensor/sensor1/mode");
    std::ofstream fs_modes_1("./test/lego-sensor/sensor1/modes");
    std::ofstream fs_num_values_1("./test/lego-sensor/sensor1/num_values");
    std::ofstream fs_poll_ms_1("./test/lego-sensor/sensor1/poll_ms");
    std::ofstream fs_value0_1("./test/lego-sensor/sensor1/value0");
    std::ofstream fs_command_1("./test/lego-sensor/sensor1/command");
    std::ofstream fs_commands_1("./test/lego-sensor/sensor1/commands");


    ASSERT_TRUE(fs_address_0.is_open());
    ASSERT_TRUE(fs_mode_0.is_open());
    ASSERT_TRUE(fs_modes_0.is_open());
    ASSERT_TRUE(fs_num_values_0.is_open());
    ASSERT_TRUE(fs_poll_ms_0.is_open());
    ASSERT_TRUE(fs_value0_0.is_open());
    ASSERT_TRUE(fs_command_0.is_open());
    ASSERT_TRUE(fs_commands_0.is_open());

    ASSERT_TRUE(fs_address_1.is_open());
    ASSERT_TRUE(fs_mode_1.is_open());
    ASSERT_TRUE(fs_modes_1.is_open());
    ASSERT_TRUE(fs_num_values_1.is_open());
    ASSERT_TRUE(fs_poll_ms_1.is_open());
    ASSERT_TRUE(fs_value0_1.is_open());
    ASSERT_TRUE(fs_command_1.is_open());
    ASSERT_TRUE(fs_commands_1.is_open());


    fs_address_0 << "ev3-ports:in1";
    fs_mode_0 << "EV3-ULTRASONIC";
    fs_modes_0 << "EV3-ULTRASONIC EV3-GYRO EV3-COLOR EV3-IR-PROX EV3-TOUCH";
    fs_num_values_0 << "1";
    fs_poll_ms_0 << "100";
    fs_value0_0 << "42";
    fs_command_0 << "value0";
    fs_commands_0 << "value0 value1 value2 value3";

    fs_address_1 << "ev3-ports:in2";
    fs_mode_1 << "EV3-ULTRASONIC";
    fs_modes_1 << "EV3-ULTRASONIC EV3-GYRO EV3-COLOR EV3-IR-PROX EV3-TOUCH";
    fs_num_values_1 << "1";
    fs_poll_ms_1 << "100";
    fs_value0_1 << "42";
    fs_command_1 << "value0";
    fs_commands_1 << "value0 value1 value2 value3";

    fs_address_0.close();
    fs_mode_0.close();
    fs_modes_0.close();
    fs_num_values_0.close();
    fs_poll_ms_0.close();
    fs_value0_0.close();
    fs_command_0.close();
    fs_commands_0.close();

    fs_address_1.close();
    fs_mode_1.close();
    fs_modes_1.close();
    fs_num_values_1.close();
    fs_poll_ms_1.close();
    fs_value0_1.close();
    fs_command_1.close();
    fs_commands_1.close();

}