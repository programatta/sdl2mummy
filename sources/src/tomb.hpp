#ifndef TOMB_HPP
#define TOMB_HPP

class Tomb
{
    public:
        Tomb(int x, int y, int contentType);
    
        void Update(const int map[16][19]);
        bool CanOpen();
        int GetX();
        int GetY();
        int GetContentTpe();

    private:
        bool mCanOpen;
        int mX;
        int mY;
        int mContentType;
};

#endif  //TOMB_HPP
