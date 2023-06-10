#include "../Singletons/InputHandler.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "Player1.hpp"

Player1::Player1() : Player()
{}

void Player1::handleInput()
{
    Vector2D newPos1 = mPosition;
    Vector2D newPos2 = mPosition;
    float buffer = 0.5;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) // right
    {
        mCurrentRow = RIGHT_MOVEMENT;
        newPos1.setX(mPosition.getX() + mSpeed + mWidth - buffer);
        newPos1.setY(mPosition.getY() + buffer);
        newPos2.setX(mPosition.getX() + mSpeed + mWidth - buffer);
        newPos2.setY(mPosition.getY() + mHeight - buffer);

        if(TheCollisionManager::Instance()->tileCollisionPlayer((newPos1))
        || TheCollisionManager::Instance()->tileCollisionPlayer(newPos2))
            mMoving = false;
        else
        {
            newPos1.setX(newPos1.getX() - mWidth + buffer);
            newPos1.setY(newPos1.getY() - buffer);
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) // left
    {
        mCurrentRow = LEFT_MOVEMENT;
        newPos1.setX(mPosition.getX() - mSpeed + buffer);
        newPos1.setY(mPosition.getY() + buffer);
        newPos2.setX(mPosition.getX() - mSpeed + buffer);
        newPos2.setY(mPosition.getY() + mHeight - buffer);

        if(TheCollisionManager::Instance()->tileCollisionPlayer(newPos1)
           || TheCollisionManager::Instance()->tileCollisionPlayer(newPos2))
            mMoving = false;
        else
        {
            newPos1.setX(newPos1.getX() - buffer);
            newPos1.setY(newPos1.getY() - buffer);
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) // up
    {
        mCurrentRow = UP_MOVEMENT;
        newPos1.setX(mPosition.getX() + buffer);
        newPos1.setY(mPosition.getY() - mSpeed + buffer);
        newPos2.setX(mPosition.getX() + mWidth - buffer);
        newPos2.setY(mPosition.getY() - mSpeed + buffer);

        if(TheCollisionManager::Instance()->tileCollisionPlayer(newPos1)
           || TheCollisionManager::Instance()->tileCollisionPlayer(newPos2))
            mMoving = false;
        else
        {
            newPos1.setX(newPos1.getX() - buffer);
            newPos1.setY(newPos1.getY() - buffer);
            mPosition = newPos1;
            mMoving = true;
        }
    }

    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) // down
    {
        mCurrentRow = DOWN_MOVEMENT;
        newPos1.setX(mPosition.getX() + buffer);
        newPos1.setY(mPosition.getY() + mSpeed + mHeight - buffer);
        newPos2.setX(mPosition.getX() + mWidth - buffer);
        newPos2.setY(mPosition.getY() + mSpeed + mHeight - buffer);

        if(TheCollisionManager::Instance()->tileCollisionPlayer(newPos1)
           || TheCollisionManager::Instance()->tileCollisionPlayer(newPos2))
            mMoving = false;
        else
        {
            newPos1.setX(newPos1.getX() - buffer);
            newPos1.setY(newPos1.getY() - mHeight + buffer);
            mPosition = newPos1;
            mMoving = true;
        }
    }
    else
        mMoving = false;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        placeBomb();
}
