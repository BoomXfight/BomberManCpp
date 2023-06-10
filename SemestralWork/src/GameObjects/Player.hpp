#pragma once
#include "SDLGameObject.hpp"

class Player : public SDLGameObject
{
public:
    Player();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams* pParams) override;
    int getLives() const;
    int getSpeed() const;
    int getRadius() const;
    bool isImmortal() const;
    bool fastBomb() const;
    bool isDamaged() const;

protected:
    void placeBomb();
    void handleBonus(int num);
    void handleBomb();
    void handleDamage();
    void handleAnimation();
    void updateBonus();
    virtual void handleInput() = 0;

    short mRadius;
    short mSpeed;
    short mLives;
    float mBombTickingTime;
    Vector2D mBombPosition;

    bool mBombReady;
    bool mExplosion;
    bool mMoving;
    bool mImmortal;
    bool mInvisible;

    Uint32 mTimer;
    Uint32 mDamageTimer;
    Uint32 mNow;
    Uint32 mBombTickingTimer;
    Uint32 mInvisibleTimer;

    std::vector<Bonus*> mBonuses;
};
