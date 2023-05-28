#include "Player.hpp"
#include "../Singletons/InputHandler.hpp"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    handleInput();
    m_currentFrame = int(((SDL_GetTicks() / 100) % 4)); // Depends on the sprite and animation
    SDLGameObject::update();
}

void Player::clean()
{}

void Player::handleInput()
{
    /**if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_position += Vector2D(2,0);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_position += Vector2D(-2,0);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_position += Vector2D(0,-2);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_position += Vector2D(0,2);
    }
    */
    Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}
