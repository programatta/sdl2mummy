#include "mummy.hpp"
#include "spritesheet.hpp"
#include "trace.hpp"
#include <sstream>
#include <algorithm>

Mummy::Mummy(int x, int y):mPosX(x),mPosY(y)
{
    srand(time(nullptr));

    mIsFramePosition = false;
    mToX = 0;
    mToY = 0;
    mAnimName = "down";
    mState = MummyState::SHOWING;
    mLastState = MummyState::NONE;

    //Checkpoints.
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(1*19+1,  std::vector<std::string>{"down", "right"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(1*19+5,  std::vector<std::string>{"right", "left", "down"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(1*19+9,  std::vector<std::string>{"right", "left", "down"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(1*19+13, std::vector<std::string>{"right", "left", "down"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(1*19+17, std::vector<std::string>{"down", "left"}));

    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(4*19+1,  std::vector<std::string>{"up", "down", "right"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(4*19+5,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(4*19+9,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(4*19+13, std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(4*19+17, std::vector<std::string>{"up", "down", "left"}));

    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(7*19+1,  std::vector<std::string>{"up", "down", "right"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(7*19+5,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(7*19+9,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(7*19+13, std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(7*19+17, std::vector<std::string>{"up", "down", "left"}));

    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(10*19+1,  std::vector<std::string>{"up", "down", "right"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(10*19+5,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(10*19+9,  std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(10*19+13, std::vector<std::string>{"up", "down", "right", "left"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(10*19+17, std::vector<std::string>{"up", "down", "left"}));

    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(13*19+1,  std::vector<std::string>{"up", "right"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(13*19+5,  std::vector<std::string>{"right", "left", "up"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(13*19+9,  std::vector<std::string>{"right", "left", "up"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(13*19+13, std::vector<std::string>{"right", "left", "up"}));
    mCheckpoints.insert(std::pair<int,std::vector<std::string>>(13*19+17, std::vector<std::string>{"up","left"}));
}

Mummy::~Mummy()
{

}

int Mummy::GetX()const
{
    return mPosX;
}

int Mummy::GetY()const
{
    return mPosY;
}

void Mummy::SetSpriteSheet(const SpriteSheet& spritesheet)
{
    mTexture = spritesheet.GetTexture();

   // //Anim momia sur (0,1,2) +
    Animation animDown;
    animDown.AddFrame(spritesheet.GetFrameByName("mummy-0.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("mummy-1.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("mummy-2.png"), 0.16f);
    animDown.AddFrame(spritesheet.GetFrameByName("mummy-1.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("down",animDown));

    // //Anim momia oeste (3,4,5) +
    Animation animLeft;
    animLeft.AddFrame(spritesheet.GetFrameByName("mummy-3.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("mummy-4.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("mummy-5.png"), 0.16f);
    animLeft.AddFrame(spritesheet.GetFrameByName("mummy-4.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("left",animLeft));

    // //Anim momia este (6,7,8) +
    Animation animRight;
    animRight.AddFrame(spritesheet.GetFrameByName("mummy-6.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("mummy-7.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("mummy-8.png"), 0.16f);
    animRight.AddFrame(spritesheet.GetFrameByName("mummy-7.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("right",animRight));

    // //Anim momia norte (9,10,11) +
    Animation upRight;
    upRight.AddFrame(spritesheet.GetFrameByName("mummy-9.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("mummy-10.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("mummy-11.png"), 0.16f);
    upRight.AddFrame(spritesheet.GetFrameByName("mummy-10.png"), 0.16f);
    mAnimations.insert( std::pair<std::string,Animation>("up",upRight)); 
}

void Mummy::Update(float deltaTime)
{
    mAnimations[mAnimName].UpdateFrame(deltaTime);
    mCurrentFrameData = mAnimations[mAnimName].GetFrame();

    if(mState == MummyState::SHOWING)
    {
        mY = 32;
        mToY = mPosY + mY;
        mState =  MummyState::LEAVING_TOMB;
    }
    else if(mState == MummyState::LEAVING_TOMB)
    {
        if(  mPosY < mToY )
        {
            mPosY = mPosY + mY*2 *deltaTime;
        }
        else if( mPosY >= mToY )
        {
            mPosY =  mToY;
            mToY=-1;
            mY=0;
            mLastState = mState;
            mState =  MummyState::CHOOSING_DIR;
        }
    }
    else if(mState == MummyState::CHOOSING_DIR)
    {
        if(mLastState == MummyState::LEAVING_TOMB)
        {
            //Aleatorio left, right.
            int pos = rand() % 6;   //[0-5]
            if(pos%2==0)
            {
                mAnimName = "right";
                mX = 32;
            }
            else
            {
                mAnimName = "left";
                mX = -32;
            }
            mToX = mPosX + mX;
        }
        else if(mLastState == MummyState::MOVING)
        {
            //Elegir uno entre los posibles que no sea el último.
            mAnimName = GetNewDirection();
            if(mAnimName == "down")
            {
                mY = 32;
                mToY = mPosY + mY;
            }
            else if(mAnimName == "up")
            {
                mY = -32;
                mToY = mPosY + mY;
            }
            else if(mAnimName == "left")
            {
                mX = -32;
                mToX = mPosX + mX;
            }
            else if(mAnimName == "right")
            {
                mX = 32;
                mToX = mPosX + mX;
            }
        }
        mLastState = mState;
        mState = MummyState::MOVING;
    }
    else if(mState == MummyState::MOVING)
    {
        if(mToY>=0)
        {
            //Verificar si la posición es un checkpoint
            if( mIsFramePosition && IsCheckPoint())
            {
                mIsFramePosition = false;
                mLastState = mState;
                mState = MummyState::CHOOSING_DIR;
                mToY=-1;
                mY=0;
            }
            
            if(mY>0)
            {
                if(mPosY < mToY)
                {
                    mPosY = mPosY + mY*2 *deltaTime;
                    mIsFramePosition = false;
                }
                else if( mPosY >= mToY )
                {
                    mPosY = mToY;
                    mToY = mPosY + mY;
                    mIsFramePosition = true;
                }
            }
            else if(mY<0)
            {
                if(mPosY > mToY)
                {
                    mPosY = mPosY + mY*2 *deltaTime;
                    mIsFramePosition = false;
                }
                else if(mPosY <= mToY)
                {
                    mPosY = mToY;
                    mToY = mPosY + mY;
                    mIsFramePosition = true;
                }
            }
        }
        else if(mToX>=0)
        {
            //Verificar si la posición es un checkpoint
            if(mIsFramePosition && IsCheckPoint())
            {
                mIsFramePosition = false;
                mLastState = mState;
                mState = MummyState::CHOOSING_DIR;
                mToX=-1;
                mX=0;
            }

            if(mX>0)
            {
                if(mPosX < mToX)
                {
                    mPosX = mPosX + mX*2 *deltaTime;
                    mIsFramePosition = false;
                }
                else if( mPosX >= mToX )
                {
                    mPosX = mToX;
                    mToX = mPosX + mX;
                    mIsFramePosition = true;
                }
            }
            else if(mX<0)
            {
                if(mPosX > mToX)
                {
                    mPosX = mPosX + mX*2 *deltaTime;
                    mIsFramePosition = false;
                }
                else if(mPosX <= mToX)
                {
                    mPosX = mToX;
                    mToX = mPosX + mX;
                    mIsFramePosition = true;
                }             
            }
        }
    }
}

void Mummy::Render(SDL_Renderer *renderer)
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


/*===========================================================================*/
/*                               Private Section                             */
/*===========================================================================*/
bool Mummy::IsCheckPoint()
{
    int xlog = (static_cast<int>(mPosX))/32;
    int ylog = (static_cast<int>(mPosY))/32;

    int keyToSearch = ylog*19+xlog;

    return mCheckpoints.count(keyToSearch)>0;
}

std::string Mummy::GetNewDirection()
{
    int xlog = (static_cast<int>(mPosX))/32;
    int ylog = (static_cast<int>(mPosY))/32;

    int keyToSearch = ylog*19+xlog;

    std::string inverseAnimName = "";
    if(mAnimName == "down")
        inverseAnimName = "up";
    else if(mAnimName == "up")
        inverseAnimName = "down";
    else if(mAnimName == "left")
        inverseAnimName = "right";
    else if(mAnimName == "right")
        inverseAnimName = "left";

    //std::remove() is a function from stl (algoritm).
    std::vector<std::string> tmp(mCheckpoints[keyToSearch].begin(),mCheckpoints[keyToSearch].end());
    tmp.erase(std::remove(tmp.begin(), tmp.end(), inverseAnimName), tmp.end());

    int pos = (tmp.size()==1) ? 0 : rand() % tmp.size();
    return tmp[pos];
}
