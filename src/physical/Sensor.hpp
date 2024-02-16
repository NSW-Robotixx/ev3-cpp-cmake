#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <physical/portManager/port/Port.hpp>

namespace finder
{
    namespace physical
    {
        class Sensor {
            public:
                Sensor();
                ~Sensor();
                void start();
                void stop();
                void read();
            
            private:
                bool started;
                finder::physical::Port _sensor;
        };
    } // namespace physical
    
} // namespace finder

#endif // SENSOR_HPP