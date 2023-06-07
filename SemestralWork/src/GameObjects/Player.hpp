#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class Player : public SDLGameObject
{
public:
    Player();
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

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const {return new Player();}
};
