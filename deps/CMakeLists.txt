set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

# SDL
# https://github.com/libsdl-org/SDL
set( SDL_LIBC ON CACHE BOOL "" FORCE )
set( SDL_TEST OFF CACHE BOOL "" FORCE )
add_subdirectory( sdl2 )
target_link_libraries( Main SDL2-static )

# lvgl-win
# https://
add_subdirectory( lvgl-win )
# target_link_libraries( Main lvgl )