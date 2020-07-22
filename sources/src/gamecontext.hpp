#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

class GameContext {
    public:
        static GameContext& GetInstance()
        {
            //if(GameContext::mMe == nullptr)
            //    GameContext::mMe = new GameContext();
            
            //return *GameContext::mMe;
            static GameContext mMe;
            return mMe;
        }

        ~GameContext()
        {
            //delete GameContext::mMe;
            //GameContext::mMe = nullptr;
        }

        void SetContext(int width, int height, int widthgame, int heightgame, float sfx, float sfy )
        {
            mScaleFactorX = sfx;
            mScaleFactorY= sfy;
            mWidthGame = widthgame;
            mHeightGame = heightgame;
            mWidth = width;
            mHeight = height;
        }

        float GetScaleFactorX() {return mScaleFactorX;}
        float GetScaleFactorY() {return mScaleFactorY;}
        int GetWidth() {return mWidth;}
        int GetHeight() {return mHeight;}
        int GetWidthGame() {return mWidthGame;}
        int GetHeightGame() {return mHeightGame;}

    private:
        GameContext()
        {
            mScaleFactorX = 0.0f;
            mScaleFactorY= 0.0f;
            mWidthGame = 0;
            mHeightGame = 0;
            mWidth = 0;
            mHeight = 0;            
        }

        float mScaleFactorX;
        float mScaleFactorY;
        int mWidthGame;
        int mHeightGame;
        int mWidth;
        int mHeight;
        
        //static GameContext *mMe;
};

//GameContext* GameContext::mMe = nullptr;

#endif  //GAMECONTEXT_HPP
