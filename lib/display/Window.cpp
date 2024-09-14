#if !defined(_MSC_VER)

#include "Window.hpp"

namespace finder::physical::display
{
    ::finder::log::Logger Window::_logger = ::finder::log::Logger();

    Window::Window(std::string name, int width, int height, int x, int y) : Screen()
    {
        this->name = name;
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
        this->fill(DISPLAY_WHITE);
    }

    Window::~Window()
    {
        _logger.debug("Window destroyed: " + this->name);
        FT_Done_FreeType(ft);
    }

    int Window::getWidth()
    {
        return this->width;
    }

    int Window::getHeight()
    {
        return this->height;
    }

    std::string Window::getName()
    {
        return this->name;
    }

    void Window::setName(std::string name)
    {
        this->name = name;
    }

    int Window::drawLine(int x0, int y0, int x1, int y1, DisplayColors color)
    {
        // out of bounds check
        if (x0 < 0 || x0 >= this->width || y0 < 0 || y0 >= this->height)
            return -1;

        // check if line is vertical
        if (x0 == x1)
        {
            return this->drawVerticalLine(x0, y0, y1, color);
        }

        // check if line is horizontal
        if (y0 == y1)
        {
            return this->drawHorizontalLine(x0, y0, x1, color);
        }

        // Bresenham's line algorithm
        int dx = x1 - x0;
        int dy = y1 - y0;
        int stepx, stepy;

        if (dy < 0)
        {
            dy = -dy;
            stepy = -1;
        }
        else
        {
            stepy = 1;
        }

        if (dx < 0)
        {
            dx = -dx;
            stepx = -1;
        }
        else
        {
            stepx = 1;
        }

        dy <<= 1;
        dx <<= 1;

        this->drawPixel(x0, y0, color);

        if (dx > dy)
        {
            int fraction = dy - (dx >> 1);
            while (x0 != x1)
            {
                if (fraction >= 0)
                {
                    y0 += stepy;
                    fraction -= dx;
                }
                x0 += stepx;
                fraction += dy;
                this->drawPixel(x0, y0, color);
            }
        }
        else
        {
            int fraction = dx - (dy >> 1);
            while (y0 != y1)
            {
                if (fraction >= 0)
                {
                    x0 += stepx;
                    fraction -= dy;
                }
                y0 += stepy;
                fraction += dx;
                this->drawPixel(x0, y0, color);
            }
        }

        return 0;
    }

    int Window::drawVerticalLine(int x0, int y0, int y1, DisplayColors color)
    {
                // out of bounds check
        if (x0 < 0 || x0 >= this->width || y0 < 0 || y0 >= this->height)
            return -1;

        if (y1 < 0 || y1 >= this->height)
            return -1;

        for (int i = y0; i <= y1; i++)
        {
            this->drawPixel(x0, i, color);
        }

        return 0;
    }

    int Window::drawHorizontalLine(int x0, int y0, int x1, DisplayColors color)
    {
        // out of bounds check
        if (x0 < 0 || x0 >= this->width || y0 < 0 || y0 >= this->height)
            return -1;

        if (x1 < 0 || x1 >= this->width)
            return -1;

        for (int i = x0; i <= x1; i++)
        {
            this->drawPixel(i, y0, color);
        }

        return 0;
    }

    int Window::drawRectangle(int x0, int y0, int x1, int y1, DisplayColors color)
    {
        // out of bounds check
        if (x0 < 0 || x0 >= this->width || y0 < 0 || y0 >= this->height)
            return -1;

        if (x1 < 0 || x1 >= this->width || y1 < 0 || y1 >= this->height)
            return -1;

        this->drawLine(x0, y0, x1, y0, color);
        this->drawLine(x0, y0, x0, y1, color);
        this->drawLine(x1, y0, x1, y1, color);
        this->drawLine(x0, y1, x1, y1, color);

        std::cout << std::hex << color << std::endl;

        return 0;
    }

