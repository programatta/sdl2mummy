#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <SDL.h>
#include "spritesheet.hpp"
#include "stage.hpp"
#include "player.hpp"

class PlayState
{
    public:
        PlayState(SDL_Renderer *renderer);
        ~PlayState();

        void ProcessEvents(SDL_Event &event);
        void ProcessEvents();
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);
    
    private:        
        SpriteSheet mSpriteSheet;
        SDL_Texture *mSpriteTex;
        Stage mStage;
        Player mPlayer;

        //TODO: esto va tener que ir a un input manager o algo asi.
        float tX0;
        float tY0;
        float tX;
        float tY;
        bool isMoving;
        int playerDir;
        bool starMovement;
};

#endif  //PLAY_STATE_HPP
