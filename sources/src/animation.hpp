#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include<vector>
#include<SDL.h>
#include "framedata.hpp"

class Animation
{
    public:
        explicit Animation();
        ~Animation();

        void AddFrame(const SDL_Rect& rect, float duration);
        void UpdateFrame(float deltaTime);
        const FrameData& GetFrame() const;
        const FrameData& GetFrame(int frame) const;

    private:
        std::vector<FrameData> mAnimations;
        float mFrameDT;
        int mFrame;
};

#endif  //ANIMATION_HPP
