#include "CollisionManager.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <ctime>

Player::Player() : SDLGameObject(), mRadius(2), mSpeed(4), mLives(3), mBombTickingTime(3), mBombReady(true),
                 mExplosion(false), mMoving(false), mImmortal(false), mInvisible(false), mTimer(SDL_GetTicks()),
                 mDamageTimer(SDL_GetTicks()), mNow(SDL_GetTicks()), mBonuses(TheCollisionManager::Instance()->getBonuses())
{}

void Player::update()
{
    mNow = SDL_GetTicks();
    handleInput();
    handleBomb();
    handleDamage();
    updateBonus();
    handleAnimation();

    if((mNow - mDamageTimer) / 1000 > 3)
        mImmortal = false;
}


int Player::getLives() const
{
    return mLives;
}

int Player::getSpeed() const
{
    return mSpeed;
}

int Player::getRadius() const
{
    return mRadius;
}

bool Player::isImmortal() const
{
    return (mImmortal || mInvisible);
}

bool Player::fastBomb() const
{
    return mBombTickingTime == 1.5;
}

bool Player::isDamaged() const
{
    return mImmortal;
}

void Player::placeBomb()
{
    if(mBombReady)
    {
        mTimer = SDL_GetTicks();
        mBombPosition = mPosition;
        TheCollisionManager::Instance()->placeBomb(mPosition);
        mBombReady = false;
    }
}

void Player::handleBonus(int num)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)) + num);
    int random = std::rand() % 100;
    std::string bonus;
    mBonuses = TheCollisionManager::Instance()->getBonuses();

    for(auto it = mBonuses.begin(); it != mBonuses.end(); it++)
    {
        if((*it)->inProbability(random))
        {
            bonus = (*it)->getName();
            if(bonus == "speed")
            {
                if(mSpeed < 7)
                    mSpeed++;
            }
            else if(bonus == "radius")
            {
                if(mRadius < 8)
                    mRadius ++;
            }
            else if(bonus == "health")
            {
                if(mLives < 3)
                    mLives++;
            }
            else if(bonus == "time")
            {
                mBombTickingTime = 1.5;
                mBombTickingTimer = SDL_GetTicks();
            }
            else if(bonus == "dmg")
            {
                mInvisible = true;
                mInvisibleTimer = SDL_GetTicks();
            }
        }
    }
}

void Player::handleBomb()
{
    if(! mBombReady && (float(mNow - mTimer)) / 1000 > mBombTickingTime)
    {
        TheCollisionManager::Instance()->explodeBomb(mBombPosition, mRadius);
        mTimer = SDL_GetTicks();
        mExplosion = true;
    }

    if(mExplosion && (float(mNow - mTimer)) / 1000 > 0.5)
    {
        TheCollisionManager::Instance()->afterExplosion(mBombPosition, mRadius);
        int walls = TheCollisionManager::Instance()->getResetExplodedWalls();
        std::cout << walls << std::endl;

        for(int i = walls; i > 0; i --)
            handleBonus(i);

        mExplosion = false;
        mBombReady = true;
    }
}

void Player::handleDamage()
{
    if((TheCollisionManager::Instance()->isPlayerDamaged(mPosition) && !mImmortal && !mInvisible)
    || (TheCollisionManager::Instance()->enemyCollisionPlayer(this) && !mImmortal && !mInvisible))
    {
        mImmortal = true;
        mDamageTimer = SDL_GetTicks();
        mLives --;
    }
}

void Player::handleAnimation()
{
    if(mMoving)
        mCurrentFrame = int(((SDL_GetTicks() / (500 / mSpeed) ) % mNumFrames));
    else
        mCurrentFrame = 1;
}

void Player::updateBonus()
{
    if(mBombTickingTime == 1.5 && ((mNow - mBombTickingTimer) / 1000 > 10))
        mBombTickingTime = 2.5;

    if(mInvisible && ((mNow - mInvisibleTimer) / 1000 > 7))
        mInvisible = false;
}
