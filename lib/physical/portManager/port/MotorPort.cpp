#include "MotorPort.hpp"

namespace finder
{
    namespace physical
    {
        ::finder::console::Logger MotorPort::_logger = ::finder::console::Logger{};

        /*
        MotorPort::MotorPort() : Port()
        {
            init();
        }
        */

        MotorPort::MotorPort(std::string port_name) : Port(port_name)
        {
            init();
        }

        MotorPort::MotorPort(std::shared_ptr<Port> port) : Port(port)
        {
            init();
        }

        path_speed_t MotorPort::getSpeedPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/speed_sp";
            } else {
                return "";
            }
        }

        path_position_sp_t MotorPort::getPositionSpPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/position_sp";
            } else {
                return "";
            }
        }

        path_duty_cycle_t MotorPort::getDutyCyclePath()
        {
            if (isEnabled()) {
                return getBasePath() + "/duty_cycle_sp";
            } else {
                return "";
            }
        }

        path_state_t MotorPort::getStatePath()
        {
            if (isEnabled()) {
                return getBasePath() + "/state";
            } else {
                return "";
            }
        }

        path_polarity_t MotorPort::getPolarityPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/polarity";
            } else {
                return "";
            }
        }

        path_stop_action_t MotorPort::getStopActionPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/stop_action";
            } else {
                return "";
            }
        }

        path_count_per_rotation_t MotorPort::getCountPerRotationPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/count_per_rot";
            } else {
                return "";
            }
        }

        void MotorPort::setSpeed(int speed)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("SPEED.SET: " + std::to_string(speed) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_speed_path->is_open()) {
                    *_file_speed_path << speed;
                    _file_speed_path->flush();
                } else {
                    _logger.error("MotorPort failed to set speed");
                }
            } else {
                // _init_future.wait();
                // setSpeed(speed);
            }
        }

        void MotorPort::setPositionSp(int position_sp)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("POSITION_SP.SET: " + std::to_string(position_sp) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_position_sp_path->is_open()) {
                    *_file_position_sp_path << position_sp;
                    _file_position_sp_path->flush();
                } else {
                    _logger.error("MotorPort failed to set position_sp");
                }
            } else {
                // _init_future.wait();
                // setPositionSp(position_sp);
            }
        }

        void MotorPort::setDutyCycle(int duty_cycle)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("DUTY_CYCLE.SET: " + std::to_string(duty_cycle) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_duty_cycle_path->is_open()) {
                    *_file_duty_cycle_path << duty_cycle;
                    _file_duty_cycle_path->flush();
                } else {
                    _logger.error("MotorPort failed to set duty_cycle");
                }
            } else {
                // _init_future.wait();
                // setDutyCycle(duty_cycle);
            }
        }

        void MotorPort::setPolarity(MotorPolarity polarity)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("POLARITY.SET: " + std::to_string(static_cast<int>(polarity)) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_polarity_path->is_open()) {
                    *_file_polarity_path << static_cast<int>(polarity);
                    _file_polarity_path->flush();
                } else {
                    _logger.error("MotorPort failed to set polarity");
                }
            } else {
                // _init_future.wait();
                // setPolarity(polarity);
            }
        }

        void MotorPort::setStopAction(MotorStopAction stop_action)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("STOP_ACTION.SET: " + std::to_string(static_cast<int>(stop_action)) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_stop_action_path->is_open()) {
                    *_file_stop_action_path << static_cast<int>(stop_action);
                    _file_stop_action_path->flush();
                } else {
                    _logger.error("MotorPort failed to set stop_action");
                }
            } else {
                // _init_future.wait();
                // setStopAction(stop_action);
            }
        }

        void MotorPort::setCommand(MotorCommand command)
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COMMAND.SET: " + std::to_string(static_cast<int>(command)) + " FOR: " + getBasePath());

            if (isEnabled()) {
                if (_file_command_path->is_open()) {
                    if (command == MotorCommand::STOP) {
                        *_file_command_path << "stop";
                    } else if (command == MotorCommand::RUN_DIRECT) {
                        *_file_command_path << "run-direct";
                    } else if (command == MotorCommand::RUN_FOREVER) {
                        *_file_command_path << "run-forever";
                    } else if (command == MotorCommand::RUN_TO_ABS_POS) {
                        *_file_command_path << "run-to-abs-pos";
                    } else if (command == MotorCommand::RUN_TO_REL_POS) {
                        *_file_command_path << "run-to-rel-pos";
                    } else if (command == MotorCommand::RUN_TIMED) {
                        *_file_command_path << "run-timed";
                    } else if (command == MotorCommand::RESET) {
                        *_file_command_path << "reset";
                    } else {
                        _logger.error("MotorPort failed to set command");
                    }
                    _file_command_path->flush();
                } else {
                    _logger.error("MotorPort failed to set command");
                }
            } else {
                // _init_future.wait();
                // setCommand(command);
            }
        }

        std::vector<MotorState> MotorPort::getState()
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("STATE.GET: " + getBasePath());

            // return std::async(std::launch::async, [this]() {
                std::vector<MotorState> states;
                if (isEnabled()) {
                    if (_file_state_path->is_open()) {
                        std::string state;
                        *_file_state_path >> state;
                        // split state string by space
                        std::istringstream iss(state);
                        std::vector<std::string> state_tokens;
                        for (std::string s; iss >> s;) {
                            state_tokens.push_back(s);
                        }
                        for (auto token : state_tokens) {
                            if (token == "running") {
                                states.push_back(MotorState::RUNNING);
                            } else if (token == "ramping") {
                                states.push_back(MotorState::RAMPING);
                            } else if (token == "holding") {
                                states.push_back(MotorState::HOLDING);
                            } else if (token == "overloaded") {
                                states.push_back(MotorState::OVERLOADED);
                            } else if (token == "stalled") {
                                states.push_back(MotorState::STALLED);
                            } else if (token == "stopped") {
                                states.push_back(MotorState::STOPPED);
                            } else {
                                _logger.error("MotorPort failed to parse state");
                            }
                        }
                    } else {
                        _logger.error("MotorPort failed to get state");
                    }
                } else {
                    // _init_future.wait();
                    // return getState().get();
                } 
                for (auto s : states) {
                    logToFile(" WITH_RESULT: " + std::to_string(static_cast<int>(s)));
                }
                return states;
            // });
        }

        int MotorPort::getCountPerRotation()
        {
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COUNT_PER_ROTATION.GET: " + getBasePath());

            // return std::async(std::launch::async, [this]() {
                if (isEnabled()) {
                    if (_file_count_per_rotation_path->is_open()) {
                        int count_per_rotation;
                        *_file_count_per_rotation_path >> count_per_rotation;
                        logToFile(" WITH_RESULT: " + std::to_string(count_per_rotation));
                        return count_per_rotation;
                    } else {
                        _logger.error("MotorPort failed to get count_per_rotation");
                    }
                } else {
                    // _init_future.wait();
                    // return getCountPerRotation().get();
                }
                return -1;
            // });
        }

        DeviceType MotorPort::getDeviceType()
        {
            if(Port::getDeviceType() != DeviceType::MOTOR) {
                throw new std::runtime_error(
                    "MotorPort::getDeviceType() called on non-motor port"
                );
            }
            return DeviceType::MOTOR;
        }

        void MotorPort::init()
        {
            // _init_future = std::async(std::launch::async, [this]() {
                if (
                    isEnabled() &&
                    std::filesystem::exists(getBasePath()) &&
                    std::filesystem::exists(getAddressPath()) &&
                    std::filesystem::exists(getCommandPath()) &&
                    std::filesystem::exists(getSpeedPath()) &&
                    std::filesystem::exists(getPositionSpPath()) &&
                    std::filesystem::exists(getDutyCyclePath()) &&
                    std::filesystem::exists(getStatePath()) &&
                    std::filesystem::exists(getPolarityPath()) &&
                    std::filesystem::exists(getStopActionPath()) &&
                    std::filesystem::exists(getCountPerRotationPath())
                ) {
                    _file_command_path = std::make_shared<std::ofstream>(getCommandPath());
                    _file_speed_path = std::make_shared<std::ofstream>(getSpeedPath());
                    _file_position_sp_path = std::make_shared<std::ofstream>(getPositionSpPath());
                    _file_duty_cycle_path = std::make_shared<std::ofstream>(getDutyCyclePath());
                    _file_state_path = std::make_shared<std::ifstream>(getStatePath());
                    _file_polarity_path = std::make_shared<std::ofstream>(getPolarityPath());
                    _file_stop_action_path = std::make_shared<std::ofstream>(getStopActionPath());
                    _file_count_per_rotation_path = std::make_shared<std::ifstream>(getCountPerRotationPath());

                    if (
                        _file_command_path->is_open() &&
                        _file_speed_path->is_open() &&
                        _file_position_sp_path->is_open() &&
                        _file_duty_cycle_path->is_open() &&
                        _file_state_path->is_open() &&
                        _file_polarity_path->is_open() &&
                        _file_stop_action_path->is_open() &&
                        _file_count_per_rotation_path->is_open()
                    ) {
                        _logger.debug(
                            "MotorPort initialized"
                        );
                    } else {
                        _logger.error("MotorPort failed to initialize" + getBasePath());
                    }
                } else {
                    _logger.error("MotorPort is not enabled or paths do not exist");
                }
            // });
        }
    }
}