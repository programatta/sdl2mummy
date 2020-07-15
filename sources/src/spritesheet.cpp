#include "spritesheet.hpp"
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include "utils.hpp"
#include "trace.hpp"
#include "json.hpp"
#include <fstream>

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture( mSpriteSheetTexture );
    mSpriteSheetTexture = nullptr;
}

void SpriteSheet::Load(SDL_Renderer *renderer, const std::string& filename)
{
    std::stringstream stex;
    std::stringstream sjson;
    stex << filename << ".png";
    sjson << filename << ".json";

    SDL_Surface *spritesheetSurf = nullptr;
    spritesheetSurf = IMG_Load(Utils::ResourcePath(stex.str()).c_str());
    if(!spritesheetSurf)
    {
        std::stringstream msg;
        msg << "IMG_Load:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
    }
    mSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, spritesheetSurf);
    SDL_FreeSurface(spritesheetSurf);
    if(!mSpriteSheetTexture)
    {
        std::stringstream msg;
        msg << "SDL_CreateTextureFromSurface:" << SDL_GetError();
        Trace::Info("SDL",msg.str());
    }

    std::stringstream contentFile;
    SDL_RWops* file = SDL_RWFromFile(Utils::ResourcePath(sjson.str()).c_str(), "r" );
    Sint64 res_size = SDL_RWsize(file);

    Sint64 nb_read_total = 0, nb_read = 1;
    while(nb_read_total < res_size && nb_read != 0)
    {
        char buf[256];
        memset(buf, 0, 256);
        nb_read = SDL_RWread(file, buf, 1, 255);
        nb_read_total += nb_read;
        std::string strtmp(buf);
        contentFile << strtmp;
    }
    SDL_RWclose(file);    

    std::string content = contentFile.str();
    content.erase( std::remove(content.begin(), content.end(), '\n'), content.end() );

    nlohmann::json spritesJson;
    spritesJson = nlohmann::json::parse(content);

    for(auto item:spritesJson["frames"])
    {
        std::string key = item["filename"].get<std::string>();
        int h = item["frame"]["h"].get<int>();
        int w = item["frame"]["w"].get<int>();
        int x = item["frame"]["x"].get<int>();
        int y = item["frame"]["y"].get<int>();
        SDL_Rect rect={x,y,w,h};
        mFrame.insert(std::pair<std::string, SDL_Rect>(key, rect));
    }
}

SDL_Texture* SpriteSheet::GetTexture() const
{
    return mSpriteSheetTexture;
}

SDL_Rect SpriteSheet::GetFrameByName(const std::string& frameName)const
{
    return mFrame.at(frameName);
}