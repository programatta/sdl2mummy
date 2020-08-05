#include "itemobject.hpp"
#include <string>
#include "spritesheet.hpp"

ItemObject::ItemObject(int type, int x, int y):mType(type),mPosX(x),mPosY(y)
{
    mState = ItemObjectState::SHOWING;
}

void ItemObject::SetSpriteSheet(SpriteSheet& spritesheet)
{
    mSpriteSheet = &spritesheet;  
}

int ItemObject::GetX() const
{
    return mPosX;
}

int ItemObject::GetY() const
{
    return mPosY;
}

int ItemObject::GetType() const
{
    return mType;
}

void ItemObject::Update(float deltaTime)
{
    if(mState == ItemObjectState::SHOWING)
    {
        mY = 32;
        mToY = mPosY + mY;
        mState =  ItemObjectState::MOVING;
    }
    else if(mState == ItemObjectState::MOVING)
    {
        if(  mPosY < mToY )
        {
            float mY1 = mPosY + mY*2 *deltaTime;
            mPosY = mY1;
        }
        else if( mPosY >= mToY )
        {
            mPosY =  mToY;
            mToY=0;
            mState =  ItemObjectState::BLINKING;
            //mSubState = ItemObjectSubState::DIMINISHING;
        }
    }
}

void ItemObject::Render(SDL_Renderer *renderer)
{
    std::string itemName = "";
    if(mType == 2)
        itemName = "object-0.png";
    if(mType == 3)
        itemName = "object-3.png";
    if(mType == 4)
        itemName = "object-14.png";  

    if(!itemName.empty())
    {
        SDL_Rect orig = mSpriteSheet->GetFrameByName(itemName);
        SDL_Rect dest = {
            static_cast<int>(mPosX), 
            static_cast<int>(mPosY),
            32,
            32
        };
        SDL_RenderCopy(renderer, mSpriteSheet->GetTexture(), &orig, &dest);
    }
}