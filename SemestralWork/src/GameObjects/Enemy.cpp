#include "../Singletons/CollisionManager.hpp"
#include "Enemy.hpp"


Enemy::Enemy() : mMoveUp(true), mSpeed(3)
{}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    handleMovement();
    SDLGameObject::update();
}

void Enemy::clean()
{}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Enemy::handleMovement()
{
    Vector2D newPos1 = mPosition;
    Vector2D newPos2 = mPosition;

    if(mMoveUp)
    {
        newPos1.setX(newPos1.getX() + mBuffer);
        newPos1.setY(newPos1.getY() - mSpeed);
        newPos2.setX(newPos2.getX() + mWidth - mBuffer);
        newPos2.setY(newPos2.getY() - mSpeed);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1)
           || TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
            mMoveUp = false;
        else
        {
            newPos1.setX(newPos1.getX() - mBuffer);
            newPos1.setY(newPos1.getY());
            mPosition = newPos1;
        }
    }
    else
    {
        newPos1.setX(newPos1.getX() + mBuffer);
        newPos1.setY(newPos1.getY() + mSpeed + mHeight);
        newPos2.setX(newPos2.getX() + mWidth - mBuffer);
        newPos2.setY(newPos2.getY() + mSpeed + mHeight);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1)
           || TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
            mMoveUp = true;
        else
        {
            newPos1.setX(newPos1.getX() - mBuffer);
            newPos1.setY(newPos1.getY() - mHeight);
            mPosition = newPos1;
        }
    }
}
