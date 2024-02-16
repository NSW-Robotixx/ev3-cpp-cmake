#include <physical/portManager/port/Port.hpp>
#ifndef MOTOR_HPP
#define MOTOR_HPP



namespace finder
{
    namespace device
    {
        class Motor {
            public:
                Motor();
                ~Motor();
                
            private:
                finder::physical::Port motor_;
        };
    } // namespace device
    
} // namespace finder

#endif // MOTOR_HPP