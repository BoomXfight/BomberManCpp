#include "Player1.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Singletons/Game.hpp"
#include <cstdlib>
#include <ctime>

Player1::Player1() : SDLGameObject(), mMoving(false), mTimer(SDL_GetTicks()), mNow(SDL_GetTicks()),
                    mDamageTimer(SDL_GetTicks()), mBombReady(true),mRadius(2), mExplosion(false), mLives(3),
                    mLivesCooldown(false), mSpeed(4), mBombTickingTime(3), mInvisible(false)
{}

void Player1::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Player1::draw()
{
    SDLGameObject::draw();
}

void Player1::update()
{
    handleInput();

    mNow = SDL_GetTicks();
    //std::cout << (mNow - mTimer) / 1000 << std::endl;

    if(!mBombReady && (float(mNow - mTimer) / 1000 > mBombTickingTime))
    {
        TheCollisionManager::Instance()->explodeBomb(mBombPosition, mRadius);
        mTimer = SDL_GetTicks();
        mExplosion = true;
    }

    if(mExplosion && (float(mNow - mTimer) / 1000 > 0.5))
    {
        TheCollisionManager::Instance()->afterExplosion(mBombPosition, mRadius);
        int walls = TheCollisionManager::Instance()->getResetExplodedWalls();
        std::cout << walls << std::endl;

        for(walls; walls > 0; walls--)
            handleBonus();

        mExplosion = false;
        mBombReady = true;
    }

    if(mMoving)
        mCurrentFrame = int(((SDL_GetTicks() / 200) % mNumFrames));
    else
        mCurrentFrame = 1;

    if(TheCollisionManager::Instance()->isDamaged(mPosition) && !mLivesCooldown && !mInvisible)
    {
        mLivesCooldown = true;
        mDamageTimer = SDL_GetTicks();
        mLives--;

        std::cout << "LIVES P1: " << mLives << std::endl;
    }

    if((mNow - mDamageTimer) / 1000 > 2)
w        mLivesCooldown = false;

    SDLGameObject::update();
}

void Player1::clean()
{}

int Player1::getLives() const
{
    return mLives;
}


void Player1::placeBomb()
{
    if(mBombReady)
    {
        mTimer = SDL_GetTicks();
        mBombPosition = mPosition;
        TheCollisionManager::Instance()->placeBomb(mPosition);
        mBombReady = false;
    }
}

void Player1::handleInput()
{
    Vector2D newPos1 = mPosition;
    Vector2D newPos2 = mPosition;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) // Right
    {
        mCurrentRow = 3;
        newPos1.setX(mPosition.getX() + mSpeed + 18);
        newPos1.setY(mPosition.getY());
        newPos2.setX(mPosition.getX() + mSpeed + 18);
        newPos2.setY(mPosition.getY() + 24);

        if(TheCollisionManager::Instance()->tileCollision(newPos1) || TheCollisionManager::Instance()->tileCollision(newPos2))
            mMoving = false;

        else
        {
            newPos1.setX(newPos1.getX()-18);
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) // Left
    {
        mCurrentRow = 4;
        newPos1.setX(mPosition.getX() - mSpeed);
        newPos1.setY(mPosition.getY());
        newPos2.setX(mPosition.getX() - mSpeed);
        newPos2.setY(mPosition.getY() + 24);

        if(TheCollisionManager::Instance()->tileCollision(newPos1) || TheCollisionManager::Instance()->tileCollision(newPos2))
            mMoving = false;

        else
        {
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) // Up
    {
        mCurrentRow = 2;
        newPos1.setX(mPosition.getX());
        newPos1.setY(mPosition.getY() - mSpeed);
        newPos2.setX(mPosition.getX() + 18);
        newPos2.setY(mPosition.getY() - mSpeed);

        if(TheCollisionManager::Instance()->tileCollision(newPos1) || TheCollisionManager::Instance()->tileCollision(newPos2))
            mMoving = false;

        else
        {
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) // Down
    {
        mCurrentRow = 1;
        newPos1.setX(mPosition.getX());
        newPos1.setY(mPosition.getY() + mSpeed + 24);
        newPos2.setX(mPosition.getX() + 18);
        newPos2.setY(mPosition.getY() + mSpeed + 24);

        if(TheCollisionManager::Instance()->tileCollision(newPos1) || TheCollisionManager::Instance()->tileCollision(newPos2))
            mMoving = false;

        else
        {
            newPos1.setY(newPos1.getY() - 24);
            mPosition = newPos1;
            mMoving = true;
        }
    }
    else
        mMoving = false;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        placeBomb();
}

void Player1::handleBonus()
{
    std::srand(std::time(nullptr));
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
                std::cout << "Up speed" << std::endl;
                mSpeed += 2;
            }

            else if(bonus == "radius")
            {
                std::cout << "Up radius" << std::endl;
                mRadius++;
            }

            else if(bonus == "health")
            {
                std::cout << "Up lives" << std::endl;
                if(mLives < 3)
                    mLives += 1;
            }

            else if(bonus == "time")
            {
                std::cout << "Down time" << std::endl;
                mBombTickingTime = 1.5;
            }

            else if(bonus == "dmg")
            {
                std::cout << "Invisible" << std::endl;
                mInvisible = true;
            }
        }
    }
}
