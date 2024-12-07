#include "MotorPort.hpp"


namespace finder
{
    namespace physical
    {
        MotorPort::MotorPort(std::string port_name) : Port(port_name)
        {
            spdlog::trace("MotorPort::MotorPort(std::string port_name)");
            absl::Status status = init();
            if (!status.ok()) {
                spdlog::error("MotorPort failed to initialize: {}"), status.message();
                throw std::runtime_error(std::string("MotorPort failed to initialize: ").append(status.message()));
            }
        }

        MotorPort::MotorPort(std::shared_ptr<Port> port) : Port(port)
        {
            spdlog::trace("MotorPort::MotorPort(std::shared_ptr<Port> port)");
            absl::Status status = init();
            if (!status.ok()) {
                spdlog::error("MotorPort failed to initialize: {}"), status.message();
                throw std::runtime_error(std::string("MotorPort failed to initialize: ").append(status.message()));
            }
        }

        absl::StatusOr<path_speed_t> MotorPort::getSpeedSpPath()
        {
            spdlog::trace("MotorPort::getSpeedSpPath()");

            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_speed_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/speed_sp";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_position_t> MotorPort::getPositionPath()
        {
            spdlog::trace("MotorPort::getPositionPath()");

            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_position_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/position";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_speed_t> MotorPort::getSpeedPath()
        {
            spdlog::trace("MotorPort::getSpeedPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_speed_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/speed";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_position_sp_t> MotorPort::getPositionSpPath()
        {
            spdlog::trace("MotorPort::getPositionSpPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_position_sp_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/position_sp";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_duty_cycle_t> MotorPort::getDutyCyclePath()
        {
            spdlog::trace("MotorPort::getDutyCyclePath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_duty_cycle_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/duty_cycle";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_state_t> MotorPort::getStatePath()
        {
            spdlog::trace("MotorPort::getStatePath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_state_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/state";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_polarity_t> MotorPort::getPolarityPath()
        {
            spdlog::trace("MotorPort::getPolarityPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_polarity_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/polarity";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_stop_action_t> MotorPort::getStopActionPath()
        {
            spdlog::trace("MotorPort::getStopActionPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_stop_action_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/stop_action";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        absl::StatusOr<path_count_per_rotation_t> MotorPort::getCountPerRotationPath()
        {
            spdlog::trace("MotorPort::getCountPerRotationPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_count_per_rotation_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/count_per_rot";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        
        absl::StatusOr<path_max_speed_t> MotorPort::getMaxSpeedPath()
        {
            spdlog::trace("MotorPort::getMaxSpeedPath()");
            if (isEnabled().value_or(false)) {
                absl::StatusOr<path_max_speed_t> path = getBasePath();
                if (path.ok()) {
                    return path.value() + "/max_speed";
                } else {
                    return absl::InternalError("Failed to get base path");
                }
            } else {
                spdlog::warn("Port is not enabled");
                return absl::InvalidArgumentError("Port is not enabled: " + _path);
            }
        }

        void MotorPort::setSpeed(int speed)
        {
            spdlog::trace("MotorPort::setSpeed()");

            if (isEnabled().value_or(false)) {
                if (_file_speed_sp_path->is_open()) {
                    *_file_speed_sp_path << speed;
                    _file_speed_sp_path->flush();
                } else {
                    spdlog::error("failed to write to speed file for {}"), getBasePath().value_or("").c_str();
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                // _init_future.wait();
                // setSpeed(speed);
            }
        }

        absl::Status MotorPort::setPositionSp(int position_sp)
        {
            spdlog::trace("MotorPort::setPositionSp()");

            if (isEnabled().value_or(false)) {
                if (!_file_position_sp_path->bad()) {
                    if (_file_position_sp_path->is_open()) {
                        *_file_position_sp_path << position_sp;
                        _file_position_sp_path->flush();
                    } else {
                        spdlog::error("failed to write to position_sp file for {}"), getBasePath().value_or("").c_str();
                        return absl::InternalError("failed to write to position_sp file for: " + _path);
                    }
                } else {
                    return absl::InternalError("position_sp file is bad for: " + _path);
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                return absl::InvalidArgumentError("Port is not enabled for: " + _path);
                // _init_future.wait();
                // setPositionSp(position_sp);
            }
            return absl::OkStatus();
        }

        void MotorPort::setDutyCycle(int duty_cycle)
        {
            spdlog::trace("MotorPort::setDutyCycle()");

            if (isEnabled().value_or(false)) {
                if (_file_duty_cycle_path->is_open()) {
                    *_file_duty_cycle_path << duty_cycle;
                    _file_duty_cycle_path->flush();
                } else {
                    spdlog::error("failed to write to duty_cycle file for {}"), getBasePath().value_or("").c_str();
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                // _init_future.wait();
                // setDutyCycle(duty_cycle);
            }
        }

        void MotorPort::setPolarity(MotorPolarity polarity)
        {
            spdlog::trace("MotorPort::setPolarity()");

            if (isEnabled().value_or(false)) {
                if (_file_polarity_path->is_open()) {
                    if (polarity == MotorPolarity::NORMAL) {
                        *_file_polarity_path << "normal";
                    } else if (polarity == MotorPolarity::INVERSED) {
                        *_file_polarity_path << "inversed";
                    } else {
                        spdlog::error("MotorPort failed to write to files for {}"), getBasePath().value_or("").c_str();
                        throw std::runtime_error("MotorPort failed to set polarity");
                    }
                    _file_polarity_path->flush();
                } else {
                    spdlog::error("MotorPort failed to set polarity for {}"), getBasePath().value_or("").c_str();
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                // _init_future.wait();
                // setPolarity(polarity);
            }
        }

        void MotorPort::setStopAction(MotorStopAction stop_action)
        {
            spdlog::trace("MotorPort::setStopAction()");

            if (isEnabled().value_or(false)) {
                if (_file_stop_action_path->is_open()) {
                    if (stop_action == MotorStopAction::COAST) {
                        *_file_stop_action_path << "coast";
                    } else if (stop_action == MotorStopAction::BRAKE) {
                        *_file_stop_action_path << "brake";
                    } else if (stop_action == MotorStopAction::HOLD) {
                        *_file_stop_action_path << "hold";
                    } else {
                        spdlog::error("MotorPort failed to write to files for {}"), getBasePath().value_or("").c_str();
                        throw std::runtime_error("MotorPort failed to set stop_action");
                    }
                    _file_stop_action_path->flush();
                } else {
                    spdlog::error("MotorPort failed to set stop_action for {}"), getBasePath().value_or("").c_str();
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                // _init_future.wait();
                // setStopAction(stop_action);
            }
        }

        absl::Status MotorPort::setCommand(MotorCommand command)
        {
            spdlog::trace("MotorPort::setCommand()");
            if (command == MotorCommand::STOP) {
                spdlog::debug(("Setting command to stop for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "stop";
            } else if (command == MotorCommand::RUN_DIRECT) {
                spdlog::debug(("Setting command to run-direct for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "run-direct";
            } else if (command == MotorCommand::RUN_FOREVER) {
                spdlog::debug(("Setting command to run-forever for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "run-forever";
            } else if (command == MotorCommand::RUN_TO_ABS_POS) {
                spdlog::debug(("Setting command to run-to-abs-pos for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "run-to-abs-pos";
            } else if (command == MotorCommand::RUN_TO_REL_POS) {
                spdlog::debug(("Setting command to run-to-rel-pos for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "run-to-rel-pos";
            } else if (command == MotorCommand::RUN_TIMED) {
                spdlog::debug(("Setting command to run-timed for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "run-timed";
            } else if (command == MotorCommand::RESET) {
                spdlog::debug(("Setting command to reset for {}"), getBasePath().value_or("").c_str());
                *this->_file_command_path << "reset";
            } else {
                spdlog::error("MotorPort failed to set command for {}"), getBasePath().value_or("").c_str();
                return absl::InvalidArgumentError("MotorPort failed to set command: " + _path);
            }
            this->_file_command_path->flush();
            return absl::OkStatus();
        }

        absl::Status MotorPort::stop()
        {
            spdlog::trace("MotorPort::stop()");
            if (isEnabled().value_or(false)) {
                ABSL_RETURN_IF_ERROR(setCommand(MotorCommand::STOP));
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
            }
            return absl::OkStatus();
        }

        int MotorPort::getSpeed() 
        {
            spdlog::trace("MotorPort::getSpeed()");

            if (isEnabled().value_or(false)) {
                if (_file_speed_path->is_open()) {
                    if (!_file_speed_path->bad()) {
                        int speed;
                        *_file_speed_path >> speed;
                        spdlog::debug(("SPEED.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), speed);
                        return speed;
                    }
                }
            } 
            spdlog::error("MotorPort failed to get speed for {}"), getBasePath().value_or("").c_str();
            return -1;
        }

        int MotorPort::getPosition()
        {
            spdlog::trace("MotorPort::getPosition()");

            if (isEnabled().value_or(false)) {
                if (_file_position_path->is_open()) {
                    if (!_file_position_path->bad()) {
                        int position;
                        *_file_position_path >> position;

                        spdlog::debug(("POSITION.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), position);
                        return position;
                    }
                    spdlog::error("MotorPort failed to get position, File bad for {}"), getBasePath().value_or("").c_str();
                    throw std::runtime_error("MotorPort failed to get position, File bad");
                }
                spdlog::error("MotorPort failed to get position, File not open for {}"), getBasePath().value_or("").c_str();
                throw std::runtime_error("MotorPort failed to get position, File not open");
            }
            spdlog::error("MotorPort failed to get position, Port not enabled for {}"), getBasePath().value_or("").c_str();
            throw std::runtime_error("MotorPort failed to get position, Port not enabled");
        }

        std::vector<MotorState> MotorPort::getState()
        {
            spdlog::trace("MotorPort::getState()");

            // return std::async(std::launch::async, [this]() {
                std::vector<MotorState> states;
                if (isEnabled().value_or(false)) {
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
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::RUNNING));
                                states.push_back(MotorState::RUNNING);
                            } else if (token == "ramping") {
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::RAMPING));
                                states.push_back(MotorState::RAMPING);
                            } else if (token == "holding") {
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::HOLDING));
                                states.push_back(MotorState::HOLDING);
                            } else if (token == "overloaded") {
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::OVERLOADED));
                                states.push_back(MotorState::OVERLOADED);
                            } else if (token == "stalled") {
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::STALLED));
                                states.push_back(MotorState::STALLED);
                            } else if (token == "stopped") {
                                spdlog::debug(("STATE.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), static_cast<int>(MotorState::STOPPED));
                                states.push_back(MotorState::STOPPED);
                            } else {
                                spdlog::error("MotorPort failed to get state {} for {}"), token, getBasePath().value_or("").c_str();
                            }
                        }
                    } else {
                        spdlog::error("MotorPort failed to get state for {}"), getBasePath().value_or("").c_str();
                    }
                } else {
                    spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                    // _init_future.wait();
                    // return getState().get();
                } 
                for (auto s : states) {
                    spdlog::info(("STATE.GET: {} WITH_RESULT: {}"), getBasePath().value_or("").c_str(), static_cast<int>(s));
                }
                return states;
            // });
        }

        int MotorPort::getCountPerRotation()
        {
            spdlog::trace("MotorPort::getCountPerRotation()");

            // return std::async(std::launch::async, [this]() {
                if (isEnabled().value_or(false)) {
                    if (_file_count_per_rotation_path->is_open()) {
                        int count_per_rotation;
                        *_file_count_per_rotation_path >> count_per_rotation;
                        spdlog::info(("COUNT_PER_ROTATION.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), count_per_rotation);
                        return count_per_rotation;
                    } else {
                        spdlog::error("MotorPort failed to get count_per_rotation for {}"), getBasePath().value_or("").c_str();
                    }
                } else {
                    spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
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
                    if (isEnabled().value_or(false)) {
                        if (_file_max_speed_path->is_open()) {
                            int max_speed;
                            *_file_max_speed_path >> max_speed;
                            spdlog::info(("MAX_SPEED.GET: {} WITH_RESULT: %d"), getBasePath().value_or("").c_str(), max_speed);
                            return max_speed;
                        } else {
                            spdlog::error("MotorPort failed to get max_speed for {}"), getBasePath().value_or("").c_str();
                        }
                    } else {
                        spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                    }
                    return -1;
                // });
        }

        absl::StatusOr<DeviceType> MotorPort::getDeviceType()
        {
            spdlog::trace("MotorPort::getDeviceType()");

            absl::StatusOr<DeviceType> device_type = Port::getDeviceType();
            if(device_type.ok() && device_type.value() != DeviceType::MOTOR) {
                spdlog::error("MotorPort::getDeviceType() called on non-motor port");
                return absl::InvalidArgumentError("MotorPort::getDeviceType() called on non-motor port");
            }
            return DeviceType::MOTOR;
        }

        absl::Status MotorPort::moveToAbsPosition(int abs_position_sp)
        {
            spdlog::trace("MotorPort::moveToPosition()");

            if (isEnabled().value_or(false)) {
                absl::Status status = setPositionSp(abs_position_sp);
                if (!status.ok()) {
                    spdlog::error("MotorPort failed to move to position for {}"), getBasePath().value_or("").c_str();
                    return status;
                }

                status = setCommand(MotorCommand::RUN_TO_ABS_POS);
                if (!status.ok()) {
                    spdlog::error("MotorPort failed to move to position for {}"), getBasePath().value_or("").c_str();
                    return status;
                }
            } else {
                spdlog::error("Port is not enabled for {}"), getBasePath().value_or("").c_str();
                return absl::InvalidArgumentError("Port is not enabled for: " + _path);
            }
            return absl::OkStatus();
        }

        absl::Status MotorPort::reset()
        {
            spdlog::trace("MotorPort::reset()");

            absl::Status stopStatus = stop();
            if (!stopStatus.ok()) {
                spdlog::error("MotorPort failed to reset for {}"), getBasePath().value_or("").c_str();
            }

            absl::Status resetStatus = setCommand(MotorCommand::RESET);
            if (!resetStatus.ok()) {
                spdlog::error("MotorPort failed to reset for {}"), getBasePath().value_or("").c_str();
            } else {
                spdlog::debug(("MotorPort reset for {}"), getBasePath().value_or("").c_str());
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
                absl::Status initStatus = init();
                if (!initStatus.ok()) {
                    spdlog::error("MotorPort failed to reset for {}"), getBasePath().value_or("").c_str();
                    return initStatus;
                }

                _position = getPosition();
                return absl::OkStatus();
            } else {
                return absl::InternalError("MotorPort failed to reset, path does not exist");
            }
        }

        absl::Status MotorPort::init()
        {
            // return std::async(std::launch::async, [this]() {
                spdlog::trace("MotorPort::init()");

                // absl::call_once(_init_flag, &MotorPort::init, this);

                absl::StatusOr<bool> enabled = isEnabled();
                absl::StatusOr<path_port_t> base_path = getBasePath();
                absl::StatusOr<path_address_t> address_path = getAddressPath();
                absl::StatusOr<path_command_t> command_path = getCommandPath();
                absl::StatusOr<path_speed_t> speed_path = getSpeedPath();
                absl::StatusOr<path_speed_t> speed_sp_path = getSpeedSpPath();
                absl::StatusOr<path_position_t> position_path = getPositionPath();
                absl::StatusOr<path_position_sp_t> position_sp_path = getPositionSpPath();
                absl::StatusOr<path_duty_cycle_t> duty_cycle_path = getDutyCyclePath();
                absl::StatusOr<path_state_t> state_path = getStatePath();
                absl::StatusOr<path_polarity_t> polarity_path = getPolarityPath();
                absl::StatusOr<path_stop_action_t> stop_action_path = getStopActionPath();
                absl::StatusOr<path_count_per_rotation_t> count_per_rotation_path = getCountPerRotationPath();

                spdlog::debug(("MotorPort::init() for {}"), getBasePath().value_or("").c_str());
                
                if (!enabled.ok()) { 
                    spdlog::error("MotorPort failed to initialize, port is not enabled");
                    return absl::InternalError("MotorPort failed to initialize, port is not enabled");
                }
                if (!base_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, base path is not valid");
                    return base_path.status();
                }
                if (!address_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, address path is not valid");
                    return address_path.status();
                }
                if (!command_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, command path is not valid");
                    return command_path.status();
                }
                if (!speed_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, speed path is not valid");
                    return speed_path.status();
                }
                if (!speed_sp_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, speed_sp path is not valid");
                    return speed_sp_path.status();
                }
                if (!position_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, position path is not valid");
                    return position_path.status();
                }
                if (!position_sp_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, position_sp path is not valid");
                    return position_sp_path.status();
                }
                if (!duty_cycle_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle path is not valid");
                    return duty_cycle_path.status();
                }
                if (!state_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, state path is not valid");
                    return state_path.status();
                }
                if (!polarity_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, polarity path is not valid");
                    return polarity_path.status();
                }
                if (!stop_action_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, stop_action path is not valid");
                    return stop_action_path.status();
                }
                if (!count_per_rotation_path.ok()) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation path is not valid");
                    return count_per_rotation_path.status();
                }

                spdlog::debug("MotorPort::init() paths are valid");

                if (!std::filesystem::exists(base_path.value())) {
                    spdlog::error("MotorPort failed to initialize, base path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, base path does not exist");
                }
                if (!std::filesystem::exists(address_path.value())) {
                    spdlog::error("MotorPort failed to initialize, address path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, address path does not exist");
                }
                if (!std::filesystem::exists(command_path.value())) {
                    spdlog::error("MotorPort failed to initialize, command path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, command path does not exist");
                }
                if (!std::filesystem::exists(speed_path.value())) {
                    spdlog::error("MotorPort failed to initialize, speed path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, speed path does not exist");
                }
                if (!std::filesystem::exists(speed_sp_path.value())) {
                    spdlog::error("MotorPort failed to initialize, speed_sp path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, speed_sp path does not exist");
                }
                if (!std::filesystem::exists(position_path.value())) {
                    spdlog::error("MotorPort failed to initialize, position path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, position path does not exist");
                }
                if (!std::filesystem::exists(position_sp_path.value())) {
                    spdlog::error("MotorPort failed to initialize, position_sp path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, position_sp path does not exist");
                }
                if (!std::filesystem::exists(duty_cycle_path.value())) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, duty_cycle path does not exist");
                }
                if (!std::filesystem::exists(state_path.value())) {
                    spdlog::error("MotorPort failed to initialize, state path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, state path does not exist");
                }
                if (!std::filesystem::exists(polarity_path.value())) {
                    spdlog::error("MotorPort failed to initialize, polarity path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, polarity path does not exist");
                }
                if (!std::filesystem::exists(stop_action_path.value())) {
                    spdlog::error("MotorPort failed to initialize, stop_action path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, stop_action path does not exist");
                }
                if (!std::filesystem::exists(count_per_rotation_path.value())) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation path does not exist");
                    return absl::InternalError("MotorPort failed to initialize, count_per_rotation path does not exist");
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
                    return absl::InternalError("MotorPort failed to initialize, command file is not open");
                }
                if (!_file_speed_path->is_open() || _file_speed_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, speed file is not open");
                    return absl::InternalError("MotorPort failed to initialize, speed file is not open");
                }
                if (!_file_speed_sp_path->is_open() || _file_speed_sp_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, speed_sp file is not open");
                    return absl::InternalError("MotorPort failed to initialize, speed_sp file is not open");
                }
                if (!_file_position_path->is_open() || _file_position_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, position file is not open");
                    return absl::InternalError("MotorPort failed to initialize, position file is not open");
                }
                if (!_file_position_sp_path->is_open() || _file_position_sp_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, position_sp file is not open");
                    return absl::InternalError("MotorPort failed to initialize, position_sp file is not open");
                }
                if (!_file_duty_cycle_path->is_open() || _file_duty_cycle_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, duty_cycle file is not open");
                    return absl::InternalError("MotorPort failed to initialize, duty_cycle file is not open");
                }
                if (!_file_state_path->is_open() || _file_state_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, state file is not open");
                    return absl::InternalError("MotorPort failed to initialize, state file is not open");
                }
                if (!_file_polarity_path->is_open() || _file_polarity_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, polarity file is not open");
                    return absl::InternalError("MotorPort failed to initialize, polarity file is not open");
                }
                if (!_file_stop_action_path->is_open() || _file_stop_action_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, stop_action file is not open");
                    return absl::InternalError("MotorPort failed to initialize, stop_action file is not open");
                }
                if (!_file_count_per_rotation_path->is_open() || _file_count_per_rotation_path->bad()) {
                    spdlog::error("MotorPort failed to initialize, count_per_rotation file is not open");
                    return absl::InternalError("MotorPort failed to initialize, count_per_rotation file is not open");
                }

                spdlog::debug("MotorPort::init() file readers opened");

                _position = getPosition();

                return absl::OkStatus();
            // }).get();
        }
    }
}