#include "player.hpp"
#include "spritesheet.hpp"
#include "trace.hpp"
#include <sstream>
#include "itemobject.hpp"

Player::Player(IMapNotificable& map)
{
    mMap = &map;
    mX=0;
    mToX=0;
    mY=0;
    mToY=0;
    mPosX=-1;
    mPosY=-1;

    mAnimName = "down";

    mItemsToOpenMainDoor = 0;
    mPotions = 0;
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

 void Player::SetPosition(float x, float y)
 {
     mPosX = x;
     mPosY = y;
 }

int Player::GetX()const
{
    return mPosX;
}

int Player::GetY()const
{
    return mPosY;
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
    if((mToY>0)||(mToX>0))
    {
        mAnimations[mAnimName].UpdateFrame(deltaTime);
        mCurrentFrameData = mAnimations[mAnimName].GetFrame();
    }
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
                mPosY = mPosY + mY*2 *deltaTime;
            }
            else if( mPosY >= mToY )
            {
                mPosY = mToY;
                mY=0;
                mToY=0;

                //Update map.
                updateMap(mPosX, mPosY, mAnimName);
            }
        }
        else if(mY<0)
        {
            if(mPosY > mToY)
            {
                mPosY = mPosY + mY*2 *deltaTime;
            }
            else if(mPosY <= mToY)
            {
                mPosY = mToY;
                mY=0;
                mToY=0;

                //Update map.
                updateMap(mPosX, mPosY, mAnimName);                
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
                mPosX = mPosX + mX*2 *deltaTime;
            }
            else if( mPosX >= mToX )
            {
                mPosX = mToX;
                mX=0;
                mToX=0;

                //Update map.
                updateMap(mPosX, mPosY, mAnimName);
            }
        }
        else if(mX<0)
        {
            if(mPosX > mToX)
            {
                mPosX = mPosX + mX*2 *deltaTime;
            }
            else if(mPosX <= mToX)
            {
                mPosX = mToX;
                mX=0;
                mToX=0;

                //Update map.
                updateMap(mPosX, mPosY, mAnimName);
            }
        }
    }
}

void Player::Render(SDL_Renderer *renderer)
{
    SDL_Rect orig = {mCurrentFrameData.x,mCurrentFrameData.y,32,32};
    SDL_Rect dest = {
        static_cast<int>(mPosX), 
        static_cast<int>(mPosY),
        32,
        32
    };
    SDL_RenderCopy(renderer, mTexture, &orig, &dest);
}


void Player::AddObject(ItemObject item)
{
    if((item.GetType() == 3) || (item.GetType() == 4))
        mItemsToOpenMainDoor += 1;
    else
    {
        mPotions += 1;

        std::stringstream msg;
        msg << "[AddObject] Potions:" << mPotions;
        Trace::Info("SDL",msg.str());
    }
}

bool Player::CanOpenMainDoor()
{
    return mItemsToOpenMainDoor == 2;
}

int Player::GetPotions()
{
    return mPotions;
}

void Player::ConsumePotion()
{
    if( mPotions>0 )
        mPotions -= 1;

    std::stringstream msg;
    msg << "[ConsumePotion] Potions:" << mPotions;
    Trace::Info("SDL",msg.str());
}

void Player::LostLive()
{
    //TODO: gestionar vidas.
    std::stringstream msg;
    msg << "[LostLive] He perdido una vida!!";
    Trace::Info("SDL",msg.str());
}


/*===========================================================================*/
/*                               Private Section                             */
/*===========================================================================*/
bool Player::checkCollision(int x, int y) const
{
    int xlog = (x)/32;
    int ylog = (y)/32;

    bool hasCol = false;
    switch(mMap->GetTypeAt(xlog, ylog))
    {
        case 1: //Muro.
        case 2: //Puerta tumba.
        case 3: //Puerta tumba abierta.
        case 4: //Puerta principal.
            hasCol = true;
            break;
        default:
            break;
    }
    return hasCol;
}

void Player::updateMap(int x, int y, const std::string& dir)
{
    int xlog = (x)/32;
    int ylog = (y)/32;

    if(mMap->GetTypeAt(xlog,ylog) == 0)
    {
        if( dir == "up")
            mMap->SetTypeAt(xlog, ylog, 6);
        if( dir == "down")
            mMap->SetTypeAt(xlog, ylog, 7);
        if( dir == "left")
            mMap->SetTypeAt(xlog, ylog, 8);
        if( dir == "right")
            mMap->SetTypeAt(xlog, ylog, 9);
    }
}