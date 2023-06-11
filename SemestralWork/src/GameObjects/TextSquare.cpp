#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "TextSquare.hpp"
#include <iostream>

TextSquare::TextSquare() : SDLGameObject(), mActive(false), mReleased(true)
{
}

void TextSquare::draw()
{
    SDLGameObject::draw();
    SDL_Color white = {255, 255, 255};
    TTF_Font* font = TheGame::Instance()->getFont();
    TTF_SetFontSize(font, 30);
    if(!mText.empty() && mText.size() <= 11)
        TheTextureManager::Instance()->drawText(mText, mPosition.getX() + 13, mPosition.getY() + 10,
                                                white,TheGame::Instance()->getRenderer(), font );
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

void TextSquare::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    SDL_StopTextInput();
    mActive = false;
    mCurrentFrame = NOT_CLICKED;
    mReleased = true;
}

std::string TextSquare::getText()
{
    return mText;
}

void TextSquare::handleInput()
{
    if(mActive)
    {
        if (!TheInputHandler::Instance()->showInput().empty())
        {
            if(mText.size() <= 10)
                mText += TheInputHandler::Instance()->getResetInput();
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE)) {
            if(!mText.empty())
                mText.pop_back();
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
