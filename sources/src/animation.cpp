#include "animation.hpp"

Animation::Animation():mFrameDT(0),mFrame(0)
{
}

Animation::~Animation()
{
    mAnimations.clear();
}

void Animation::AddFrame(const SDL_Rect& rect, float duration)
{
    FrameData frameData {rect.x, rect.y, rect.w, rect.h, duration};
    mAnimations.push_back(frameData);
}

void Animation::UpdateFrame(float deltaTime)
{
    mFrameDT += deltaTime;
    if( mFrameDT>=mAnimations[mFrame].duration )
    {
        mFrame = (mFrame+1)%4;
        mFrameDT = 0.0f;
    }
}

const FrameData& Animation::GetFrame() const
{
    return mAnimations[mFrame];
}

const FrameData& Animation::GetFrame(int frame) const
{
    return mAnimations[frame];
}
