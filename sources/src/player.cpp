#include "player.hpp"
#include "spritesheet.hpp"
#include "trace.hpp"
#include <sstream>

Player::Player()
{
    mX=0;
    mToX=0;
    mY=0;
    mToY=0;
    mPosX=-1;
    mPosY=-1;

    mAnimName = "down";
}

void Player::SetSpriteSheet(const SpriteSheet& spritesheet)
{
    mTexture = spritesheet.GetTexture();

    // //Anim player sur (0,1,2) +
    Animation animDown;
    animDown.AddFrame(spritesheet.GetFrameByName("player-0.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("player-1.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("player-2.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("player-1.png"), 0.16f);
    mAnimations.insert(std::pair<std::string,Animation>("down",animDown));

    // //Anim player oeste (3,4,5) +
    Animation animLeft;
    animLeft.AddFrame(spritesheet.GetFrameByName("player-3.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("player-4.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("player-5.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("player-4.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("left",animLeft));

    // //Anim player este (6,7,8) +
    Animation animRight;
    animRight.AddFrame(spritesheet.GetFrameByName("player-6.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("player-7.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("player-8.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("player-7.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("right",animRight));

    // //Anim player norte (9,10,11) +
    Animation upRight;
    upRight.AddFrame(spritesheet.GetFrameByName("player-9.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("player-10.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("player-11.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("player-10.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("up",upRight));    
}


void Player::Move(PlayerDir direction)
{
    switch(direction)
    {
        case PlayerDir::DOWN:
            if((mToY == 0) && (mToX == 0))
            {
                mY = 32;
                mToY = mPosY + mY;
                mAnimName = "down";
            }
            break;
        case PlayerDir::UP:
            if((mToY == 0) && (mToX == 0))
            {
                mY = -32;
                mToY = mPosY + mY;
                mAnimName = "up";
            }
            break;
        case PlayerDir::LEFT:
            if((mToX == 0) && (mToY == 0))
            {
                mX = -32;
                mToX = mPosX + mX;
                mAnimName = "left";
            }
            break;
        case PlayerDir::RIGHT:
            if((mToX == 0) && (mToY == 0))
            {
                mX = 32;
                mToX = mPosX + mX;
                mAnimName = "right";
            }
            break;
    }    
}

void Player::Update(float deltaTime)
{   
    mAnimations[mAnimName].UpdateFrame(deltaTime);
    if((mToY>0)||(mToX>0))
        mCurrentFrameData = mAnimations[mAnimName].GetFrame();
    else
        mCurrentFrameData = mAnimations[mAnimName].GetFrame(1);    

    if( mToY > 0)
    {
        if( checkCollision( static_cast<int>(mPosX), mToY) )
        {
            mToY = 0;
            mY = 0;
            return;
        }

        if(mY>0)
        {
            if(mPosY < mToY)
            {
                float mY1 = mPosY + mY*2 *deltaTime;
                mPosY = mY1;
            }
            else if( mPosY >= mToY )
            {
                mPosY = mToY;
                mY=0;
                mToY=0;

                //Update map.
                //updateMap(mSprite.getPosition().x, mSprite.getPosition().y, mAnimName);
            }
        }
        else if(mY<0)
        {
            if(mPosY > mToY)
            {
                float mY1 = mPosY + mY*2 *deltaTime;
                mPosY = mY1;
            }
            else if(mPosY <= mToY)
            {
                mPosY = mToY;
                mY=0;
                mToY=0;

                //Update map.
                //updateMap(mSprite.getPosition().x, mSprite.getPosition().y, mAnimName);                
            }
        }
    }
    else if( mToX > 0)
    {
        if( checkCollision(mToX, static_cast<int>(mPosY)) )
        {
            mToX = 0;
            mX = 0;
            return;
        }

        if(mX>0)
        {
            if(mPosX < mToX)
            {
                float mX1 = mPosX + mX*2 *deltaTime;
                mPosX = mX1;
            }
            else if( mPosX >= mToX )
            {
                mPosX = mToX;
                mX=0;
                mToX=0;

                //Update map.
                //updateMap(mSprite.getPosition().x, mSprite.getPosition().y, mAnimName);
            }
        }
        else if(mX<0)
        {
            if(mPosX > mToX)
            {
                float mX1 = mPosX + mX*2 *deltaTime;
                mPosX = mX1;
            }
            else if(mPosX <= mToX)
            {
                mPosX = mToX;
                mX=0;
                mToX=0;

                //Update map.
                //updateMap(mSprite.getPosition().x, mSprite.getPosition().y, mAnimName);
            }
        }
    }
}

void Player::Render(SDL_Renderer *renderer)
{
    float scaleFactorX=1,scaleFactorY=1;
    SDL_RenderGetScale(renderer, &scaleFactorX, &scaleFactorY);
    
    if( mPosX == -1 && mPosY == -1)
    {
        int w,h;
        SDL_GetRendererOutputSize(renderer, &w, &h);

        //int px = w/scaleFactorY/2;
        //int py = h/scaleFactorY/2;
        mPosX = w/scaleFactorY/2 - 16;
        mPosY = h/scaleFactorY/2 - 32;
    }
    SDL_Rect orig = {mCurrentFrameData.x,mCurrentFrameData.y,32,32};
    SDL_Rect dest = {
        static_cast<int>(mPosX), 
        static_cast<int>(mPosY),
        32,
        32
    };

    //orig = mSpriteSheet.GetFrameByName("player-1.png");

    SDL_RenderCopy(renderer, mTexture, &orig, &dest);
}


/*===========================================================================*/
/*                               Private Section                             */
/*===========================================================================*/
bool Player::checkCollision(int x, int y) const
{
    return false;
}
