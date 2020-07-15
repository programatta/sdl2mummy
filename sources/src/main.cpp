#include <SDL.h>
#include "game.hpp"

#if ANDROID
int SDL_main(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
    #if ANDROID
    Game game("DemoSDL02", 608, 512, true);
    #else
    Game game("DemoSDL02", 608, 512, false);
    #endif
    int status = game.Run();
    return status;
}
