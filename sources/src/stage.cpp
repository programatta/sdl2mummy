#include "stage.hpp"

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

}

void Stage::Render(SDL_Renderer *renderer)
{
    float scaleFactorX=1,scaleFactorY=1;
    SDL_RenderGetScale(renderer, &scaleFactorX, &scaleFactorY);
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
        
    int offsetToCenter = ((w / scaleFactorY)-(32*19))/2;

    for(int r=0; r<16; r++) 
    {
        for(int c = 0; c < 19; c++)
        {
            SDL_Rect orig;
            if(mMap[r][c] == 1)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-36.png");
            }
            else if(mMap[r][c] == 2)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-57.png");
            }
            else if(mMap[r][c] == 4)
            {
                orig = mSpriteSheet.GetFrameByName("tiles-54.png");
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

            SDL_Rect dest = {32 * c + offsetToCenter, 32 * r, 32, 32};
            SDL_RenderCopy(renderer, mSpriteSheet.GetTexture(), &orig, &dest);
        }
    }
}