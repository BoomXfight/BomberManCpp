#include "MenuButton.hpp"
#include "../Vector2D.hpp"
#include "../Singletons/InputHandler.hpp"

MenuButton::MenuButton() : SDLGameObject()
{
}

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

void MenuButton::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    mCallbackID = pParams->getCallbackID();
    mCurrentFrame = MOUSE_OUT;
}

int MenuButton::getCallbackID() const
{
    return mCallbackID;
}

void MenuButton::setCallback(void (*pCallback)())
{
    mCallback = pCallback;
}
