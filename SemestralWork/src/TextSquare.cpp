#include "TextSquare.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include <iostream>

TextSquare::TextSquare(const LoaderParams* pParams)
    : SDLGameObject(pParams), active(false)
{
    SDL_StopTextInput();
    m_currentFrame = NOT_CLICKED;
    m_bReleased = true;
}

void TextSquare::draw()
{
    SDLGameObject::draw();
}

void TextSquare::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance() ->getMousePosition();
    if(pMousePos->getX() < (m_position.getX() + m_width)
       && pMousePos->getX() > m_position.getX()
       && pMousePos->getY() < (m_position.getY() + m_height)
       && pMousePos->getY() > m_position.getY()
       && TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
    {
        if(!SDL_IsTextInputActive())
        {
            m_currentFrame = CLICKED;
            SDL_StartTextInput();
            active = true;
            std::cout << "TextInputOn\n";
        }
        m_bReleased = false;
    }
    handleInput();
}

void TextSquare::clean()
{
    SDLGameObject::clean();
}

void TextSquare::handleInput()
{
    if(active)
    {
        if (!TheInputHandler::Instance()->showInput().empty()) {
            m_text += TheInputHandler::Instance()->getInput();
            std::cout << m_text << std::endl;
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE)) {
            m_text.pop_back();
            std::cout << m_text << std::endl;
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)
            || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_KP_ENTER)) {
            if (SDL_IsTextInputActive()) {
                SDL_StopTextInput();
                active = false;
                std::cout << "Text input off" << std::endl;
            }
            m_currentFrame = NOT_CLICKED;
            m_bReleased = true;
        }
    }
}

std::string TextSquare::getText()
{
    return m_text;
}
