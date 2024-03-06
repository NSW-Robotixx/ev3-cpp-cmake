#include "Screen.hpp"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
    



namespace finder::physical::display
{
::finder::console::Logger Screen::_logger = ::finder::console::Logger();

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
        exit(4);
    }
    width = screensize / vinfo.yres;
    height = screensize / vinfo.xres;
    // printf("The framebuffer device was mapped to memory successfully.\n");

}

Screen::~Screen()
{
    munmap(fbp, screensize);
    close(fbfd);
}

    void Screen::drawPixel(int x, int y, uint32_t color)
    {
        _logger.debug("Drawing pixel in Screen at x: " + std::to_string(x) + " y: " + std::to_string(y));
        if(x < 0 || x > width || y < 0 || y > height) {
            return;
        }
        fbp[x + y * width] = color;

        _logger.debug("Pixel drawn in Screen at x: " + std::to_string(x) + " y: " + std::to_string(y));
    }
} // namespace finder::physical::display