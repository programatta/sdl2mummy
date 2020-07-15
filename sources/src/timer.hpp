#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>

class Timer
{
    public:
        Timer(int fps);
        float GetDeltaTime();
        int GetCurrentFPS();
        void Start();
        void End();
    private:
        const int MIN_FRAME_TIME;
        Uint32 mFPSTime;
        Uint32 mFrameTime;
        int iFPS, iNumOfFPS;
        float mDeltaTime;
};

#endif  //TIMER_HPP
