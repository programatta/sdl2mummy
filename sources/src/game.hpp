#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <string>
#include "playstate.hpp"

class Game
{
    public:
        Game(const std::string &title, int width, int height, bool fullscreen=false);
        ~Game();
        int Run();

    private:
        void ProcessEvents();
        void Update(float deltaTime);
        void Render();

        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        SDL_bool mHasSDL;
        bool mIsRunning;

        //TODO: será una maquina de estados.
        PlayState *mPlayState;
};

#endif  //GAME_HPP
