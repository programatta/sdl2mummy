#ifndef ITEMOBJECT_HPP
#define ITEMOBJECT_HPP

#include <SDL.h>
//#include "spritesheet.hpp"

class SpriteSheet;

enum ItemObjectState { SHOWING, MOVING, BLINKING };

class ItemObject
{
    public:
        ItemObject(int type, int x, int y);

        void SetSpriteSheet(SpriteSheet& spritesheet);
        int GetX() const;
        int GetY() const;
        int GetType() const;

        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);
    
    private:
        SpriteSheet *mSpriteSheet;
        float mPosX;
        float mPosY;
        int mType;
        int mY;
        int mToY;
        ItemObjectState mState;
};

#endif  //ITEMOBJECT_HPP
