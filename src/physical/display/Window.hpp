#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <console/Logger.hpp>
#include <physical/display/bitmaps/Bitmaps.hpp>

namespace finder::physical::display
{
    enum DisplayColors {
        DISPLAY_BLACK = 0x11111111,
        DISPLAY_DARK = 0x78787878,
        DISPLAY_LIGHT = 0xb4b4b4b4,
        DISPLAY_WHITE = 0xffffffff,
        // If the display supports colors
        DISPLAY_RED = 0xff000000,
        DISPLAY_GREEN = 0x00ff0000,
        DISPLAY_BLUE = 0x0000ff00,
        DISPLAY_YELLOW = 0xffff0000,
        DISPLAY_CYAN = 0x00ffff00,
        DISPLAY_MAGENTA = 0xff00ff00,
        DISPLAY_ORANGE = 0xffa50000,
        DISPLAY_PURPLE = 0x80008000,
        DISPLAY_BROWN = 0xa52a2a00,
        DISPLAY_PINK = 0xffc0cb00
    };


    class Window
    {
        public:
            Window(std::string name, int width, int height, int x, int y);
            ~Window();

            int getWidth();
            int getHeight();
            std::string getName();

            void setName(std::string name);
            
            std::vector<uint32_t>& getPixels();

            void update();

            int drawPixel(int x, int y, DisplayColors color);
            int drawLine(int x0, int y0, int x1, int y1, DisplayColors color);
            int drawRectangle(int x0, int y0, int x1, int y1, DisplayColors color);
            int drawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, DisplayColors color);
            int drawCircle(int x0, int y0, int radius, DisplayColors color);
            int drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, DisplayColors color);
            int drawText(int x, int y, std::string text, DisplayColors color);
            int drawMonochromeBitmap(int x, int y, std::shared_ptr<bitmaps::ImageFormat> bitmap);
            int fill(DisplayColors color);
            
            int getStartX() { return x; };
            int getStartY() { return y; };
            
        private:
            static ::finder::console::Logger _logger;
            std::string name;
            int width;
            int height;
            int x;
            int y;
            std::vector<uint32_t> pixels;
    };
} // namespace finder::physical::display

#endif // __WINDOW_HPP__