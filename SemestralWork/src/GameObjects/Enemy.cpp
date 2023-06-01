#include "Enemy.hpp"
#include "../Singletons/InputHandler.hpp"

Enemy::Enemy() : SDLGameObject()
{}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    handleInput();
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    SDLGameObject::update();
}

void Enemy::clean()
{}

void Enemy::handleInput()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
    {
        m_position += Vector2D(2,0);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
    {
        m_position += Vector2D(-2,0);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
    {
        m_position += Vector2D(0,-2);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
    {
        m_position += Vector2D(0,2);
    }
}