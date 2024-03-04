#include <linux/fb.h>
#include <sys/mman.h>
#include <stdint.h>
#include <memory>


#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

namespace physical::display
{
  enum DisplayColors {
      DISPLAY_BLACK = 0x11111111,
      DISPLAY_DARK = 0x78787878,
      DISPLAY_LIGHT = 0xb4b4b4b4,
      DISPLAY_WHITE = 0xffffffff,
      // If the display gets colors
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

  class Screen
  {
  protected:
      int fbfd;
      std::unique_ptr<uint32_t> *fbp;
      size_t screensize = 0;

      unsigned int width;
      unsigned int height;
  public:
      Screen();
      ~Screen();
  };
} // namespace physical::display

#endif