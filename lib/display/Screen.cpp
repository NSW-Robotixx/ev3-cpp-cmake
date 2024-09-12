#if !defined(_MSC_VER)


#include "Screen.hpp"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <linux/fb.h>
    



namespace finder::physical::display
{
::finder::log::Logger Screen::_logger = ::finder::log::Logger();

Screen::Screen()
{
    fbfd = open("/dev/fb0", O_RDWR);
    
    if(fbfd == -1) {
        perror("Error: cannot open framebuffer device");
    }
    // printf("The framebuffer device was opened successfully.\n");
    /* Get fixed screen information */
    struct fb_var_screeninfo finfo;
    struct fb_var_screeninfo vinfo;

    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
    }

    /* Get variable screen information */
    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
    }

    /* Figure out the size of the screen in bytes */
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    // printf("Screen size is %ld\n", static_cast<long int>(screensize));
    // printf("Vinfo.bpp = %d\n", vinfo.bits_per_pixel);
    // printf("Yres = %d\n", vinfo.yres);
    // printf("Xres = %d\n", vinfo.xres);

    /* Map the device to memory */
    fbp = static_cast<uint32_t*>(
        mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0)
    );
    if(fbp == MAP_FAILED) {
        perror("Error: failed to map framebuffer device to memory");
        throw std::runtime_error("Error: failed to map framebuffer device to memory");
    }
    width = vinfo.xres;
    height = vinfo.yres;
    // printf("The framebuffer device was mapped to memory successfully.\n");

}

Screen::~Screen()
{
    munmap(fbp, screensize);
    close(fbfd);
}

    void Screen::drawPixel(int x, int y, uint32_t color)
    {
        if(x < 0 || x > width || y < 0 || y > height) {
            _logger.warn("Tried to draw pixel outside of screen at x: " + std::to_string(x) + " y: " + std::to_string(y));
            return;
        }

        if (fbp[y * width + x] == color) {
            return;
        }
        fbp[y * width + x] = color;
    }


    void Screen::clear()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                drawPixel(x, y, 0xffffffff);
            }
        }
    }
    void Screen::fillScreen(uint32_t color)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                drawPixel(x, y, color);
            }
        }
    }
} // namespace finder::physical::display

#endif // !defined(_MSC_VER)