#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class Player1 : public SDLGameObject
{
public:
    Player1();
    void load(const LoaderParams* pParams) override;
    void draw() override;
    void update() override;
    void clean() override;
    int getLives() const;

private:
    void placeBomb();
    void handleInput();
    void handleBonus();

    bool mBombReady;
    bool mExplosion;
    Vector2D mBombPosition;
    int mRadius;
    int mSpeed;
    float mBombTickingTime;

    short mLives;
    bool mMoving;
    bool mLivesCooldown;
    bool mInvisible;

    Uint32 mTimer;
    Uint32 mDamageTimer;
    Uint32 mNow;

    std::vector<Bonus*> mBonuses;
};

class Player1Creator : public BaseCreator
{
    GameObject* createGameObject() const {return new Player1();}
};
