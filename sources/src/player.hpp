#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include <map>
#include <string>
#include "animation.hpp"


class SpriteSheet;

enum PlayerDir {
    DOWN,
    UP,
    LEFT,
    RIGHT
};

class Player
{
    public:
        explicit Player();
        void SetSpriteSheet(const SpriteSheet& spritesheet);

        void Move(PlayerDir direction);
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);
        
    private:
        bool checkCollision(int x, int y) const;

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
};

#endif  //PLAYER_HPP
