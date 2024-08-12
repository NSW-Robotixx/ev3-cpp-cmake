#ifndef __EV3_CONF_HPP__
#define __EV3_CONF_HPP__
    // all values are given in mm

    // define the offsets of the sensors on the robot
    #define EV3_SENSOR_COLOR_RIGHT_OFFSET_X 0                           // to be implemented
    #define EV3_SENSOR_COLOR_RIGHT_OFFSET_Y 0                           // to be implemented

    #define EV3_SENSOR_COLOR_LEFT_OFFSET_X 0                            // to be implemented
    #define EV3_SENSOR_COLOR_LEFT_OFFSET_Y 0                            // to be implemented

    #define EV3_SENSOR_COLOR_FRONT_OFFSET_X 0                           // to be implemented
    #define EV3_SENSOR_COLOR_FRONT_OFFSET_Y 0                           // to be implemented

    // define the trigger values for the color sensors
    #define EV3_COLOR_SENSOR_TRIGGER 42

    // use the rgb mode for the color sensors
    #define EV3_COLOR_SENSOR_USE_RGB_MODE 0                             // to be implemented

    // define the trigger values for the color sensors with rgb mode
    #define EV3_COLOR_SENSOR_TRIGGER_RED 42                             // to be implemented
    #define EV3_COLOR_SENSOR_TRIGGER_GREEN 42                           // to be implemented
    #define EV3_COLOR_SENSOR_TRIGGER_BLUE 42                            // to be implemented

    // define the offsets of the motors on the robot
    #define EV3_MOTOR_WHEELBASE 0                                       // to be implemented

    // define the field parameters
    #define EV3_FIELD_WIDTH 2000
    #define EV3_FIELD_HEIGHT 1000

    // set the file format of the destinations file
    #define EV3_DESTINATIONS_FILE_FORMAT_YAML 1
    #if     EV3_DESTINATIONS_FILE_FORMAT_YAML
        // define the destinations.yaml path
        #define EV3_DESTINATIONS_FILE_PATH "./destinations.yaml"
    #else
        // define the destinations.txt path
        #define EV3_DESTINATIONS_FILE_PATH "./destinations.list"
    #endif

    // define the port for the tcp communication of the compute module
    #define EV3_COMPUTE_PORT 34001
#endif