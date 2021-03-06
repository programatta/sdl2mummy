#include "playstate.hpp"
#include <SDL_image.h>
#include <sstream>
#include "trace.hpp"
#include "utils.hpp"

PlayState::PlayState(SDL_Renderer *renderer):mStage(*this),mPlayer(mStage)
{
    //Cargamos los sprites.
    mSpriteSheet.Load(renderer,"sprites");

    int w,h;
    SDL_RenderGetLogicalSize(renderer, &w, &h);

    mOrigPlayerX = w/2 - 16;
    mOrigPlayerY = h/2 - 32;

    std::stringstream msg;
    msg << "[PlayState] Player Pos x:" << mOrigPlayerX <<  " - pos y:" << mOrigPlayerY << std::endl;
    msg << "[PlayState] W:" << w <<  " - H:" << h;
    Trace::Info("SDL",msg.str());

    mPlayer.SetPosition(mOrigPlayerX, mOrigPlayerY);
    mPlayer.SetSpriteSheet(mSpriteSheet);

    mStage.SetSpriteSheet(mSpriteSheet);
}

PlayState::~PlayState()
{
}

void PlayState::ProcessEvents(SDL_Event &event)
{
    //ESTO HACE QUE NO VAYA FLUIDO EL MOVIMIENTO DEL PLAYER.
    //USAMOS ProcessEvents que leemos del Buffer de teclado.
    // if(event.type == SDL_KEYDOWN)
    // {
    //     if(event.key.keysym.scancode == SDL_SCANCODE_DOWN)
    //         mPlayer.Move(PlayerDir::DOWN);
    //     else if(event.key.keysym.scancode == SDL_SCANCODE_UP)
    //         mPlayer.Move(PlayerDir::UP);
    // }
    if(event.type == SDL_FINGERDOWN)
    {
        tX0 = event.tfinger.x;
        tY0 = event.tfinger.y;
        std::stringstream msg;
        msg << "[FINGERDOWN] Pos x:" << tX0 <<  " - pos y:" << tY0;
        Trace::Info("SDL",msg.str());
        playerDir = 0;
        starMovement = true;
    }

    if(event.type == SDL_FINGERMOTION)
    {
        if( !starMovement )
            return;

        float DELTA_SWIPED = 0.000025;
        tX = event.tfinger.x;
        tY = event.tfinger.y;

        // std::stringstream msg;
        // msg << "[FINGERMOTION] Pos x0:" << tX0 <<  " - pos y0:" << tY0 << std::endl;
        // msg << "[FINGERMOTION] Pos x:" << tX <<  " - pos y:" << tY << std::endl;
        // msg << "[FINGERMOTION] DIFF Pos x:" << (tX0 - tX) <<  " - DIFF pos y:" << (tY0 - tY) << std::endl;
        // Trace::Info("SDL",msg.str());

        if( tX0 - tX > (608 * DELTA_SWIPED))
        {
            //SWIPED LEFT
            playerDir = 1;
            tX0 = tX;
        }
        else if( tX0 - tX < - (608 * DELTA_SWIPED))
        {
            //SWIPED RIGHT
            playerDir = 2;
            tX0 = tX;
        }

        if( tY0 - tY > (512 * DELTA_SWIPED))
        {
            //SWIPED DOWN
            playerDir = 3;
            tY0 = tY;
        }
        else if( tY0 - tY < - (512 * DELTA_SWIPED))
        {
            //SWIPED UP
            playerDir = 4;
            tY0 = tY;
        }
        isMoving = true;
    }
    if(event.type == SDL_FINGERUP)
    {
        tX0 = tX = 0.0f;
        tY0 = tY = 0.0f;
        isMoving = false;
        playerDir = 0;
        starMovement = false;
    }

    if(isMoving)
    {
        if( playerDir == 1)
            mPlayer.Move(PlayerDir::LEFT);
        else if( playerDir == 2)
            mPlayer.Move(PlayerDir::RIGHT);
        else if( playerDir == 3)
            mPlayer.Move(PlayerDir::UP);
        else if( playerDir == 4)
            mPlayer.Move(PlayerDir::DOWN);
    }
}


