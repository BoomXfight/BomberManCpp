#include "Player.hpp"
#include "../Singletons/InputHandler.hpp"

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

void Player::handleInput()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        mCurrentRow = 3;
        mPosition += Vector2D(4,0);
        mMoving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        mCurrentRow = 4;
        mPosition += Vector2D(-4,0);
        mMoving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        mCurrentRow = 2;
        mPosition += Vector2D(0,-4);
        mMoving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        mCurrentRow = 1;
        mPosition += Vector2D(0,4);
        mMoving = true;
    }
    else
        mMoving = false;
}
