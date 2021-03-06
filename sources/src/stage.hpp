#ifndef STAGE_HPP
#define STAGE_HPP

#include <SDL.h>
#include <vector>
#include "imapnotificable.hpp"
#include "icreateobjectnotificable.hpp"
#include "spritesheet.hpp"

class Tomb;

class Stage : public IMapNotificable
{
    public:
        Stage(ICreateObjectNotificable &object);
        ~Stage();
    
        void SetTypeAt(int x, int y, int type) override;
        int GetTypeAt(int x, int y) const override;

        void SetSpriteSheet(const SpriteSheet& spritesheet);
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);

        void OpenMainDoor();

    private:
        int generateContentType();
        void createObjectType(int type, int x, int y);

        int mMap[16][19];
        const SpriteSheet* mSpriteSheet;
        std::vector<Tomb> mTombs;
        ICreateObjectNotificable *mObject;
};

#endif  //STAGE_HPP
