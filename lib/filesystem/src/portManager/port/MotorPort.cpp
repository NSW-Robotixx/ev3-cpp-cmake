#include "MotorPort.hpp"


namespace finder
{
    namespace physical
    {
        MotorPort::MotorPort(std::string port_name) : Port(port_name)
        {
            spdlog::trace("MotorPort::MotorPort(std::string port_name)");
            boost::leaf::result<void> status = init();
            if (!status) {
                spdlog::error("MotorPort failed to initialize:");
                throw std::runtime_error(std::string("MotorPort failed to initialize"));
            }
        }

        MotorPort::MotorPort(std::shared_ptr<Port> port) : Port(port)
        {
            spdlog::trace("MotorPort::MotorPort(std::shared_ptr<Port> port)");
            boost::leaf::result<void> status = init();
            if (!status) {
                spdlog::error("MotorPort failed to initialize");
                throw status.error();
            }
        }

        boost::leaf::result<path_speed_t> MotorPort::getSpeedSpPath()
        {
            spdlog::trace("MotorPort::getSpeedSpPath()");

            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_speed_t> path = getBasePath();
                if (path) {
                    return path.value() + "/speed_sp";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_position_t> MotorPort::getPositionPath()
        {
            spdlog::trace("MotorPort::getPositionPath()");

            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_position_t> path = getBasePath();
                if (path) {
                    return path.value() + "/position";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_speed_t> MotorPort::getSpeedPath()
        {
            spdlog::trace("MotorPort::getSpeedPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_speed_t> path = getBasePath();
                if (path) {
                    return path.value() + "/speed";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_position_sp_t> MotorPort::getPositionSpPath()
        {
            spdlog::trace("MotorPort::getPositionSpPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_position_sp_t> path = getBasePath();
                if (path) {
                    return path.value() + "/position_sp";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_duty_cycle_t> MotorPort::getDutyCyclePath()
        {
            spdlog::trace("MotorPort::getDutyCyclePath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_duty_cycle_t> path = getBasePath();
                if (path) {
                    return path.value() + "/duty_cycle_sp";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_state_t> MotorPort::getStatePath()
        {
            spdlog::trace("MotorPort::getStatePath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_state_t> path = getBasePath();
                if (path) {
                    return path.value() + "/state";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_polarity_t> MotorPort::getPolarityPath()
        {
            spdlog::trace("MotorPort::getPolarityPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_polarity_t> path = getBasePath();
                if (path) {
                    return path.value() + "/polarity";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_stop_action_t> MotorPort::getStopActionPath()
        {
            spdlog::trace("MotorPort::getStopActionPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_stop_action_t> path = getBasePath();
                if (path) {
                    return path.value() + "/stop_action";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_count_per_rotation_t> MotorPort::getCountPerRotationPath()
        {
            spdlog::trace("MotorPort::getCountPerRotationPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_count_per_rotation_t> path = getBasePath();
                if (path) {
                    return path.value() + "/count_per_rot";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        
        boost::leaf::result<path_max_speed_t> MotorPort::getMaxSpeedPath()
        {
            spdlog::trace("MotorPort::getMaxSpeedPath()");
            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<path_max_speed_t> path = getBasePath();
                if (path) {
                    return path.value() + "/max_speed";
                } else {
                    return boost::leaf::new_error(std::invalid_argument("Failed to get base path"));
                }
            } else {
                spdlog::warn("Port is not enabled");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        void MotorPort::setSpeed(int speed)
        {
            spdlog::trace("MotorPort::setSpeed()");

            if (isEnabled() && *isEnabled()) {
                if (_file_speed_sp_path->is_open()) {
                    *_file_speed_sp_path << speed;
                    _file_speed_sp_path->flush();
                } else {
                    spdlog::error("failed to write to speed file for");
                }
            } else {
                spdlog::error("Port is not enabled for");
                // _init_future.wait();
                // setSpeed(speed);
            }
        }

        boost::leaf::result<void> MotorPort::setPositionSp(int position_sp)
        {
            spdlog::trace("MotorPort::setPositionSp()");

            if (isEnabled() && *isEnabled()) {
                if (!_file_position_sp_path->bad()) {
                    if (_file_position_sp_path->is_open()) {
                        *_file_position_sp_path << position_sp;
                        _file_position_sp_path->flush();
                    } else {
                        spdlog::error("failed to write to position_sp file for");
                        return boost::leaf::new_error(std::invalid_argument("failed to write to position_sp file for: " + _path));
                    }
                } else {
                    return boost::leaf::new_error(std::invalid_argument("position_sp file is bad for: " + _path));
                }
            } else {
                spdlog::error("Port is not enabled for");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled for: " + _path));
                // _init_future.wait();
                // setPositionSp(position_sp);
            }
            return boost::leaf::result<void>();
        }

        void MotorPort::setDutyCycle(int duty_cycle)
        {
            spdlog::trace("MotorPort::setDutyCycle()");

            if (isEnabled() && *isEnabled()) {
                if (_file_duty_cycle_path->is_open()) {
                    *_file_duty_cycle_path << duty_cycle;
                    _file_duty_cycle_path->flush();
                } else {
                    spdlog::error("failed to write to duty_cycle file for");
                }
            } else {
                spdlog::error("Port is not enabled for");
                // _init_future.wait();
                // setDutyCycle(duty_cycle);
            }
        }

        void MotorPort::setPolarity(MotorPolarity polarity)
        {
            spdlog::trace("MotorPort::setPolarity()");

            if (isEnabled() && *isEnabled()) {
                if (_file_polarity_path->is_open()) {
                    if (polarity == MotorPolarity::NORMAL) {
                        *_file_polarity_path << "normal";
                    } else if (polarity == MotorPolarity::INVERSED) {
                        *_file_polarity_path << "inversed";
                    } else {
                        spdlog::error("MotorPort failed to write to files for");
                        throw std::runtime_error("MotorPort failed to set polarity");
                    }
                    _file_polarity_path->flush();
                } else {
                    spdlog::error("MotorPort failed to set polarity for");
                }
            } else {
                spdlog::error("Port is not enabled for");
                // _init_future.wait();
                // setPolarity(polarity);
            }
        }

        void MotorPort::setStopAction(MotorStopAction stop_action)
        {
            spdlog::trace("MotorPort::setStopAction()");

            if (isEnabled() && *isEnabled()) {
                if (_file_stop_action_path->is_open()) {
                    if (stop_action == MotorStopAction::COAST) {
                        *_file_stop_action_path << "coast";
                    } else if (stop_action == MotorStopAction::BRAKE) {
                        *_file_stop_action_path << "brake";
                    } else if (stop_action == MotorStopAction::HOLD) {
                        *_file_stop_action_path << "hold";
                    } else {
                        spdlog::error("MotorPort failed to write to files for");
                        throw std::runtime_error("MotorPort failed to set stop_action");
                    }
                    _file_stop_action_path->flush();
                } else {
                    spdlog::error("MotorPort failed to set stop_action for");
                }
            } else {
                spdlog::error("Port is not enabled for");
                // _init_future.wait();
                // setStopAction(stop_action);
            }
        }

        boost::leaf::result<void> MotorPort::setCommand(MotorCommand command)
        {
            spdlog::trace("MotorPort::setCommand()");

            if (command == MotorCommand::STOP) {
                spdlog::debug(("Setting command to stop for: " + _path));
                *this->_file_command_path << "stop";
            } else if (command == MotorCommand::RUN_DIRECT) {
                spdlog::debug(("Setting command to run-direct for" + _path));
                *this->_file_command_path << "run-direct";
            } else if (command == MotorCommand::RUN_FOREVER) {
                spdlog::debug(("Setting command to run-forever for" + _path));
                *this->_file_command_path << "run-forever";
            } else if (command == MotorCommand::RUN_TO_ABS_POS) {
                spdlog::debug(("Setting command to run-to-abs-pos for" + _path));
                *this->_file_command_path << "run-to-abs-pos";
            } else if (command == MotorCommand::RUN_TO_REL_POS) {
                spdlog::debug(("Setting command to run-to-rel-pos for" + _path));
                *this->_file_command_path << "run-to-rel-pos";
            } else if (command == MotorCommand::RUN_TIMED) {
                spdlog::debug(("Setting command to run-timed for" + _path));
                *this->_file_command_path << "run-timed";
            } else if (command == MotorCommand::RESET) {
                spdlog::debug(("Setting command to reset for" + _path));
                *this->_file_command_path << "reset";
            } else {
                spdlog::error("MotorPort failed to set command for");
                return boost::leaf::new_error(std::invalid_argument("MotorPort failed to set command: " + _path));
            }
            this->_file_command_path->flush();
            return boost::leaf::result<void>();
        }

        boost::leaf::result<void> MotorPort::stop()
        {
            spdlog::trace("MotorPort::stop()");
            if (isEnabled() && *isEnabled()) {
                ABSL_RETURN_IF_ERROR(setCommand(MotorCommand::STOP));
            } else {
                spdlog::error("Port is not enabled for");
            }
            return boost::leaf::result<void>();
        }

        int MotorPort::getSpeed() 
        {
            spdlog::trace("MotorPort::getSpeed()");

            if (isEnabled() && *isEnabled()) {
                if (_file_speed_path->is_open()) {
                    if (!_file_speed_path->bad()) {
                        int speed;
                        *_file_speed_path >> speed;
                        spdlog::debug(("SPEED.GET: WITH_RESULT: %d"), speed);
                        return speed;
                    }
                }
            } 
            spdlog::error("MotorPort failed to get speed for");
            return -1;
        }

        int MotorPort::getPosition()
        {
            spdlog::trace("MotorPort::getPosition()");

            if (isEnabled() && *isEnabled()) {
                if (_file_position_path->is_open()) {
                    if (!_file_position_path->bad()) {
                        int position;
                        *_file_position_path >> position;

                        spdlog::debug(("POSITION.GET: WITH_RESULT: {}"), position);
                        return position;
                    }
                    spdlog::error("MotorPort failed to get position, File bad for");
                    throw std::runtime_error("MotorPort failed to get position, File bad");
                }
                spdlog::error("MotorPort failed to get position, File not open for");
                throw std::runtime_error("MotorPort failed to get position, File not open");
            }
            spdlog::error("MotorPort failed to get position, Port not enabled for");
            throw std::runtime_error("MotorPort failed to get position, Port not enabled");
        }

        std::vector<MotorState> MotorPort::getState()
        {
            spdlog::trace("MotorPort::getState()");

            // return std::async(std::launch::async, [this]() {
                std::vector<MotorState> states;
                if (isEnabled() && *isEnabled()) {
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
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::RUNNING));
                                states.push_back(MotorState::RUNNING);
                            } else if (token == "ramping") {
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::RAMPING));
                                states.push_back(MotorState::RAMPING);
                            } else if (token == "holding") {
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::HOLDING));
                                states.push_back(MotorState::HOLDING);
                            } else if (token == "overloaded") {
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::OVERLOADED));
                                states.push_back(MotorState::OVERLOADED);
                            } else if (token == "stalled") {
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::STALLED));
                                states.push_back(MotorState::STALLED);
                            } else if (token == "stopped") {
                                spdlog::debug(("STATE.GET: WITH_RESULT: %d"), static_cast<int>(MotorState::STOPPED));
                                states.push_back(MotorState::STOPPED);
                            } else {
                                spdlog::error("MotorPort failed to get state for"), token;
                            }
                        }
                    } else {
                        spdlog::error("MotorPort failed to get state for");
                    }
                } else {
                    spdlog::error("Port is not enabled for");
                    // _init_future.wait();
                    // return getState().get();
                } 
                for (auto s : states) {
                    spdlog::info(("STATE.GET: WITH_RESULT:"), static_cast<int>(s));
                }
                return states;
            // });
        }

        int MotorPort::getCountPerRotation()
        {
            spdlog::trace("MotorPort::getCountPerRotation()");

            // return std::async(std::launch::async, [this]() {
                if (isEnabled() && *isEnabled()) {
                    if (_file_count_per_rotation_path->is_open()) {
                        int count_per_rotation;
                        *_file_count_per_rotation_path >> count_per_rotation;
                        spdlog::info(("COUNT_PER_ROTATION.GET: WITH_RESULT: %d"), count_per_rotation);
                        return count_per_rotation;
                    } else {
                        spdlog::error("MotorPort failed to get count_per_rotation for");
                    }
                } else {
                    spdlog::error("Port is not enabled for");
                    // _init_future.wait();
                    // return getCountPerRotation().get();
                }
                return -1;
            // });
        }

        int MotorPort::getMaxSpeed()
        {
            spdlog::trace("MotorPort::getMaxSpeed()");

                // return std::async(std::launch::async, [this]() {
                    if (isEnabled() && *isEnabled()) {
                        if (_file_max_speed_path->is_open()) {
                            int max_speed;
                            *_file_max_speed_path >> max_speed;
                            spdlog::info(("MAX_SPEED.GET: WITH_RESULT: %d"), max_speed);
                            return max_speed;
                        } else {
                            spdlog::error("MotorPort failed to get max_speed for");
                        }
                    } else {
                        spdlog::error("Port is not enabled for");
                    }
                    return -1;
                // });
        }

        boost::leaf::result<DeviceType> MotorPort::getDeviceType()
        {
            spdlog::trace("MotorPort::getDeviceType()");

            boost::leaf::result<DeviceType> device_type = Port::getDeviceType();
            if(device_type && device_type.value() != DeviceType::MOTOR) {
                spdlog::error("MotorPort::getDeviceType() called on non-motor port");
                return boost::leaf::new_error(std::invalid_argument("MotorPort::getDeviceType() called on non-motor port"));
            }
            return DeviceType::MOTOR;
        }

        boost::leaf::result<void> MotorPort::moveToAbsPosition(int abs_position_sp)
        {
            spdlog::trace("MotorPort::moveToAbsPosition()");

            if (isEnabled() && *isEnabled()) {
                boost::leaf::result<void> status = setPositionSp(abs_position_sp);
                if (!status) {
                    spdlog::error("MotorPort failed to move to position for");
                    return status;
                }

                status = setCommand(MotorCommand::RUN_TO_ABS_POS);
                if (!status) {
                    spdlog::error("MotorPort failed to move to position for");
                    return status;
                }
            } else {
                spdlog::error("Port is not enabled for");
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled for: " + _path));
            }
            return boost::leaf::result<void>();
        }

        boost::leaf::result<void> MotorPort::waitUntilStopped()
        {
            while (true) {
                std::vector<MotorState> states = getState();
                if (std::find(states.begin(), states.end(), MotorState::STOPPED) != states.end()) {
                    if constexpr (EV3_DETAILED_LOGGING) {
                        spdlog::info("MotorPort::waitUntilStopped() still running: "+ std::to_string(getPosition()));
                    } else {
                        spdlog::info("MotorPort::waitUntilStopped() still running");
                    }
                    return boost::leaf::result<void>();
                }
            }
        }

        boost::leaf::result<void> MotorPort::reset()
        {
            spdlog::trace("MotorPort::reset()");

            boost::leaf::result<void> stopStatus = stop();
            if (!stopStatus) {
                spdlog::error("MotorPort failed to reset for");
            }

            boost::leaf::result<void> resetStatus = setCommand(MotorCommand::RESET);
            if (!resetStatus) {
                spdlog::error("MotorPort failed to reset for");
            } else {
                spdlog::debug(("MotorPort reset for"));
            }

            // exit all files
            _file_speed_sp_path->close();
            _file_position_sp_path->close();
            _file_duty_cycle_path->close();
            _file_state_path->close();
            _file_polarity_path->close();
            _file_stop_action_path->close();
            _file_count_per_rotation_path->close();
            _file_max_speed_path->close();

            if (std::filesystem::exists(_path)) {
                boost::leaf::result<void> initStatus = init();
                if (!initStatus) {
                    spdlog::error("MotorPort failed to reset for");
                    return initStatus;
                }

                _position = getPosition();
                return boost::leaf::result<void>();
            } else {
                return boost::leaf::new_error(std::invalid_argument("MotorPort failed to reset, path does not exist"));
            }
        }

        boost::leaf::result<void> MotorPort::init()
        {
            // return std::async(std::launch::async, [this]() {
                spdlog::trace("MotorPort::init()");

                // absl::call_once(_init_flag, &MotorPort::init, this);

                boost::leaf::result<bool> enabled = isEnabled();
                boost::leaf::result<path_port_t> base_path = getBasePath();
                boost::leaf::result<path_address_t> address_path = getAddressPath();
                boost::leaf::result<path_command_t> command_path = getCommandPath();
                boost::leaf::result<path_speed_t> speed_path = getSpeedPath();
                boost::leaf::result<path_speed_t> speed_sp_path = getSpeedSpPath();
                boost::leaf::result<path_position_t> position_path = getPositionPath();
                boost::leaf::result<path_position_sp_t> position_sp_path = getPositionSpPath();
                boost::leaf::result<path_duty_cycle_t> duty_cycle_path = getDutyCyclePath();
                boost::leaf::result<path_state_t> state_path = getStatePath();
                boost::leaf::result<path_polarity_t> polarity_path = getPolarityPath();
                boost::leaf::result<path_stop_action_t> stop_action_path = getStopActionPath();
                boost::leaf::result<path_count_per_rotation_t> count_per_rotation_path = getCountPerRotationPath();

                spdlog::debug(("MotorPort::init() for"));
                
                if (!enabled) { 
                    spdlog::error("MotorPort failed to initialize, port is not enabled");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, port is not enabled"));
                }
                if (!base_path) {
                    spdlog::error("MotorPort failed to initialize, base path is not valid");
                    return base_path.error();
                }
                if (!address_path) {
                    spdlog::error("MotorPort failed to initialize, address path is not valid");
                    return address_path.error();
                }
                if (!command_path) {
                    spdlog::error("MotorPort failed to initialize, command path is not valid");
                    return command_path.error();
                }
                if (!speed_path) {
                    spdlog::error("MotorPort failed to initialize, speed path is not valid");
                    return speed_path.error();
                }
                if (!speed_sp_path) {
                    spdlog::error("MotorPort failed to initialize, speed_sp path is not valid");
                    return speed_sp_path.error();
                }
                if (!position_path) {
                    spdlog::error("MotorPort failed to initialize, position path is not valid");
                    return position_path.error();
                }
                if (!position_sp_path) {
                    spdlog::error("MotorPort failed to initialize, position_sp path is not valid");
                    return position_sp_path.error();
                }
                if (!duty_cycle_path) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle path is not valid");
                    return duty_cycle_path.error();
                }
                if (!state_path) {
                    spdlog::error("MotorPort failed to initialize, state path is not valid");
                    return state_path.error();
                }
                if (!polarity_path) {
                    spdlog::error("MotorPort failed to initialize, polarity path is not valid");
                    return polarity_path.error();
                }
                if (!stop_action_path) {
                    spdlog::error("MotorPort failed to initialize, stop_action path is not valid");
                    return stop_action_path.error();
                }
                if (!count_per_rotation_path) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation path is not valid");
                    return count_per_rotation_path.error();
                }

                spdlog::debug("MotorPort::init() paths are valid");

                if (!std::filesystem::exists(base_path.value())) {
                    spdlog::error("MotorPort failed to initialize, base path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, base path does not exist"));
                }
                if (!std::filesystem::exists(address_path.value())) {
                    spdlog::error("MotorPort failed to initialize, address path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, address path does not exist"));
                }
                if (!std::filesystem::exists(command_path.value())) {
                    spdlog::error("MotorPort failed to initialize, command path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, command path does not exist"));
                }
                if (!std::filesystem::exists(speed_path.value())) {
                    spdlog::error("MotorPort failed to initialize, speed path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, speed path does not exist"));
                }
                if (!std::filesystem::exists(speed_sp_path.value())) {
                    spdlog::error("MotorPort failed to initialize, speed_sp path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, speed_sp path does not exist"));
                }
                if (!std::filesystem::exists(position_path.value())) {
                    spdlog::error("MotorPort failed to initialize, position path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, position path does not exist"));
                }
                if (!std::filesystem::exists(position_sp_path.value())) {
                    spdlog::error("MotorPort failed to initialize, position_sp path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, position_sp path does not exist"));
                }
                if (!std::filesystem::exists(duty_cycle_path.value())) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, duty_cycle path does not exist"));
                }
                if (!std::filesystem::exists(state_path.value())) {
                    spdlog::error("MotorPort failed to initialize, state path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, state path does not exist"));
                }
                if (!std::filesystem::exists(polarity_path.value())) {
                    spdlog::error("MotorPort failed to initialize, polarity path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, polarity path does not exist"));
                }
                if (!std::filesystem::exists(stop_action_path.value())) {
                    spdlog::error("MotorPort failed to initialize, stop_action path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, stop_action path does not exist"));
                }
                if (!std::filesystem::exists(count_per_rotation_path.value())) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation path does not exist");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, count_per_rotation path does not exist"));
                }

                spdlog::debug("MotorPort::init() paths exist");

                _file_command_path = std::make_shared<std::ofstream>(command_path.value());
                _file_speed_path = std::make_shared<std::ifstream>(speed_path.value());
                _file_speed_sp_path = std::make_shared<std::ofstream>(speed_sp_path.value());
                _file_position_path = std::make_shared<std::ifstream>(position_path.value());
                _file_position_sp_path = std::make_shared<std::ofstream>(position_sp_path.value());
                _file_duty_cycle_path = std::make_shared<std::ofstream>(duty_cycle_path.value());
                _file_state_path = std::make_shared<std::ifstream>(state_path.value());
                _file_polarity_path = std::make_shared<std::ofstream>(polarity_path.value());
                _file_stop_action_path = std::make_shared<std::ofstream>(stop_action_path.value());
                _file_count_per_rotation_path = std::make_shared<std::ifstream>(count_per_rotation_path.value());

                spdlog::debug("MotorPort::init() file readers created");

                if (!_file_command_path->is_open() || _file_command_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, command file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, command file is not open"));
                }
                if (!_file_speed_path->is_open() || _file_speed_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, speed file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, speed file is not open"));
                }
                if (!_file_speed_sp_path->is_open() || _file_speed_sp_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, speed_sp file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, speed_sp file is not open"));
                }
                if (!_file_position_path->is_open() || _file_position_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, position file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, position file is not open"));
                }
                if (!_file_position_sp_path->is_open() || _file_position_sp_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, position_sp file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, position_sp file is not open"));
                }
                if (!_file_duty_cycle_path->is_open() || _file_duty_cycle_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, duty_cycle file is not open"));
                }
                if (!_file_state_path->is_open() || _file_state_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, state file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, state file is not open"));
                }
                if (!_file_polarity_path->is_open() || _file_polarity_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, polarity file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, polarity file is not open"));
                }
                if (!_file_stop_action_path->is_open() || _file_stop_action_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, stop_action file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, stop_action file is not open"));
                }
                if (!_file_count_per_rotation_path->is_open() || _file_count_per_rotation_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation file is not open");
                    return boost::leaf::new_error(std::invalid_argument("MotorPort failed to initialize, count_per_rotation file is not open"));
                }

                spdlog::debug("MotorPort::init() file readers opened");

                _position = getPosition();

                return boost::leaf::result<void>();
            // }).get();
        }
    }
}