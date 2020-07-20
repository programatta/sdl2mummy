#ifndef STAGE_HPP
#define STAGE_HPP

#include <SDL.h>
#include "imapnotificable.hpp"
#include "spritesheet.hpp"

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
        int mMap[16][19];
        SpriteSheet mSpriteSheet;
};

#endif  //STAGE_HPP
