#include "Player.hpp"
#include "../Singletons/InputHandler.hpp"

Player::Player() : SDLGameObject(), moving(false)
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

    if(moving)
        m_currentFrame = int(((SDL_GetTicks() / 200) % m_numFrames));
    else
        m_currentFrame = 1;

    SDLGameObject::update();
}

void Player::clean()
{}

void Player::handleInput()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_currentRow = 3;
        m_position += Vector2D(4,0);
        moving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_currentRow = 4;
        m_position += Vector2D(-4,0);
        moving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_currentRow = 2;
        m_position += Vector2D(0,-4);
        moving = true;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_currentRow = 1;
        m_position += Vector2D(0,4);
        moving = true;
    }
    else
        moving = false;
}





















