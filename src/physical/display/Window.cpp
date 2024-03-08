#include <physical/display/Window.hpp>

namespace finder::physical::display
{
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

    int Window::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, DisplayColors color)
    {
        this->drawLine(x0, y0, x1, y1, color);
        this->drawLine(x1, y1, x2, y2, color);
        this->drawLine(x2, y2, x0, y0, color);
        return 0;
    }

    int Window::drawText(int x, int y, std::string text, DisplayColors color)
    {
        for (int i = 0; i < text.size(); i++)
        {
            int ascii = text[i] - 32;

            if (ascii < 0 || ascii >= font8x8_basic.size())
                continue;

            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 8; k++)
                {
                    if ((font8x8_basic[ascii][j] >> k) & 0x1)
                    {
                        this->drawPixel(x + k, y + j, color);
                    }
                }
            }
            x += 8;
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
