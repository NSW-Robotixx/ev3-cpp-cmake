#include "RobotMovement.hpp"

namespace finder::robot
{
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorLeft;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorRight;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorShift;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorTool;

    int RobotMovement::_speed = 50;
    int RobotMovement::_dutyCycle = 50;

    finder::console::Logger RobotMovement::_logger;

    unsigned long int RobotMovement::_movementID = 0;
    unsigned long int RobotMovement::_movementIDAhead = 0;
    std::mutex RobotMovement::_movementIDMutex;

    std::queue<std::future<void>> RobotMovement::_movementFuture;
    std::mutex RobotMovement::_movementFutureMutex;

    std::queue<std::shared_ptr<std::condition_variable>> RobotMovement::_movementQueueCV;
    std::queue<std::shared_ptr<std::mutex>> RobotMovement::_movementQueueCVMutex;


    RobotMovement::RobotMovement()
    {

        _logger.debug("Initializing RobotMovement");
        _logger.debug(_motorLeft->getBasePath());
        _logger.debug(_motorRight->getBasePath());
        _logger.debug(_motorShift->getBasePath());
        _logger.debug(_motorTool->getBasePath());
        _logger.debug("RobotMovement initialized");
    }

    RobotMovement::~RobotMovement()
    {
        stop();
    }

    void RobotMovement::move(MovementType type, int distance = 0, int speed = MovementAction::getDefaultSpeed(), float arcRatio = 1)
    {
        _movementQueueCV.push(std::shared_ptr<std::condition_variable>( new std::condition_variable{}));
        _movementQueueCVMutex.push(std::shared_ptr<std::mutex>( new std::mutex{}));

        _movementFuture.push(std::async(std::launch::async, [&](){

            // check if this thread is the only one in the queue, if not wait for signal to continue
            std::size_t _movementFutureSize;
            {
                std::lock_guard<std::mutex> lock(_movementFutureMutex);
                _movementFutureSize = _movementFuture.size();
            }

            if (_movementFutureSize != 1)
            {
                std::unique_lock<std::mutex> lk(*_movementQueueCVMutex.back());
                _movementQueueCV.back()->wait(lk, []{ return false; });
            }


            awaitMotorReady();
            
            MovementAction(type, distance, speed, arcRatio);
        }));
    }


    void RobotMovement::stop()
    {
        _movementQueueCV.push(std::shared_ptr<std::condition_variable>( new std::condition_variable{}));
        _movementQueueCVMutex.push(std::shared_ptr<std::mutex>( new std::mutex{}));

        _movementFuture.push(std::async(std::launch::async, [&](){

            // check if this thread is the only one in the queue, if not wait for signal to continue
            std::size_t _movementFutureSize;
            {
                std::lock_guard<std::mutex> lock(_movementFutureMutex);
                _movementFutureSize = _movementFuture.size();
            }

            if (_movementFutureSize != 1)
            {
                std::unique_lock<std::mutex> lk(*_movementQueueCVMutex.back());
                _movementQueueCV.back()->wait(lk, []{ return false; });
            }


            awaitMotorReady();
            
            _motorLeft->setCommand(physical::MotorCommand::STOP);
            _motorRight->setCommand(physical::MotorCommand::STOP);
        }));
    }

    void RobotMovement::setSpeed(int speed)
    {
        _speed = speed;
    }

    void RobotMovement::setDutyCycle(int dutyCycle)
    {
        _dutyCycle = dutyCycle;
    }

    void RobotMovement::awaitMotorReady()
    {
        std::vector<::finder::physical::MotorState> _leftState = _motorLeft->getState();
        std::vector<::finder::physical::MotorState> _rightState = _motorRight->getState();

        while (
            std::find(_rightState.begin(), _rightState.end(), ::finder::physical::MotorState::HOLDING) == _rightState.end() ||
            std::find(_leftState.begin(), _leftState.end(), ::finder::physical::MotorState::HOLDING) == _leftState.end()
        ) {
            _leftState = _motorLeft->getState();
            _rightState = _motorRight->getState();
        }
    }

    void RobotMovement::processQueueChanges()
    {
        if (_movementFuture.size() == 1) {
            _movementQueueCV.front()->notify_all();
        }
    }

} // namespace finder::robot