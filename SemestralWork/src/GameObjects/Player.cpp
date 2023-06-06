#include "Player.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../Singletons/CollisionManager.hpp"

Player::Player() : SDLGameObject(), mMoving(false)
{}

void Player::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    handleInput();

    if(mMoving)
        mCurrentFrame = int(((SDL_GetTicks() / 200) % mNumFrames));
    else
        mCurrentFrame = 1;

    SDLGameObject::update();
}

void Player::clean()
{}

void Player::placeBomb()
{
    TheCollisionManager::Instance()->placeBomb(mPosition);
}

void Player::handleInput()
{
    Vector2D newPos = mPosition;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) //Texture adjustment
    {
        mCurrentRow = 3;
        newPos.setX(mPosition.getX() + 3 + 18);
        newPos.setY(mPosition.getY());

        if(TheCollisionManager::Instance()->tileCollision(newPos))
            mMoving = false;

        else
        {
            newPos.setX(newPos.getX()-18);
            mPosition = newPos;
            mMoving = true;
        }
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) //Fine
    {
        mCurrentRow = 4;
        newPos.setX(mPosition.getX() - 3);
        newPos.setY(mPosition.getY());

        if(TheCollisionManager::Instance()->tileCollision(newPos))
            mMoving = false;

        else
        {
            mPosition = newPos;
            mMoving = true;
        }
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) //Fine
    {
        mCurrentRow = 2;
        newPos.setX(mPosition.getX());
        newPos.setY(mPosition.getY() - 3);

        if(TheCollisionManager::Instance()->tileCollision(newPos))
            mMoving = false;

        else
        {
            mPosition = newPos;
            mMoving = true;
        }
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) //Texture adjustment
    {
        mCurrentRow = 1;
        newPos.setX(mPosition.getX());
        newPos.setY(mPosition.getY() + 3 + 24);

        if(TheCollisionManager::Instance()->tileCollision(newPos))
            mMoving = false;

        else
        {
            newPos.setY(newPos.getY() - 24);
            mPosition = newPos;
            mMoving = true;
        }
    }
    else
        mMoving = false;

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        placeBomb();
}
