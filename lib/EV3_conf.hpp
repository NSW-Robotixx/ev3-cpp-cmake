#ifndef __EV3_CONF_HPP__
#define __EV3_CONF_HPP__

    #include <math.h>

    // general settings
    constexpr bool EV3_THROW_ON_ERROR = true;
    
    constexpr const char* EV3_DEFAULT_PORT_BASE_PATH = "/sys/class/";

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

    // define the default speed of the motors
    constexpr unsigned int EV3_GEARBOX_SHIFT_SPEED = 500;
    constexpr unsigned int EV3_MOTOR_TOOL_SPEED = 500;
    constexpr unsigned int EV3_DRIVE_SPEED = 400;
    constexpr unsigned int EV3_TURN_SPEED = 20;
    
    // define the gear positions of the gearbox
    constexpr char EV3_PORT_GEARBOX_SHIFT = EV3_PORT_OUTPUT_D;
    constexpr unsigned int EV3_GEARBOX_GEAR_POS_1  = 0;
    constexpr unsigned int EV3_GEARBOX_GEAR_POS_2  = 90;
    constexpr unsigned int EV3_GEARBOX_GEAR_POS_3  = 180;
    constexpr unsigned int EV3_GEARBOX_GEAR_POS_4  = 270;


    // define the tolerance for the gearbox
    constexpr unsigned int EV3_GEARBOX_GEAR_POS_TOLERANCE = 5;

    // define the tolerance for the blocked gear
    constexpr unsigned int EV3_GEAR_BLOCKED_TOLERANCE = 5;

    // define the timeout for the blocked gear
    constexpr unsigned int EV3_GEAR_BLOCKED_TIMEOUT_MS = 1000;

    // define the tolerance for the gyro sensor
    constexpr unsigned int EV3_GYRO_TURN_TOLERANCE = 0;

    // define the timeout for the calibration of the gyro sensor
    constexpr unsigned int EV3_GYRO_CALIBRATION_TIMEOUT_MS = 1000;

    // define the offsets of the sensors on the robot
    constexpr unsigned int EV3_SENSOR_COLOR_RIGHT_OFFSET_X = 0;
    constexpr unsigned int EV3_SENSOR_COLOR_RIGHT_OFFSET_Y = 0; 

    constexpr unsigned int EV3_SENSOR_COLOR_LEFT_OFFSET_X = 0;  
    constexpr unsigned int EV3_SENSOR_COLOR_LEFT_OFFSET_Y = 0;  

    constexpr unsigned int EV3_SENSOR_COLOR_FRONT_OFFSET_X = 0; 
    constexpr unsigned int EV3_SENSOR_COLOR_FRONT_OFFSET_Y = 0; 

    // define the trigger values for the color sensors
    constexpr unsigned int EV3_COLOR_SENSOR_TRIGGER = 42;

    // use the rgb mode for the color sensors
    #define EV3_COLOR_SENSOR_USE_RGB_MODE 1           // to be implemented

    // define the backlog of the sensors for position estimation
    constexpr unsigned int EV3_COLOR_SENSOR_BACKLOG = 5;
    constexpr unsigned int EV3_GYRO_SENSOR_BACKLOG = 5;

    // define the trigger values for the color sensors with rgb mode
    constexpr unsigned int EV3_COLOR_SENSOR_TRIGGER_RED = 42;           // to be implemented
    constexpr unsigned int EV3_COLOR_SENSOR_TRIGGER_GREEN = 42;         // to be implemented
    constexpr unsigned int EV3_COLOR_SENSOR_TRIGGER_BLUE = 42;          // to be implemented

    constexpr const char* EV3_COLOR_SENSOR_IMAGE_PATH = "./color_sensor.svg";

    // define the offsets of the motors on the robot in mm
    constexpr unsigned int EV3_MOTOR_WHEELBASE = 140;                     // to be implemented

    // define the circumference of the turn circle of the robot
    constexpr unsigned int EV3_MOTOR_TURN_CIRCLE = M_PI * EV3_MOTOR_WHEELBASE;

    // define the wheel circumference of the robot
    constexpr double EV3_MOTOR_WHEEL_DIAMETER = 43;
    constexpr double EV3_MOTOR_WHEEL_CIRCUMFERENCE = M_PI * EV3_MOTOR_WHEEL_DIAMETER;

    // define the distance per degree of the motors
    constexpr double EV3_MOTOR_DISTANCE_PER_DEGREE = 360 / EV3_MOTOR_WHEEL_CIRCUMFERENCE;

    // define the position jump tolerance of the motors for the position estimation
    constexpr unsigned int EV3_POSITION_JUMP_TOLERANCE = 1000;

    // define the field parameters
    constexpr unsigned int EV3_FIELD_WIDTH = 2000;
    constexpr unsigned int EV3_FIELD_HEIGHT = 1000;

    // define the position of the robot on the field
    constexpr unsigned int EV3_ROBOT_POSITION_X = 70;
    constexpr unsigned int EV3_ROBOT_POSITION_Y = 160;

    // set the file format of the destinations file
    #define EV3_DESTINATIONS_FILE_FORMAT_YAML 1
    #if     EV3_DESTINATIONS_FILE_FORMAT_YAML
        // define the destinations.yaml path
        #define EV3_DESTINATIONS_FILE_ABS_PATH  0
        #if     EV3_DESTINATIONS_FILE_ABS_PATH
            constexpr const char* EV3_DESTINATIONS_FILE_PATH = "/home/robot/destinations.yaml";
        #else 
            constexpr const char* EV3_DESTINATIONS_FILE_PATH = "./destinations.yaml";
        #endif
    #else
        // define the destinations.txt path
        #define EV3_DESTINATIONS_FILE_PATH "./destinations.list"
    #endif

    // define the file format of the obstacles file
    #define EV3_OBSTACLES_FILE_FORMAT_YAML 1
    #if     EV3_OBSTACLES_FILE_FORMAT_YAML
        // define the obstacles.yaml path
        #define EV3_OBSTACLES_FILE_ABS_PATH  0
        #if     EV3_OBSTACLES_FILE_ABS_PATH
            constexpr const char* EV3_OBSTACLES_FILE_PATH = "/home/dennis/src/niklas/ev3-cpp-cmake/lib/system/src/obstacles.yaml";
        #else 
            constexpr const char* EV3_OBSTACLES_FILE_PATH = "./obstacles.yaml";
        #endif
    #else
        // define the obstacles.txt path
        #define EV3_OBSTACLES_FILE_PATH "./obstacles.yaml"
    #endif

    // disable tcp requests
    #define EV3_COMPUTE_NO_TCP  1
    #if     EV3_COMPUTE_NO_TCP
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 0
    #else
        #define EV3_COMPUTE_MODULE_TCP_ENABLED 1
            // define the port for the tcp communication of the compute module
            constexpr unsigned int EV3_COMPUTE_PORT = 34001;
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
        constexpr unsigned int EV3_WEBSERVER_PORT = 8080;
        constexpr const char* EV3_WEBSERVER_HOST = "localhost";
    #endif 
#endif