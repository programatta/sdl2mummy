#include "timer.hpp"

Timer::Timer(int fps):MIN_FRAME_TIME(1000/fps)
{
    mFPSTime = SDL_GetTicks();
    iFPS=0;
    iNumOfFPS=0;

    mDeltaTime = 0.05f; // a 20 FPS.
}

float Timer::GetDeltaTime()
{
    return mDeltaTime;
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
    Uint32 currentTicks = SDL_GetTicks();
    if(currentTicks - 1000 >= mFPSTime)
    {
        mFPSTime = currentTicks;
        iNumOfFPS = iFPS;
        iFPS = 0;
    }
    ++iFPS;

    if(currentTicks - mFrameTime < MIN_FRAME_TIME)
        SDL_Delay(MIN_FRAME_TIME - (currentTicks - mFrameTime));

    mDeltaTime = (currentTicks - mFrameTime)*0.001;
    // Limit the time delta to 0.05 seconds (about 20FPS).
    if(mDeltaTime > 0.05f)
        mDeltaTime = 0.05f;
}
