#ifndef __EV3_CONF_HPP__
#define __EV3_CONF_HPP__

    #include <stdint-gcc.h>

    // general settings
    constexpr bool EV3_THROW_ON_ERROR = true;

    // map the physical ports to the internal ports
    typedef char DevicePort;
    constexpr char EV3_PORT_INPUT_1  = '1';
    constexpr char EV3_PORT_INPUT_2  = '2';
    constexpr char EV3_PORT_INPUT_3  = '3';
    constexpr char EV3_PORT_INPUT_4  = '4';
    constexpr char EV3_PORT_OUTPUT_A = 'A';
    constexpr char EV3_PORT_OUTPUT_B = 'B';
    constexpr char EV3_PORT_OUTPUT_C = 'C';
    constexpr char EV3_PORT_OUTPUT_D = 'D';

    constexpr char EV3_MOTOR_COUNT = 4;
    constexpr char EV3_SENSOR_COUNT = 4;

    constexpr char EV3_PORT_GEARBOX_SHIFT = EV3_PORT_OUTPUT_D;
    
    constexpr uint_fast16_t EV3_GEARBOX_GEAR_POS_1  = 0;
    constexpr uint_fast16_t EV3_GEARBOX_GEAR_POS_2  = 90;
    constexpr uint_fast16_t EV3_GEARBOX_GEAR_POS_3  = 180;
    constexpr uint_fast16_t EV3_GEARBOX_GEAR_POS_4  = 270;

    constexpr uint_fast8_t EV3_GEARBOX_GEAR_POS_TOLERANCE = 5;

    constexpr uint_fast16_t EV3_GEAR_BLOCKED_TIMEOUT_MS = 1000;

    // define the tolerance for the gyro sensor
    constexpr uint_fast8_t EV3_GYRO_TURN_TOLERANCE = 3;

    // define the offsets of the sensors on the robot
    constexpr uint_fast8_t EV3_SENSOR_COLOR_RIGHT_OFFSET_X = 0;                  // to be implemented
    constexpr uint_fast8_t EV3_SENSOR_COLOR_RIGHT_OFFSET_Y = 0;         // to be implemented

    constexpr uint_fast8_t EV3_SENSOR_COLOR_LEFT_OFFSET_X = 0;          // to be implemented
    constexpr uint_fast8_t EV3_SENSOR_COLOR_LEFT_OFFSET_Y = 0;          // to be implemented

    constexpr uint_fast8_t EV3_SENSOR_COLOR_FRONT_OFFSET_X = 0;         // to be implemented
    constexpr uint_fast8_t EV3_SENSOR_COLOR_FRONT_OFFSET_Y = 0;         // to be implemented

    // define the trigger values for the color sensors
    constexpr uint_fast8_t EV3_COLOR_SENSOR_TRIGGER = 42;

    // use the rgb mode for the color sensors
    constexpr uint_fast8_t EV3_COLOR_SENSOR_USE_RGB_MODE = 0;           // to be implemented

    // define the trigger values for the color sensors with rgb mode
    constexpr uint_fast8_t EV3_COLOR_SENSOR_TRIGGER_RED = 42;           // to be implemented
    constexpr uint_fast8_t EV3_COLOR_SENSOR_TRIGGER_GREEN = 42;         // to be implemented
    constexpr uint_fast8_t EV3_COLOR_SENSOR_TRIGGER_BLUE = 42;          // to be implemented

    // define the offsets of the motors on the robot
    constexpr uint_fast8_t EV3_MOTOR_WHEELBASE = 0;                     // to be implemented

    // define the field parameters
    constexpr uint_fast16_t EV3_FIELD_WIDTH = 2000;
    constexpr uint_fast16_t EV3_FIELD_HEIGHT = 1000;

    // set the file format of the destinations file
    #define EV3_DESTINATIONS_FILE_FORMAT_YAML 0
    #if     EV3_DESTINATIONS_FILE_FORMAT_YAML
        // define the destinations.yaml path
        #define EV3_DESTINATIONS_FILE_ABS_PATH  1
        #if     EV3_DESTINATIONS_FILE_ABS_PATH
            constexpr const char* EV3_DESTINATIONS_FILE_PATH = "/home/dennis/src/niklas/ev3-cpp-cmake/lib/system/src/destinations.yaml";
        #else 
            constexpr const char* EV3_DESTINATIONS_FILE_PATH = "./destinations.yaml";
        #endif
    #else
        // define the destinations.txt path
        #define EV3_DESTINATIONS_FILE_PATH "./destinations.list"
    #endif



    // disable tcp requests
    #define EV3_COMPUTE_NO_TCP  1
    #if     EV3_COMPUTE_NO_TCP
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 0
    #else
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 1
            // define the port for the tcp communication of the compute module
            constexpr uint_fast16_t EV3_COMPUTE_PORT = 34001;
        // local or external compute module
        #define EV3_COMPUTE_LOCAL 1
        #if     EV3_COMPUTE_LOCAL
            // define the ip address of the local compute module
            constexpr const char* EV3_COMPUTE_IP = "localhost";
        #else
            // define the ip address of the external compute module
            constexpr const char* EV3_COMPUTE_IP "localhost";
        #endif
    #endif

    // enable display of the robot
    #define EV3_DISPLAY_ENABLED 1
    #if     EV3_DISPLAY_ENABLED
        // use color display
        #define EV3_DISPLAY_COLOR 1

        // draw text with freetype
        #define EV3_DISPLAY_USE_FREETYPE 0
        #if     EV3_DISPLAY_USE_FREETYPE
            #define EV3_ENABLE_USE_BITMAPS 0

            // define the path to the font file
            constexpr const char* EV3_DISPLAY_FONT_PATH = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf";
        #else
            #define EV3_ENABLE_USE_BITMAPS 1
        #endif
    #endif

    // define the webserver settings
    #define EV3_WEBSERVER_ENABLED 1
    #if     EV3_WEBSERVER_ENABLED
        // define the port for the webserver
        constexpr uint_fast16_t EV3_WEBSERVER_PORT = 8080;
        constexpr const char* EV3_WEBSERVER_HOST = "localhost";
    #endif 
#endif