#if !defined(_MSC_VER)


#include <linux/fb.h>
#include <sys/mman.h>
#include <stdint.h>
#include <memory>

#include <spdlog/spdlog.h>


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

namespace finder::physical::display
{
  /// @brief Screen class, controlling the display of the EV3
  class Screen
  {
  protected:
      Screen();
      ~Screen();

      /// @brief Width of the screen
      unsigned int width;

      /// @brief Height of the screen
      unsigned int height;

      /// @brief Draw a pixel on the screen
      /// @param x X coordinate of the pixel
      /// @param y Y coordinate of the pixel
      /// @param color Color of the pixel
      void drawPixel(int x, int y, uint32_t color);

      /// @brief Clear the screen
      void clear();

      /// @brief Fill the screen with a color
      /// @param color Color to fill the screen with
      void fillScreen(uint32_t color);

      /// @brief Framebuffer file descriptor
      int fbfd;

      /// @brief File descriptor of the framebuffer
      uint32_t *fbp;

      /// @brief Screen size
      size_t screensize = 0;
  public:


  };
} // namespace finder::physical::display

#endif

#endif // !defined(_MSC_VER)
