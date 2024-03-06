#include <physical/display/Window.hpp>

namespace finder::physical::display
{
    std::vector<std::vector<int>> Window::font8x8_basic = {
        // letter a
        {0b00000000, 
         0b00000000, 
         0b00000000, 
         0b00000000, 
         0b01111100, 
         0b10000010, 
         0b10000010, 
         0b01111101},
        // letter b
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000010, 0b10000010, 0b01111100},
        // letter c
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000000, 0b10000000, 0b01111100},
        // letter d
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000000, 0b10000000, 0b01111100},
        // letter e
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000010, 0b10000010, 0b10000000},
        // letter f
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000010, 0b10000010, 0b10000000},
        // letter g
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000000, 0b10000010, 0b01111100},
        // letter h
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter i
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b00100000, 0b00100000, 0b01111100},
        // letter j
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b00100000, 0b00100000, 0b01111100},
        // letter k
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10010000, 0b10100000, 0b11000000},
        // letter l
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b11111100},
        // letter m
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b11010110, 0b10101010, 0b10000010},
        // letter n
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b11000010, 0b10100010, 0b10010010},
        // letter o
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000010, 0b10000010, 0b01111100},
        // letter p
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000010, 0b10000010, 0b01111100},
        // letter q
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000010, 0b10000010, 0b01111100},
        // letter r
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b10000010, 0b10000010, 0b01111100},
        // letter s
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000000, 0b10000000, 0b01111100},
        // letter t
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111100, 0b00100000, 0b00100000, 0b01111100},
        // letter u
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter v
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter w
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter x
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter y
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // letter z
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // number 0
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10010010, 0b10101010, 0b01111100},
        // number 1
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b01100000, 0b00100000, 0b01110000},
        // number 2
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000010, 0b00111100, 0b11111110},
        // number 3
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b00000100, 0b00000100, 0b01111100},
        // number 4
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10000010, 0b10000010, 0b01111100},
        // number 5
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111110, 0b10000000, 0b10000000, 0b01111100},
        // number 6
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000000, 0b10000000, 0b01111100},
        // number 7
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111110, 0b00000100, 0b00001000, 0b00010000},
        // number 8
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000010, 0b10000010, 0b01111100},
        // number 9
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b10000010, 0b10000010, 0b01111100},
        // exclamation mark
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00100000, 0b00100000, 0b00100000},
    };
    ::finder::console::Logger Window::_logger = ::finder::console::Logger();

    Window::Window(std::string name, int width, int height, int x, int y)
    {
        this->name = name;
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
        this->pixels.resize(width * height);
    }

    Window::~Window()
    {
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

    std::vector<uint32_t>& Window::getPixels()
    {
        return this->pixels;
    }

    void Window::update()
    {
        
    }

    int Window::drawPixel(int x, int y, DisplayColors color)
    {
        if (x < 0 || x >= this->width || y < 0 || y >= this->height)
            return -1;

        this->pixels[y * this->width + x] = color;
        return 0;
    }

    int Window::drawLine(int x0, int y0, int x1, int y1, DisplayColors color)
    {
        // out of bounds check
        if (x0 < 0 || x0 >= this->width || y0 < 0 || y0 >= this->height)
            return -1;

        if (x1 < 0 || x1 >= this->width || y1 < 0 || y1 >= this->height)
            return -1;

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

    int Window::drawText(int x, int y, std::string text, DisplayColors color)
    {
        for (std::string::size_type i = 0; i < text.size(); i++)
        {
            char c = text[i];
            if (c < 32 || c > 126)
                continue;

            for (int j = 0; j < 8; j++)
            {
                int bit = font8x8_basic[c - 32][j];
                for (int k = 0; k < 8; k++)
                {
                    if (bit & (1 << k))
                    {
                        this->drawPixel(x + (i * 8) + k, y + j, color);
                    }
                }
            }
        }

        return 0;
    }

    int Window::fill(DisplayColors color)
    {
        std::fill(this->pixels.begin(), this->pixels.end(), color);

        _logger.debug("Filled window with color: " + std::to_string(color));
        return 0;
    }
} // namespace finder::physical::display
