#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class Player2 : public SDLGameObject
{
public:
    Player2();
    void load(const LoaderParams* pParams) override;
    void draw() override;
    void update() override;
    void clean() override;

private:
    void placeBomb();
    void handleInput();

    bool mBombReady;
    bool mExplosion;
    Vector2D mBombPosition;
    int mRadius;

    Uint32 mTimer;
    Uint32 mNow;
    bool mMoving;
};

class Player2Creator : public BaseCreator
{
    GameObject* createGameObject() const {return new Player2();}
};
