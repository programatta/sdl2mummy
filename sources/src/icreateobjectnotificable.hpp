#ifndef ICREATEOBJECTNOTIFICABLE_HPP
#define ICREATEOBJECTNOTIFICABLE_HPP

class ICreateObjectNotificable
{
    public:
        virtual void CreateObject(int type, int x, int y) = 0;
};

#endif  //ICREATEOBJECTNOTIFICABLE_HPP
