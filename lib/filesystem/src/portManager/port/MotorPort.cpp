#include "MotorPort.hpp"

namespace finder
{
    namespace physical
    {
        log4cplus::Logger MotorPort::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main.MotorPort"));

        /*
        MotorPort::MotorPort() : Port()
        {
            init();
        }
        */

        MotorPort::MotorPort(std::string port_name) : Port(port_name)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::MotorPort(std::string port_name)");
            init();
        }

        MotorPort::MotorPort(std::shared_ptr<Port> port) : Port(port)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::MotorPort(std::shared_ptr<Port> port)");
            init();
        }

        path_speed_t MotorPort::getSpeedSpPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getSpeedSpPath()");

            if (isEnabled()) {
                return getBasePath() + "/speed_sp";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_position_t MotorPort::getPositionPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getPositionPath()");

            if (isEnabled()) {
                return getBasePath() + "/position";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_speed_t MotorPort::getSpeedPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getSpeedPath()");
            if (isEnabled()) {
                return getBasePath() + "/speed";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_position_sp_t MotorPort::getPositionSpPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getPositionSpPath()");
            if (isEnabled()) {
                return getBasePath() + "/position_sp";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_duty_cycle_t MotorPort::getDutyCyclePath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getDutyCyclePath()");
            if (isEnabled()) {
                return getBasePath() + "/duty_cycle_sp";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_state_t MotorPort::getStatePath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getStatePath()");
            if (isEnabled()) {
                return getBasePath() + "/state";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_polarity_t MotorPort::getPolarityPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getPolarityPath()");
            if (isEnabled()) {
                return getBasePath() + "/polarity";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_stop_action_t MotorPort::getStopActionPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getStopActionPath()");
            if (isEnabled()) {
                return getBasePath() + "/stop_action";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        path_count_per_rotation_t MotorPort::getCountPerRotationPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getCountPerRotationPath()");
            if (isEnabled()) {
                return getBasePath() + "/count_per_rot";
            } else {
                LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
                return "";
            }
        }

        
        path_max_speed_t MotorPort::getMaxSpeedPath()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getMaxSpeedPath()");
            if (isEnabled()) {
                return _path + "/max_speed";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return "";
        }

        void MotorPort::setSpeed(int speed)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setSpeed()");

            if (isEnabled()) {
                if (_file_speed_sp_path->is_open()) {
                    *_file_speed_sp_path << speed;
                    _file_speed_sp_path->flush();
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("failed to write to speed file for %s"), getBasePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // setSpeed(speed);
            }
        }

        void MotorPort::setPositionSp(int position_sp)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setPositionSp()");

            if (isEnabled()) {
                if (_file_position_sp_path->is_open()) {
                    *_file_position_sp_path << position_sp;
                    _file_position_sp_path->flush();
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("failed to write to position_sp file for %s"), getBasePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // setPositionSp(position_sp);
            }
        }

        void MotorPort::setDutyCycle(int duty_cycle)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setDutyCycle()");

            if (isEnabled()) {
                if (_file_duty_cycle_path->is_open()) {
                    *_file_duty_cycle_path << duty_cycle;
                    _file_duty_cycle_path->flush();
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("failed to write to duty_cycle file for %s"), getBasePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // setDutyCycle(duty_cycle);
            }
        }

        void MotorPort::setPolarity(MotorPolarity polarity)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setPolarity()");

            if (isEnabled()) {
                if (_file_polarity_path->is_open()) {
                    if (polarity == MotorPolarity::NORMAL) {
                        *_file_polarity_path << "normal";
                    } else if (polarity == MotorPolarity::INVERSED) {
                        *_file_polarity_path << "inversed";
                    } else {
                        LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to write to files for %s"), getBasePath().c_str());
                        throw std::runtime_error("MotorPort failed to set polarity");
                    }
                    _file_polarity_path->flush();
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to set polarity for %s"), getBasePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // setPolarity(polarity);
            }
        }

        void MotorPort::setStopAction(MotorStopAction stop_action)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setStopAction()");

            if (isEnabled()) {
                if (_file_stop_action_path->is_open()) {
                    if (stop_action == MotorStopAction::COAST) {
                        *_file_stop_action_path << "coast";
                    } else if (stop_action == MotorStopAction::BRAKE) {
                        *_file_stop_action_path << "brake";
                    } else if (stop_action == MotorStopAction::HOLD) {
                        *_file_stop_action_path << "hold";
                    } else {
                        LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to write to files for %s"), getBasePath().c_str());
                        throw std::runtime_error("MotorPort failed to set stop_action");
                    }
                    _file_stop_action_path->flush();
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to set stop_action for %s"), getBasePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // setStopAction(stop_action);
            }
        }

        void MotorPort::setCommand(MotorCommand command)
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::setCommand()");
            if (command == MotorCommand::STOP) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to stop for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RUN_DIRECT) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to run-direct for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RUN_FOREVER) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to run-forever for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RUN_TO_ABS_POS) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to run-to-abs-pos for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RUN_TO_REL_POS) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to run-to-rel-pos for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RUN_TIMED) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to run-timed for %s"), getBasePath().c_str());
            } else if (command == MotorCommand::RESET) {
                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Setting command to reset for %s"), getBasePath().c_str());
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to set command for %s"), getBasePath().c_str());
                throw std::runtime_error("MotorPort failed to set command");
            }
        }

        void MotorPort::stop()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::stop()");
            if (isEnabled()) {
                setCommand(MotorCommand::STOP);
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                // _init_future.wait();
                // stop();
            }
        }

        int MotorPort::getSpeed() 
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getSpeed()");

            if (isEnabled()) {
                if (_file_speed_path->is_open()) {
                    if (!_file_speed_path->bad()) {
                        int speed;
                        *_file_speed_path >> speed;
                        LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("SPEED.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), speed);
                        return speed;
                    }
                }
            } 
            LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get speed for %s"), getBasePath().c_str());
            return -1;
        }

        int MotorPort::getPosition()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getPosition()");

            if (isEnabled()) {
                if (_file_position_path->is_open()) {
                    if (!_file_position_path->bad()) {
                        int position;
                        *_file_position_path >> position;

                        LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("POSITION.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), position);
                        return position;
                    }
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get position, File bad for %s"), getBasePath().c_str());
                    throw std::runtime_error("MotorPort failed to get position, File bad");
                }
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get position, File not open for %s"), getBasePath().c_str());
                throw std::runtime_error("MotorPort failed to get position, File not open");
            }
            LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get position, Port not enabled for %s"), getBasePath().c_str());
            throw std::runtime_error("MotorPort failed to get position, Port not enabled");
        }

        std::vector<MotorState> MotorPort::getState()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getState()");

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
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::RUNNING));
                                states.push_back(MotorState::RUNNING);
                            } else if (token == "ramping") {
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::RAMPING));
                                states.push_back(MotorState::RAMPING);
                            } else if (token == "holding") {
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::HOLDING));
                                states.push_back(MotorState::HOLDING);
                            } else if (token == "overloaded") {
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::OVERLOADED));
                                states.push_back(MotorState::OVERLOADED);
                            } else if (token == "stalled") {
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::STALLED));
                                states.push_back(MotorState::STALLED);
                            } else if (token == "stopped") {
                                LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(MotorState::STOPPED));
                                states.push_back(MotorState::STOPPED);
                            } else {
                                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get state %s for %s"), token, getBasePath().c_str());
                            }
                        }
                    } else {
                        LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get state for %s"), getBasePath().c_str());
                    }
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                    // _init_future.wait();
                    // return getState().get();
                } 
                for (auto s : states) {
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("STATE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), static_cast<int>(s));
                }
                return states;
            // });
        }

        int MotorPort::getCountPerRotation()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getCountPerRotation()");

            // return std::async(std::launch::async, [this]() {
                if (isEnabled()) {
                    if (_file_count_per_rotation_path->is_open()) {
                        int count_per_rotation;
                        *_file_count_per_rotation_path >> count_per_rotation;
                        LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("COUNT_PER_ROTATION.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), count_per_rotation);
                        return count_per_rotation;
                    } else {
                        LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get count_per_rotation for %s"), getBasePath().c_str());
                    }
                } else {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                    // _init_future.wait();
                    // return getCountPerRotation().get();
                }
                return -1;
            // });
        }

        int MotorPort::getMaxSpeed()
        {
            LOG4CPLUS_TRACE(_logger, "MotorPort::getMaxSpeed()");

                // return std::async(std::launch::async, [this]() {
                    if (isEnabled()) {
                        if (_file_max_speed_path->is_open()) {
                            int max_speed;
                            *_file_max_speed_path >> max_speed;
                            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("MAX_SPEED.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), max_speed);
                            return max_speed;
                        } else {
                            LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("MotorPort failed to get max_speed for %s"), getBasePath().c_str());
                        }
                    } else {
                        LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                        // _init_future.wait();
                        // return getMaxSpeed().get();
                    }
                    return -1;
                // });
        }

        DeviceType MotorPort::getDeviceType()
        {
            if(Port::getDeviceType() != DeviceType::MOTOR) {
                LOG4CPLUS_ERROR(_logger, "MotorPort::getDeviceType() called on non-motor port");
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
                        LOG4CPLUS_DEBUG(_logger, "MotorPort initialized");
                    } else {
                        LOG4CPLUS_ERROR(_logger, "MotorPort failed to initialize");
                    }
                } else {
                    LOG4CPLUS_ERROR(_logger, "MotorPort failed to initialize, port does not exist");
                }
            // });
        }
    }
}