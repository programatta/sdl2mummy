#ifndef MUMMY_HPP
#define MUMMY_HPP

#include <SDL.h>
#include <map>
#include <string>
#include "animation.hpp"

class SpriteSheet;

class Mummy
{
    public:
        explicit Mummy(int x, int y);
        ~Mummy();

        void SetSpriteSheet(const SpriteSheet& spritesheet);
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);

    private:
        bool IsCheckPoint();
        std::string GetNewDirection();


        enum MummyState { NONE, SHOWING, LEAVING_TOMB, CHOOSING_DIR, MOVING };
        
        SDL_Texture *mTexture;
        std::map<std::string, Animation> mAnimations;
        std::string mAnimName;
        float mPosX;
        float mPosY;
        int mX;
        int mToX;
        int mY;
        int mToY;
        FrameData mCurrentFrameData;
        MummyState mState, mLastState;
        std::map<int, std::vector<std::string>> mCheckpoints;
        bool mIsFramePosition;

};

#endif  //End MUMMY_HPP
