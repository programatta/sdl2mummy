#include "playstate.hpp"
#include <SDL_image.h>
#include <sstream>
#include "trace.hpp"
#include "utils.hpp"

PlayState::PlayState(SDL_Renderer *renderer):mPlayer(mStage)
{
    //Cargamos los sprites.
    mSpriteSheet.Load(renderer,"sprites");

    //Situamos al player en el centro de la ventana.
    float scaleFactorX=1,scaleFactorY=1;
    SDL_RenderGetScale(renderer, &scaleFactorX, &scaleFactorY);
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    float posX = w/scaleFactorY/2 - 16;
    float posY = h/scaleFactorY/2 - 32;

    mPlayer.SetPosition(posX, posY);
    mPlayer.SetSpriteSheet(mSpriteSheet);

    mStage.SetSpriteSheet(mSpriteSheet);
}

PlayState::~PlayState()
{
}

void PlayState::ProcessEvents()
{
    const Uint8 *keys = (SDL_GetKeyboardState(nullptr));
    if( keys == nullptr)
        return;

    if( keys[SDL_SCANCODE_DOWN])
        mPlayer.Move(PlayerDir::DOWN);
    else if(keys[SDL_SCANCODE_UP])
        mPlayer.Move(PlayerDir::UP);
    else if(keys[SDL_SCANCODE_LEFT])
        mPlayer.Move(PlayerDir::LEFT);
    else if(keys[SDL_SCANCODE_RIGHT])
        mPlayer.Move(PlayerDir::RIGHT);
}


void PlayState::Update(float deltaTime)
{
    mStage.Update(deltaTime);
    mPlayer.Update(deltaTime);
}

void PlayState::Render(SDL_Renderer *renderer)
{
    //Stage.
    mStage.Render(renderer);

    //Player.
    mPlayer.Render(renderer);
}
