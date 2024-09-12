#ifndef __EV3_CONF_HPP__
#define __EV3_CONF_HPP__

    // define the tolerance for the gyro sensor
    #define EV3_GYRO_TURN_TOLERANCE 3

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
    #define EV3_DESTINATIONS_FILE_FORMAT_YAML 0
    #if     EV3_DESTINATIONS_FILE_FORMAT_YAML
        // define the destinations.yaml path
        #define EV3_DESTINATIONS_FILE_ABS_PATH  1
        #if     EV3_DESTINATIONS_FILE_ABS_PATH
            #define EV3_DESTINATIONS_FILE_PATH "/home/dennis/src/niklas/ev3-cpp-cmake/lib/system/src/destinations.yaml"
        #else 
            #define EV3_DESTINATIONS_FILE_PATH "./destinations.yaml"
        #endif
    #else
        // define the destinations.txt path
        #define EV3_DESTINATIONS_FILE_PATH "./destinations.list"
    #endif



    // disable tcp requests
    #define EV3_COMPUTE_NO_TCP 1
    #if     EV3_COMPUTE_NO_TCP
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 0
    #else
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 1
            // define the port for the tcp communication of the compute module
            #define EV3_COMPUTE_PORT 34001
        // local or external compute module
        #define EV3_COMPUTE_LOCAL 1
        #if     EV3_COMPUTE_LOCAL
            // define the ip address of the local compute module
            #define EV3_COMPUTE_IP "localhost"
        #else
            // define the ip address of the external compute module
            #define EV3_COMPUTE_IP "localhost"
        #endif

    // enable display of the robot
    #define EV3_DISPLAY_ENABLED 1
    #if     EV3_DISPLAY_ENABLED
        // use color display
        #define EV3_DISPLAY_COLOR 1
        
    #endif
#endif
#endif