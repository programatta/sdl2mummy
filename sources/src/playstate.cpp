#include "playstate.hpp"
#include <SDL_image.h>
#include <sstream>
#include "trace.hpp"
#include "utils.hpp"

PlayState::PlayState(SDL_Renderer *renderer)
{
    //Cargamos los sprites.
    mSpriteSheet.Load(renderer,"sprites");
    mPlayer.SetSpriteSheet(mSpriteSheet);
}

PlayState::~PlayState()
{
}

void PlayState::ProcessEvents(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN) // || event.type == SDL_FINGERDOWN)
    {
        Trace::Info("SDL", "PlayState::ProcessEvents - tecla pulsada");
        switch( event.key.keysym.sym )
        {
            case SDLK_DOWN:
                mPlayer.Move(PlayerDir::DOWN);
                break;
            case SDLK_UP:
                mPlayer.Move(PlayerDir::UP);
                break;
            case SDLK_LEFT:
                mPlayer.Move(PlayerDir::LEFT);
                break;
            case SDLK_RIGHT:
                mPlayer.Move(PlayerDir::RIGHT);
                break;
        }
    }
}

void PlayState::Update(float deltaTime)
{
    mPlayer.Update(deltaTime);
}

void PlayState::Render(SDL_Renderer *renderer)
{
    float scaleFactorX=1,scaleFactorY=1;
    SDL_RenderGetScale(renderer, &scaleFactorX, &scaleFactorY);
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
        
    int offsetToCenter = ((w / scaleFactorY)-(32*19))/2;

    DrawMap(renderer, mSpriteSheet.GetTexture(), offsetToCenter);

    //Player.
    mPlayer.Render(renderer);

    // int px = w/scaleFactorY/2;
    // int py = h/scaleFactorY/2;
    // SDL_Rect orig = {0,0,32,32};
    // SDL_Rect dest = {px-16,py-32,32,32};

    // orig = mSpriteSheet.GetFrameByName("player-1.png");
    // DrawMap(renderer, mSpriteSheet.GetTexture(), offsetToCenter);
    // SDL_RenderCopy(renderer, mSpriteSheet.GetTexture(), &orig, &dest);
}


/*===========================================================================*/
/*                                Private Section                            */
/*===========================================================================*/
void PlayState::DrawMap(SDL_Renderer* render, SDL_Texture* texture, int offsetToCenter)
{
    int map[16][19] = {
            {1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    };

    for(int r=0; r<16; r++) 
    {
        for(int c = 0; c < 19; c++)
        {
            SDL_Rect orig;
            if(map[r][c] == 1)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-36.png");
            }
            else if(map[r][c] == 2)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-57.png");
            }
            else if(map[r][c] == 4)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-54.png");
            }
            else
            {
                orig = mSpriteSheet.GetFrameByName("desert-3.png");
            }

            SDL_Rect dest = {32 * c + offsetToCenter, 32 * r, 32, 32};
            SDL_RenderCopy(render, texture, &orig, &dest);
        }
    }
}
