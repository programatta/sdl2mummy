#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <SDL.h>
#include <vector>
#include "spritesheet.hpp"
#include "stage.hpp"
#include "player.hpp"
#include "itemobject.hpp"
#include "icreateobjectnotificable.hpp"
#include "mummy.hpp"

class PlayState : public ICreateObjectNotificable
{
    public:
        PlayState(SDL_Renderer *renderer);
        ~PlayState();

        void ProcessEvents(SDL_Event &event);
        void ProcessEvents();
        void Update(float deltaTime);
        void Render(SDL_Renderer *renderer);

        void CreateObject(int type, int x, int y) override;
    
    private:
        bool checkCanPickUpObject(const Player &player, const ItemObject &itemObject);
        
        SpriteSheet mSpriteSheet;
        SDL_Texture *mSpriteTex;
        Stage mStage;
        Player mPlayer;
        std::vector<ItemObject> mObjects;
        std::vector<Mummy> mMummies;

        //TODO: esto va tener que ir a un input manager o algo asi.
        float tX0;
        float tY0;
        float tX;
        float tY;
        bool isMoving;
        int playerDir;
        bool starMovement;
};

#endif  //PLAY_STATE_HPP
