#include "MotorPort.hpp"

namespace finder
{
    namespace physical
    {
#ifdef ENABLE_LOGGING
        ::finder::log::Logger MotorPort::_logger = ::finder::log::Logger{};
#endif
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

        path_speed_t MotorPort::getSpeedSpPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/speed_sp";
            } else {
                return "";
            }
        }

        path_position_t MotorPort::getPositionPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/position";
            } else {
                return "";
            }
        }

        path_speed_t MotorPort::getSpeedPath()
        {
            if (isEnabled()) {
                return getBasePath() + "/speed";
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
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("SPEED.SET: " + std::to_string(speed) + " FOR: " + getBasePath());
#endif

            if (isEnabled()) {
                if (_file_speed_sp_path->is_open()) {
                    *_file_speed_sp_path << speed;
                    _file_speed_sp_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set speed");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setSpeed(speed);
            }
        }

        void MotorPort::setPositionSp(int position_sp)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("POSITION_SP.SET: " + std::to_string(position_sp) + " FOR: " + getBasePath());
#endif

            if (isEnabled()) {
                if (_file_position_sp_path->is_open()) {
                    *_file_position_sp_path << position_sp;
                    _file_position_sp_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set position_sp");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setPositionSp(position_sp);
            }
        }

        void MotorPort::setDutyCycle(int duty_cycle)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("DUTY_CYCLE.SET: " + std::to_string(duty_cycle) + " FOR: " + getBasePath());
#endif

            if (isEnabled()) {
                if (_file_duty_cycle_path->is_open()) {
                    *_file_duty_cycle_path << duty_cycle;
                    _file_duty_cycle_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set duty_cycle");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setDutyCycle(duty_cycle);
            }
        }

        void MotorPort::setPolarity(MotorPolarity polarity)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("POLARITY.SET: " + std::to_string(static_cast<int>(polarity)) + " FOR: " + getBasePath());
#endif

            if (isEnabled()) {
                if (_file_polarity_path->is_open()) {
                    if (polarity == MotorPolarity::NORMAL) {
                        *_file_polarity_path << "normal";
                    } else if (polarity == MotorPolarity::INVERSED) {
                        *_file_polarity_path << "inversed";
                    } else {
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to set polarity");
#endif
                        throw std::runtime_error("MotorPort failed to set polarity");
                    }
                    _file_polarity_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set polarity");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setPolarity(polarity);
            }
        }

        void MotorPort::setStopAction(MotorStopAction stop_action)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("STOP_ACTION.SET: " + std::to_string(static_cast<int>(stop_action)) + " FOR: " + getBasePath());
#endif

            if (isEnabled()) {
                if (_file_stop_action_path->is_open()) {
                    if (stop_action == MotorStopAction::COAST) {
                        *_file_stop_action_path << "coast";
                    } else if (stop_action == MotorStopAction::BRAKE) {
                        *_file_stop_action_path << "brake";
                    } else if (stop_action == MotorStopAction::HOLD) {
                        *_file_stop_action_path << "hold";
                    } else {
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to set stop_action");
#endif
                        throw std::runtime_error("MotorPort failed to set stop_action");
                    }
                    _file_stop_action_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set stop_action");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setStopAction(stop_action);
            }
        }

        void MotorPort::setCommand(MotorCommand command)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COMMAND.SET: " + std::to_string(static_cast<int>(command)) + " FOR: " + getBasePath());
#endif

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
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to set command");
#endif                        
                    }
                    _file_command_path->flush();
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort failed to set command");
#endif                    
                }
            } else {
                // _init_future.wait();
                // setCommand(command);
            }
        }

        void MotorPort::stop()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("STOP: " + getBasePath());