    int Window::drawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, DisplayColors color)
    {
        this->drawLine(x0, y0, x1, y1, color);
        this->drawLine(x1, y1, x2, y2, color);
        this->drawLine(x2, y2, x3, y3, color);
        this->drawLine(x3, y3, x0, y0, color);
        return 0;
    }

    int Window::drawCircle(int x0, int y0, int radius, DisplayColors color)
    {
        int x = radius;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            this->drawPixel(x0 + x, y0 + y, color);
            this->drawPixel(x0 + y, y0 + x, color);
            this->drawPixel(x0 - y, y0 + x, color);
            this->drawPixel(x0 - x, y0 + y, color);
            this->drawPixel(x0 - x, y0 - y, color);
            this->drawPixel(x0 - y, y0 - x, color);
            this->drawPixel(x0 + y, y0 - x, color);
            this->drawPixel(x0 + x, y0 - y, color);

            if (err <= 0)
            {
                y += 1;
                err += 2 * y + 1;
            }

            if (err > 0)
            {
                x -= 1;
                err -= 2 * x + 1;
            }
        }

        return 0;
    }

    int Window::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, DisplayColors color)
    {
        this->drawLine(x0, y0, x1, y1, color);
        this->drawLine(x1, y1, x2, y2, color);
        this->drawLine(x2, y2, x0, y0, color);
        return 0;
    }

    int Window::drawText(int x, int y, std::string text, DisplayColors color)
    {
        #if EV3_DISPLAY_USE_FREETYPE
        if (FT_Init_FreeType(&ft))
        {
            _logger.error("Could not init freetype library");
            return -1;
        }

        if (FT_New_Face(ft, EV3_DISPLAY_FONT_PATH, 0, &face))
        {
            _logger.error("Could not open font");
            return -1;
        }

        for (int i = 0; i < text.size(); i++)
        {
            if (FT_Set_Pixel_Sizes(face, 0, 6))
            {
                _logger.error("Could not set pixel size");
                return -1;
            }

            if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
            {
                _logger.error("Could not load character");
                return -1;
            }

            FT_GlyphSlot g = face->glyph;

            for (int j = 0; j < g->bitmap.rows; j++)
            {
                for (int k = 0; k < g->bitmap.width; k++)
                {
                    if (g->bitmap.buffer[j * g->bitmap.width + k] > 0)
                    {
                        this->drawPixel(x + k, y + j, color);
                    }
                }
            }

            x += g->bitmap.width;
        }

        #else
        unsigned int xpos = x;
        unsigned int ypos = y;
        for (int i = 0; i < text.size(); i++)
        {
            int ascii = static_cast<int>(text[i]) - 97;
            _logger.debug("Ascii version of character: " + std::to_string(ascii));

            if (ascii < 0 || ascii >= bitmaps::Keyboard::Keyboard_images.size()) 
            {
                _logger.warn("Character not found in font: " + std::to_string(text[i]) + " ascii: " + std::to_string(ascii));
                continue;
            }

            if (xpos + 8 >= this->width)
            {
                xpos = x;
                ypos += bitmaps::Keyboard::Keyboard_images[ascii]->height + 1;
            }

            _logger.debug("Drawing character: " + std::to_string(text[i]) + " at: " + std::to_string(xpos) + ", " + std::to_string(ypos));
            this->drawBitmap(xpos, ypos, bitmaps::Keyboard::Keyboard_images[ascii]);
            xpos += bitmaps::Keyboard::Keyboard_images[ascii]->width + 1;
        }
        return 0;
        #endif
    }

    int Window::drawBitmap(int x, int y, std::shared_ptr<bitmaps::ImageFormat> bitmap)
    {
        _logger.debug("Drawing bitmap at: " + std::to_string(x) + ", " + std::to_string(y));
        _logger.debug("Bitmap width: " + std::to_string(bitmap->width));
        _logger.debug("Bitmap height: " + std::to_string(bitmap->height));
        for (int i = 0; i < bitmap->height; i++)
        {
            for (int j = 0; j < bitmap->width; j++)
            {
                if ((bitmap->data[i] >> j) & 0x1)
                {
                    this->drawPixel(x + j, y + i, DISPLAY_BLACK);
                }
                else
                {
                    this->drawPixel(x + j, y + i, DISPLAY_WHITE);
                }
            }
        }
        return 0;
    }

    int Window::fill(DisplayColors color)
    {
        fillScreen(color);

        _logger.debug("Filled window with color: " + std::to_string(color));
        return 0;
    }
} // namespace finder::physical::display

#endif // !defined(__WINDOW_CPP__)