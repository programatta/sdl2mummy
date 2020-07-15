#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <SDL.h>
#include <string>
#include <map>


class SpriteSheet
{
    public:
        ~SpriteSheet();
        void Load(SDL_Renderer *renderer, const std::string& filename);
        SDL_Texture* GetTexture() const;
        SDL_Rect GetFrameByName(const std::string& frameName) const;

    private:
        SDL_Texture *mSpriteSheetTexture;
        std::map<std::string, SDL_Rect> mFrame;
};

#endif  //SPRITESHEET_HPP