#endif
    
            if (isEnabled()) {
                setCommand(MotorCommand::STOP);
            } else {
                // _init_future.wait();
                // stop();
            }
        }

        int MotorPort::getSpeed() 
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("SPEED.GET: " + getBasePath());
#endif
            if (isEnabled()) {
                if (_file_speed_path->is_open()) {
                    if (!_file_speed_path->bad()) {
                        int speed;
                        *_file_speed_path >> speed;
#ifdef ENABLE_LOGGING
                        logToFile(" WITH_RESULT: " + std::to_string(speed));
#endif
                        return speed;
                    }
                }
            } 
            return -1;
        }

        int MotorPort::getPosition()
        {
            if (isEnabled()) {
                if (_file_position_path->is_open()) {
                    if (!_file_position_path->bad()) {
                        int position;
                        *_file_position_path >> position;
#ifdef ENABLE_LOGGING
                        logToFile("POSITION_SP.GET: " + getBasePath() + " WITH_RESULT: " + std::to_string(position));
#endif
                        return position;
                    }
                    throw std::runtime_error("MotorPort failed to get position, File bad");
                }
                throw std::runtime_error("MotorPort failed to get position, File not open");
            }
            throw std::runtime_error("MotorPort failed to get position, Port not enabled");
        }

        std::vector<MotorState> MotorPort::getState()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("STATE.GET: " + getBasePath());
#endif

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
#ifdef ENABLE_LOGGING                                
                                _logger.error("MotorPort failed to parse state");
#endif                                
                            }
                        }
                    } else {
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to get state");
#endif                        
                    }
                } else {
                    // _init_future.wait();
                    // return getState().get();
                } 
                for (auto s : states) {
#ifdef ENABLE_LOGGING                    
                    logToFile(" WITH_RESULT: " + std::to_string(static_cast<int>(s)));
#endif                    
                }
                return states;
            // });
        }

        int MotorPort::getCountPerRotation()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COUNT_PER_ROTATION.GET: " + getBasePath());
#endif

            // return std::async(std::launch::async, [this]() {
                if (isEnabled()) {
                    if (_file_count_per_rotation_path->is_open()) {
                        int count_per_rotation;
                        *_file_count_per_rotation_path >> count_per_rotation;
#ifdef ENABLE_LOGGING
                        logToFile(" WITH_RESULT: " + std::to_string(count_per_rotation));
#endif                    
                        return count_per_rotation;
                    } else {
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to get count_per_rotation");
#endif                        
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
                    std::filesystem::exists(getSpeedSpPath()) &&
                    std::filesystem::exists(getPositionPath()) &&
                    std::filesystem::exists(getPositionSpPath()) &&
                    std::filesystem::exists(getDutyCyclePath()) &&
                    std::filesystem::exists(getStatePath()) &&
                    std::filesystem::exists(getPolarityPath()) &&
                    std::filesystem::exists(getStopActionPath()) &&
                    std::filesystem::exists(getCountPerRotationPath())
                ) {
                    _file_command_path = std::make_shared<std::ofstream>(getCommandPath());
                    _file_speed_path = std::make_shared<std::ifstream>(getSpeedPath());
                    _file_speed_sp_path = std::make_shared<std::ofstream>(getSpeedSpPath());
                    _file_position_path = std::make_shared<std::ifstream>(getPositionPath());
                    _file_position_sp_path = std::make_shared<std::ofstream>(getPositionSpPath());
                    _file_duty_cycle_path = std::make_shared<std::ofstream>(getDutyCyclePath());
                    _file_state_path = std::make_shared<std::ifstream>(getStatePath());
                    _file_polarity_path = std::make_shared<std::ofstream>(getPolarityPath());
                    _file_stop_action_path = std::make_shared<std::ofstream>(getStopActionPath());
                    _file_count_per_rotation_path = std::make_shared<std::ifstream>(getCountPerRotationPath());

                    if (
                        _file_command_path->is_open() &&
                        _file_speed_path->is_open() &&
                        _file_speed_sp_path->is_open() &&
                        _file_position_path->is_open() &&
                        _file_position_sp_path->is_open() &&
                        _file_duty_cycle_path->is_open() &&
                        _file_state_path->is_open() &&
                        _file_polarity_path->is_open() &&
                        _file_stop_action_path->is_open() &&
                        _file_count_per_rotation_path->is_open()
                    ) {
#ifdef ENABLE_LOGGING                        
                        _logger.debug("MotorPort initialized");
#endif
                    } else {
#ifdef ENABLE_LOGGING                        
                        _logger.error("MotorPort failed to initialize" + getBasePath());
#endif                        
                    }
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.error("MotorPort is not enabled or paths do not exist");
#endif                    
                }
            // });
        }
    }
}