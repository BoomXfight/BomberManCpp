#include "TextSquare.hpp"
#include "../Singletons/InputHandler.hpp"
#include <iostream>

TextSquare::TextSquare() : SDLGameObject()
{
}

void TextSquare::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    SDL_StopTextInput();
    mActive = false;
    mCurrentFrame = NOT_CLICKED;
    mReleased = true;
}

void TextSquare::draw()
{
    SDLGameObject::draw();
}

void TextSquare::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance() ->getMousePosition();
    if(pMousePos->getX() < (mPosition.getX() + mWidth)
       && pMousePos->getX() > mPosition.getX()
       && pMousePos->getY() < (mPosition.getY() + mHeight)
       && pMousePos->getY() > mPosition.getY()
       && TheInputHandler::Instance()->getMouseButtonState(LEFT) && mReleased)
    {
        if(!SDL_IsTextInputActive())
        {
            mCurrentFrame = CLICKED;
            SDL_StartTextInput();
            mActive = true;
            std::cout << "TextInputOn" << std::endl;
        }
        mReleased = false;
    }
    handleInput();
}

void TextSquare::clean()
{
    SDLGameObject::clean();
}

std::string TextSquare::getText()
{
    return mText;
}

/**
 * This method handles the user input and reactions with the TextSquare gameObject
 */
void TextSquare::handleInput()
{
    if(mActive)
    {
        if (!TheInputHandler::Instance()->showInput().empty())
        {
            mText += TheInputHandler::Instance()->getResetInput();
            std::cout << mText << std::endl;
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE)) {
            if(!mText.empty())
            {
                mText.pop_back();
                std::cout << mText << std::endl;
            }
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)
            || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_KP_ENTER))
        {
            if (SDL_IsTextInputActive())
            {
                SDL_StopTextInput();
                mActive = false;
                std::cout << "Text input off" << std::endl;
            }
            mCurrentFrame = NOT_CLICKED;
            mReleased = true;
        }
    }
}
