#include "MenuButton.hpp"
#include "Vector2D.hpp"
#include "InputHandler.hpp"

MenuButton::MenuButton(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_currentFrame = MOUSE_OUT; // start at frame 0
}

void MenuButton::draw()
{
    SDLGameObject::draw(); // use the base class drawing
}

/**
 * This method implements the dynamic button, swapping its states based on the position of the mouse
 */
void MenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance() ->getMousePosition();
    if(pMousePos->getX() < (m_position.getX() + m_width)
       && pMousePos->getX() > m_position.getX()
       && pMousePos->getY() < (m_position.getY() + m_height)
       && pMousePos->getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_currentFrame = CLICKED;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}