#include "Player1.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../Singletons/CollisionManager.hpp"

Player1::Player1() : SDLGameObject(), mMoving(false), mTimer(SDL_GetTicks()), mNow(SDL_GetTicks()), mBombReady(true),
                     mRadius(2), mExplosion(false)
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
    std::cout << (mNow - mTimer) / 1000 << std::endl;

    if(!mBombReady && ((mNow - mTimer) / 1000 > 4))
    {
        TheCollisionManager::Instance()->explodeBomb(mBombPosition, mRadius);
        mTimer = SDL_GetTicks();
        mExplosion = true;
    }

    if(mExplosion && ((mNow - mTimer) / 1000 > 1))
    {
        TheCollisionManager::Instance()->afterExplosion(mBombPosition, mRadius);
        mExplosion = false;
        mBombReady = true;
    }

    if(mMoving)
        mCurrentFrame = int(((SDL_GetTicks() / 200) % mNumFrames));
    else
        mCurrentFrame = 1;

    SDLGameObject::update();
}

void Player1::clean()
{}

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
        newPos1.setX(mPosition.getX() + 3 + 18);
        newPos1.setY(mPosition.getY());
        newPos2.setX(mPosition.getX() + 3 + 18);
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
        newPos1.setX(mPosition.getX() - 3);
        newPos1.setY(mPosition.getY());
        newPos2.setX(mPosition.getX() - 3);
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
        newPos1.setY(mPosition.getY() - 3);
        newPos2.setX(mPosition.getX() + 18);
        newPos2.setY(mPosition.getY() - 3);

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
        newPos1.setY(mPosition.getY() + 3 + 24);
        newPos2.setX(mPosition.getX() + 18);
        newPos2.setY(mPosition.getY() + 3 + 24);

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