void PlayState::ProcessEvents()
{
    const Uint8 *keys = (SDL_GetKeyboardState(nullptr));
    if( keys == nullptr)
        return;

    if( keys[SDL_SCANCODE_DOWN])
        mPlayer.Move(PlayerDir::DOWN);
    else if(keys[SDL_SCANCODE_UP])
        mPlayer.Move(PlayerDir::UP);
    else if(keys[SDL_SCANCODE_LEFT])
        mPlayer.Move(PlayerDir::LEFT);
    else if(keys[SDL_SCANCODE_RIGHT])
        mPlayer.Move(PlayerDir::RIGHT);
}


void PlayState::Update(float deltaTime)
{
    mStage.Update(deltaTime);
    mPlayer.Update(deltaTime);

    auto itObj = mObjects.begin();
    while(itObj != mObjects.end())
    {
        if(checkCanPickUpObject(mPlayer,(*itObj)))
        {
            itObj = mObjects.erase(itObj);
            mPlayer.AddObject((*itObj));
            if(mPlayer.CanOpenMainDoor())
                mStage.OpenMainDoor();
        }
        else
        {
           (*itObj).Update(deltaTime);
           ++itObj;
        }
    }

    //Mummies.
    auto itMummy = mMummies.begin();
    while(itMummy != mMummies.end())
    {
        if(checkPlayerIsAttackedByMummy(mPlayer,(*itMummy)))
        {
            if(mPlayer.GetPotions()>0)
                mPlayer.ConsumePotion();
            else
            {
                mPlayer.LostLive();
                mPlayer.SetPosition(mOrigPlayerX, mOrigPlayerY);
            }

            itMummy = mMummies.erase(itMummy);
        }
        else
        {
           (*itMummy).Update(deltaTime);
           ++itMummy;
        }
    } 
}

void PlayState::Render(SDL_Renderer *renderer)
{
    //Stage.
    mStage.Render(renderer);

    //Player.
    mPlayer.Render(renderer);

    //Object.
    for(auto &object:mObjects)
        object.Render(renderer);

    //Mummies.
    for(auto &mummy:mMummies)
        mummy.Render(renderer);    
}

void PlayState::CreateObject(int type, int x, int y)
{
    if( type == 1 ) //Momia.
    {
        Mummy mummy(x,y);
        mummy.SetSpriteSheet(mSpriteSheet);
        mMummies.push_back(mummy);
    }
    else if((2 <= type) && (type <= 4)) //Pocion, Llave y Papiro.
    {
        ItemObject itemObject(type, x, y);
        itemObject.SetSpriteSheet(mSpriteSheet);
        mObjects.push_back(itemObject);
    }
    else if( type == 5 ) //Hechizo.
    {
        //TODO:        
    }    
}


/*===========================================================================*/
/*===========================================================================*/
bool PlayState::checkCanPickUpObject(const Player &player, const ItemObject &itemObject)
{
    int xObjLog = (itemObject.GetX()+16)/32;
    int yObjLog = (itemObject.GetY()+16)/32;

    int xLog = (player.GetX()+16)/32;
    int yLog = (player.GetY()+16)/32;

    return (xObjLog == xLog) && (yObjLog == yLog);
}

bool PlayState::checkPlayerIsAttackedByMummy(const Player &player, const Mummy &mummy)
{
    int xMummyLog = (mummy.GetX()+16)/32;
    int yMummyLog = (mummy.GetY()+16)/32;

    int xLog = (player.GetX()+16)/32;
    int yLog = (player.GetY()+16)/32;

    return (xMummyLog == xLog) && (yMummyLog == yLog);   
}