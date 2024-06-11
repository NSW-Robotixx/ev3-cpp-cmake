#ifndef __LIB_SYSTEM_DISPLAY_GRAPHICALINTERFACE_HPP__
#define __LIB_SYSTEM_DISPLAY_GRAPHICALINTERFACE_HPP__


//#include <lvgl.h>

class GraphicalInterface
{
    public:
        GraphicalInterface();
        static void start();
        static void stop();
    private:
        static void loop();
};


#endif // __LIB_SYSTEM_DISPLAY_GRAPHICALINTERFACE_HPP__