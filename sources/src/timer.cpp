#include "timer.hpp"

Timer::Timer(int fps):MIN_FRAME_TIME(1000/fps)
{
    mFPSTime = SDL_GetTicks();
    iFPS=0;
    iNumOfFPS=0;
}

float Timer::GetDeltaTime()
{
    if(iNumOfFPS > 0)
        return mDeltaTime/iNumOfFPS;
    else
    {
        return mDeltaTime/(1000/MIN_FRAME_TIME);
    }
}

int Timer::GetCurrentFPS()
{
    return iNumOfFPS;
}

void Timer::Start()
{
    mFrameTime = SDL_GetTicks();
}

void Timer::End()
{
    if(SDL_GetTicks() - 1000 >= mFPSTime)
    {
        mFPSTime = SDL_GetTicks();
        iNumOfFPS = iFPS;
        iFPS = 0;
    }
    ++iFPS;

    mDeltaTime = (SDL_GetTicks () - mFrameTime)*0.001*iNumOfFPS;
    if(SDL_GetTicks() - mFrameTime < MIN_FRAME_TIME)
        SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks () - mFrameTime));
}
