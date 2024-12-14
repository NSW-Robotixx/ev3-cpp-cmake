#if !defined(_MSC_VER)

#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "../EV3_conf.hpp"
#include <memory>
#include <string>
#include <atomic>
#include <vector>
#include <map>
#include <iomanip>
#include "Screen.hpp"
#include "bitmaps/Bitmaps.hpp"

#if EV3_DISPLAY_USE_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

namespace finder::physical::display
{

    /// @brief Display colors that can be used
    enum DisplayColors {
        DISPLAY_BLACK = 0x00000000,
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
        DISPLAY_PINK = 0xffc0cb00,
        DISPLAY_TRAFFIC_RED = 0xC1121C00,
        DISPLAY_TRAFFIC_GREEN = 0x00A74A00,
    };


    /// @brief Class that represents a window on the display
    class Window : public Screen
    {
        friend class WindowManager;

        public:
            /// @brief Constructor
            /// @param name Name of the window
            /// @param width Width of the window
            /// @param height Height of the window
            /// @param x X start position of the window on the display
            /// @param y Y start position of the window on the display
            Window(std::string name, int width, int height, int x, int y);
            ~Window();

            /// @brief Get the width of the window
            /// @return Width of the window
            int getWidth();

            /// @brief Get the height of the window
            /// @return Height of the window
            int getHeight();

            /// @brief Get the name of the window
            /// @return Name of the window
            std::string getName();

            /// @brief Set the name of the window
            /// @param name Name of the window
            void setName(std::string name);

            /// @brief Update the content of the window        
            virtual void update() = 0;

            /// @brief Draw a Line on the window
            /// @param x0 X0 Coordinate
            /// @param y0 Y0 Coordinate
            /// @param x1 X1 Coordinate
            /// @param y1 Y1 Coordinate
            /// @param color Color of the line
            /// @return 0 if successful, -1 if not
            int drawLine(int x0, int y0, int x1, int y1, DisplayColors color);

            /// @brief Draw a Vertical Line on the window
            /// @param x0 X0 Coordinate
            /// @param y0 Y0 Coordinate
            /// @param y1 Y1 Coordinate
            /// @param color Color of the line
            /// @return 0 if successful, -1 if not
            int drawVerticalLine(int x0, int y0, int y1, DisplayColors color);

            /// @brief Draw a Horizontal Line on the window
            /// @param x0 X0 Coordinate
            /// @param y0 Y0 Coordinate
            /// @param x1 X1 Coordinate
            /// @param color Color of the line
            /// @return 0 if successful, -1 if not
            int drawHorizontalLine(int x0, int y0, int x1, DisplayColors color);

            /// @brief Draw a Rectangle on the window
            /// @param x0 Lower left X Coordinate
            /// @param y0 Lower left Y Coordinate
            /// @param x1 Upper right X Coordinate
            /// @param y1 Upper right Y Coordinate
            /// @param color Color of the rectangle
            /// @return 0 if successful, -1 if not
            int drawRectangle(int x0, int y0, int x1, int y1, DisplayColors color);

            /// @brief Draw a rotated Rectangle on the window
            /// @param x0 X0 Coordinate
            /// @param y0 Y0 Coordinate
            /// @param x1 X1 Coordinate
            /// @param y1 Y1 Coordinate
            /// @param x2 X2 Coordinate
            /// @param y2 Y2 Coordinate
            /// @param x3 X3 Coordinate
            /// @param y3 Y3 Coordinate
            /// @param color Color of the rectangle
            /// @return 0 if successful, -1 if not
            int drawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, DisplayColors color);

            /// @brief Draw a Circle on the window
            /// @param x0 X Coordinate
            /// @param y0 Y Coordinate
            /// @param radius Radius of the circle
            /// @param color Color of the circle
            /// @return 0 if successful, -1 if not
            int drawCircle(int x0, int y0, int radius, DisplayColors color);

            /// @brief Draw a triangle on the window
            /// @param x0 X0 Coordinate
            /// @param y0 Y0 Coordinate
            /// @param x1 X1 Coordinate
            /// @param y1 Y1 Coordinate
            /// @param x2 X2 Coordinate
            /// @param y2 Y2 Coordinate
            /// @param color Color of the triangle
            /// @return 0 if successful, -1 if not
            int drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, DisplayColors color);

            /// @brief Draw Text on the window
            /// @param x Offset X Coordinate
            /// @param y Offset Y Coordinate
            /// @param text Text to draw 
            /// @param color Color of the text
            /// @return 0 if successful, -1 if not
            int drawText(int x, int y, std::string text, DisplayColors color);

#ifndef EV3_DISPLAY_USE_BITMAPS
            /// @brief Draw Bitmap on the window
            /// @param x Offset X Coordinate
            /// @param y Offset Y Coordinate
            /// @param bitmap Bitmap to draw
            int drawBitmap(int x, int y, std::shared_ptr<bitmaps::ImageFormat> bitmap);
#endif

            /// @brief Fill the window with a color
            /// @param color Color to fill the window with
            /// @return 0 if successful, -1 if not
            int fill(DisplayColors color);

            /// @brief Get the X start position of the window on the display
            /// @return X start position of the window
            int getStartX() { return x; };

            /// @brief Get the Y start position of the window on the display
            /// @return Y start position of the window
            int getStartY() { return y; };
            
        private:
            std::string name;
            int width;
            int height;
            int x;
            int y;

            std::atomic_bool _dirty;
            std::atomic_bool _button_left_pressed;
            std::atomic_bool _button_right_pressed;
            std::atomic_bool _button_up_pressed;
            std::atomic_bool _button_down_pressed;
            std::atomic_bool _button_enter_pressed;
            std::atomic_bool _button_back_pressed;
            
            std::atomic_bool _button_left_released;
            std::atomic_bool _button_right_released;
            std::atomic_bool _button_up_released;
            std::atomic_bool _button_down_released;
            std::atomic_bool _button_enter_released;
            std::atomic_bool _button_back_released;

            #if EV3_DISPLAY_USE_FREETYPE
            FT_Library ft;
            FT_Face face;
            #endif
    };
} // namespace finder::physical::display

#endif // __WINDOW_HPP__

#endif // !defined(_MSC_VER)