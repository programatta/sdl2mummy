#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <SDL.h>
#include "spritesheet.hpp"
#include "player.hpp"

class PlayState
{
    public:
        PlayState(SDL_Renderer *renderer);
        ~PlayState();

        void ProcessEvents(const SDL_Event& event);
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);
    
    private:
        void DrawMap(SDL_Renderer* render, SDL_Texture* texture, int offsetToCenter);
        
        SpriteSheet mSpriteSheet;
        SDL_Texture *mSpriteTex;
        Player mPlayer;
};

#endif  //PLAY_STATE_HPP
