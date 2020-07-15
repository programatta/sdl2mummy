#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;

class PlayState
{
    public:
        PlayState(SDL_Renderer *renderer);
        ~PlayState();

        void ProcessEvents();
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);
    
    private:
        void DrawMap(SDL_Renderer* render, SDL_Texture* texture, int offsetToCenter);

        
        SDL_Texture *mPlayerTex;
        SDL_Texture *mMapTex;
};

#endif  //PLAY_STATE_HPP
