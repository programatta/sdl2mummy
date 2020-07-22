#include "stage.hpp"
#include "tomb.hpp"
#include <stdlib.h>     /* srand, rand */

Stage::Stage():
    mMap{
            {1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
            {1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    }
{
    int x0=2;
    int y0=2;

    srand(time(nullptr));

    int sg1 = rand() % 8;       //[0-7]
    int sg2 = rand() % 8 + 7;   //[0-7]+8=[8-15]

    for(int i=0; i<16; i++)
    {
        int x1 = x0+4*(i/4);
        int y1 = y0+3*(i%4);
    
        int contentType;
        if( i == sg1 )
            contentType = 3;
        else if( i == sg2 )
            contentType = 4;
        else
            contentType = generateContentType();

        mTombs.push_back(Tomb(x1, y1, contentType));
    }
}

Stage::~Stage()
{
}


/*===========================================================================*/
/*                       Override from IMapNotificable                       */
/*===========================================================================*/
void Stage::SetTypeAt(int x, int y, int type)
{
    mMap[y][x] = type;
}

int Stage::GetTypeAt(int x, int y) const
{
    return mMap[y][x];
}


void Stage::SetSpriteSheet(const SpriteSheet& spritesheet)
{
    mSpriteSheet = spritesheet;
}

void Stage::Update(float deltaTime)
{
    auto it = mTombs.begin();
    while(it != mTombs.end())
    {
        (*it).Update(mMap);
        if( (*it).CanOpen() )
        {
            mMap[(*it).GetY()+1][(*it).GetX()+1] = 3;   //Tumba abierta.
            createObjectType((*it).GetContentTpe(), (*it).GetX()+1, (*it).GetY()+1);
            it = mTombs.erase(it);
        }
        else
            ++it;
    }

    if( mTombs.empty() )
        mMap[0][9] = 5;   //Nivel abierto.
}

void Stage::Render(SDL_Renderer *renderer)
{
    for(int r=0; r<16; r++) 
    {
        for(int c = 0; c < 19; c++)
        {
            SDL_Rect orig;
            if(mMap[r][c] == 1)
            {
                //muro
                orig = mSpriteSheet.GetFrameByName("tiles-36.png");
            }
            else if(mMap[r][c] == 2)
            {
                //puerta tumba
                orig = mSpriteSheet.GetFrameByName("tiles-57.png");
            }
            else if(mMap[r][c] == 3)
            {
                //puerta tumba abierta
                orig = mSpriteSheet.GetFrameByName("tiles-58.png");
            }
            else if(mMap[r][c] == 4)
            {
                //puerta principal
                orig = mSpriteSheet.GetFrameByName("tiles-54.png");
            }
            else if(mMap[r][c] == 5)
            {
                //puerta principal abierta
                orig = mSpriteSheet.GetFrameByName("tiles-55.png");
            }
            else if(mMap[r][c] == 6)
            {
                //pasos arriba
                orig =  mSpriteSheet.GetFrameByName("desert-33.png");
            }
            else if(mMap[r][c] == 7)
            {
                //pasos abajo
                orig =  mSpriteSheet.GetFrameByName("desert-52.png");
            }
            else if(mMap[r][c] == 8)
            {
                //pasos izquierda
                orig = mSpriteSheet.GetFrameByName("desert-51.png");
            }
            else if(mMap[r][c] == 9)
            {
                //pasos derecha
                orig = mSpriteSheet.GetFrameByName("desert-32.png");
            }            
            else
            {
                orig = mSpriteSheet.GetFrameByName("desert-3.png");
            }

            SDL_Rect dest = {32 * c, 32 * r, 32, 32};
            SDL_RenderCopy(renderer, mSpriteSheet.GetTexture(), &orig, &dest);
        }
    }
}

/*===========================================================================*/
/*                                Private Section                            */
/*===========================================================================*/
int Stage::generateContentType()
{
    int selector = rand() % 10 + 1;
    int contentType = 0;    //Vacio
    switch (selector)
    {
        case 2:
        case 5:
        case 7:
            contentType = 1;    //Momia.
            break;

        case 4:
        case 9:
            contentType = 2;    //Pocion.
            break;
        default: //1,3,6,8,10   /Vacio.
            break;
    }
    return contentType;
}

void Stage::createObjectType(int type, int xlog, int ylog)
{
    //Logic to phisic.
    int x = xlog*32+16;
    int y = ylog*32+16;

    //mObject->CreateObject(type, x, y);
}