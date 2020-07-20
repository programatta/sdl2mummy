#ifndef IMAPNOTIFICABLE_HPP
#define IMAPNOTIFICABLE_HPP

class IMapNotificable
{
    public:
        virtual void SetTypeAt(int x, int y, int type) = 0;
        virtual int GetTypeAt(int x, int y) const = 0;
};

#endif  //IMAPNOTIFICABLE_HPP
