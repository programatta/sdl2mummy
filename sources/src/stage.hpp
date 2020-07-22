#ifndef STAGE_HPP
#define STAGE_HPP

#include <SDL.h>
#include <vector>
#include "imapnotificable.hpp"
#include "spritesheet.hpp"

class Tomb;

class Stage : public IMapNotificable
{
    public:
        Stage();
        ~Stage();
    
        void SetTypeAt(int x, int y, int type) override;
        int GetTypeAt(int x, int y) const override;

        void SetSpriteSheet(const SpriteSheet& spritesheet);
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);

    private:
        int generateContentType();
        void createObjectType(int type, int x, int y);

        int mMap[16][19];
        SpriteSheet mSpriteSheet;
        std::vector<Tomb> mTombs;
};

#endif  //STAGE_HPP
