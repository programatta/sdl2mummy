#include "game.hpp"

#include <sstream>
#include "trace.hpp"
#include "utils.hpp"
#include "timer.hpp"
#include "playstate.hpp"

Game::Game(const std::string &title, int width, int height, bool isFullScreen)
{
    bool isOk = true;
    SDL_Rect screenRect = { 0, 0, width, height };

    Trace::Info("SDL","SDL_main starting...");

    mHasSDL = SDL_FALSE;
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::stringstream msg;
        msg << "SDL_Init:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        isOk = false;
    }

    if(!isOk) return;

    if(isFullScreen)
    {
        //Get device display mode
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            screenRect.w = displayMode.w;
            screenRect.h = displayMode.h;
        }
    }
    #if ANDROID
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    #endif

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED | SDL_WINDOW_OPENGL;
    if(isFullScreen)
        flags = flags | SDL_WINDOW_FULLSCREEN;

    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenRect.w, screenRect.h, flags);
    if(mWindow == nullptr)
    {
        std::stringstream msg;
        msg << "SDL_CreateWindow:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        isOk = false;
    }

    if(!isOk) return;

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mRenderer == nullptr)
    {
        std::stringstream msg;
        msg << "SDL_CreateRenderer:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
        isOk = false;
    }

    if(!isOk) return;

    SDL_RenderSetLogicalSize(mRenderer, width, height);
    
    mHasSDL = SDL_TRUE;
    mPlayState = new PlayState(mRenderer);
    Trace::Info("SDL","SDL_main started ok!");
}

Game::~Game()
{
    Trace::Info("SDL","SDL_main releasing resources...");

    delete mPlayState;

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();

    mPlayState = nullptr;
    mRenderer = nullptr;
    mWindow = nullptr;
    mHasSDL = SDL_FALSE;
    Trace::Info("SDL","SDL_main released resources... ok!");
}

int Game::Run()
{
    if(mHasSDL)
        mIsRunning = true;
    
    Timer timer(60);
    timer.Start();
    while(mIsRunning)
    {
        //timer.Start();

        ProcessEvents();
        Update( timer.GetDeltaTime() );
        Render();
        
        timer.End();
    }

    return 0;
}


/*===========================================================================*/
/*                                Private Section                            */
/*===========================================================================*/
void Game::ProcessEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            mIsRunning = false;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    mIsRunning = false;
                    break;
            }
        }
    }
    
    #if ANDROID
    mPlayState->ProcessEvents(event);
    #else
    mPlayState->ProcessEvents();
    #endif
}

void Game::Update(float deltaTime)
{
    mPlayState->Update(deltaTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(mRenderer);
    mPlayState->Render(mRenderer);
    SDL_RenderPresent(mRenderer);
}
