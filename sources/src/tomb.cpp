#include "tomb.hpp"

Tomb::Tomb(int x, int y, int contentType):mCanOpen(true),mX(x),mY(y),mContentType(contentType)
{
}

void Tomb::Update(const int map[16][19])
{
    mCanOpen = true;
    int x = mX-1;
    int y = mY-1;
    for(int i=0; i<5; i++)
    {
        mCanOpen &= map[y][x+i] > 0;
        mCanOpen &= map[y+3][x+i] > 0;
    }

    for(int i=0; i<4; i++)
    {
        mCanOpen &= map[y+i][x] > 0;
        mCanOpen &= map[y+i][x+4] > 0;
    }
}

bool Tomb::CanOpen()
{
    return mCanOpen;
}

int Tomb::GetX()
{
    return mX;
}

int Tomb::GetY()
{
    return mY;
}

int Tomb::GetContentTpe()
{
    return mContentType;
}
