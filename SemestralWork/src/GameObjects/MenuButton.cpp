#include "MenuButton.hpp"
#include "../Vector2D.hpp"
#include "../Singletons/InputHandler.hpp"

MenuButton::MenuButton() : SDLGameObject()
{
}

/**
 * This method loads the MenuButton
 * @param[in] pParams
 */
void MenuButton::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    mCallbackID = pParams->getCallbackID();
    mCurrentFrame = MOUSE_OUT;
}

/**
 * This method draws the MenuButton
 */
void MenuButton::draw()
{
    SDLGameObject::draw();
}

/**
 * This method implements the dynamics of the button, swapping its states based on the position of the mouse
 */
void MenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance() ->getMousePosition();
    if(pMousePos->getX() < (mPosition.getX() + mWidth)
       && pMousePos->getX() > mPosition.getX()
       && pMousePos->getY() < (mPosition.getY() + mHeight)
       && pMousePos->getY() > mPosition.getY())
    {
        if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && mReleased)
        {
            mCurrentFrame = CLICKED;
            mCallback(); // call our callback function
            mReleased = false;
        }
        else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            mReleased = true;
            mCurrentFrame = MOUSE_OVER;
        }
    }
    else
    {
        mCurrentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}

int MenuButton::getCallbackID()
{
    return mCallbackID;
}

void MenuButton::setCallback(void (*pCallback)())
{
    mCallback = pCallback;
}
