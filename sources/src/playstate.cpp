#include "playstate.hpp"
#include <SDL_image.h>
#include <sstream>
#include "trace.hpp"
#include "utils.hpp"

PlayState::PlayState(SDL_Renderer *renderer)
{
    //Player.
    SDL_Surface *playerSurf = nullptr;
    playerSurf = IMG_Load(Utils::ResourcePath("player.png").c_str());
    if(!playerSurf)
    {
        std::stringstream msg;
        msg << "IMG_Load:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        //return 1;
    }
    mPlayerTex = SDL_CreateTextureFromSurface(renderer, playerSurf);
    SDL_FreeSurface(playerSurf);
    if(!mPlayerTex)
    {
        std::stringstream msg;
        msg << "SDL_CreateTextureFromSurface:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        //return 1;
    }

    //Map
    SDL_Surface *mapSurf = nullptr;
    mapSurf = IMG_Load(Utils::ResourcePath("walls.png").c_str());
    if(!mapSurf)
    {
        std::stringstream msg;
        msg << "IMG_Load:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        //return 1;
    }
    mMapTex = SDL_CreateTextureFromSurface(renderer, mapSurf);
    SDL_FreeSurface(mapSurf);
    if(!mMapTex)
    {
        std::stringstream msg;
        msg << "SDL_CreateTextureFromSurface:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        //return 1;
    }
}

PlayState::~PlayState()
{
    SDL_DestroyTexture( mPlayerTex );
    SDL_DestroyTexture( mMapTex );
    mPlayerTex = nullptr;
    mMapTex = nullptr;
}

void PlayState::ProcessEvents()
{

}

void PlayState::Update(float deltaTime)
{

}

void PlayState::Render(SDL_Renderer *renderer)
{
    float scaleFactorX=1,scaleFactorY=1;
    SDL_RenderGetScale(renderer, &scaleFactorX, &scaleFactorY);
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    
    std::stringstream msg;
    msg << "Render - el w:" << w << " - el sfX:" << scaleFactorX << " - el sfY:" << scaleFactorY;
    Trace::Info("SDL",msg.str());
    
    int offsetToCenter = ((w / scaleFactorY)-(32*19))/2;

    //Player.
    SDL_Rect orig = {0,0,32,32};
    SDL_Rect dest = {455-16,256-32,32,32};

    DrawMap(renderer, mMapTex, offsetToCenter);
    SDL_RenderCopy(renderer, mPlayerTex, &orig, &dest);
}


/*===========================================================================*/
/*                                Private Section                            */
/*===========================================================================*/
void PlayState::DrawMap(SDL_Renderer* render, SDL_Texture* texture, int offsetToCenter)
{
    std::stringstream msg;
    msg << "OffsetToCenter:" << offsetToCenter;
    Trace::Info("SDL",msg.str());
    int map[16][19] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    };
    SDL_Rect orig = {0,0,32,32};

    for(int r=0; r<16; r++) {
        for (int c = 0; c < 19; c++) {
            if (map[r][c] == 1) {
                SDL_Rect dest = {32 * c + offsetToCenter, 32 * r, 32, 32};
                SDL_RenderCopy(render, texture, &orig, &dest);
            }
        }
    }
}