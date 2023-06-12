#include <iostream>
#include "InputHandler.hpp"
#include "Game.hpp"

InputHandler* InputHandler::Instance()
{
    if(mInstance == 0)
        mInstance = new InputHandler();

    return mInstance;
}

void InputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                TheGame::Instance()->clean();
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;

            case SDL_KEYDOWN:
                onKeyDown();
                break;

            case SDL_KEYUP:
                onKeyUp();
                break;

            case SDL_TEXTINPUT:
                input(event);
                break;

            default:
                break;
        }
    }
}

void InputHandler::clean()
{
    delete mInstance;
}

void InputHandler::reset()
{
    for(int i = 0; i < 3; i++)
        mMouseButtonStates.push_back(false);
}

bool InputHandler::getMouseButtonState(int pButtonNumber)
{
    return mMouseButtonStates[pButtonNumber];
}

bool InputHandler::isKeyDown(SDL_Scancode pKey)
{
    if(mKeyStates != 0)
    {
        if(mKeyStates[pKey] == 1)
            return true;
    }
    return false;
}

Vector2D* InputHandler::getMousePosition()
{
    return &mMousePosition;
}

std::string InputHandler::showInput()
{
    return mInput;
}

std::string InputHandler::getResetInput()
{
    std::string tmp;
    tmp = mInput;
    mInput = "";
    return tmp;
}

InputHandler::InputHandler()
        : mMousePosition(Vector2D(0,0)), mKeyStates(nullptr)
{
    for(int i = 0; i < 3; i++) // mouse buttons = false
        mMouseButtonStates.push_back(false);
}

void InputHandler::onKeyDown()
{
    mKeyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::onKeyUp()
{
    mKeyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    mMousePosition.setX(event.motion.x);
    mMousePosition.setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mMouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mMouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mMouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mMouseButtonStates[LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mMouseButtonStates[MIDDLE] = false;
    }

    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mMouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::input(SDL_Event& event)
{
    mInput = event.text.text;
}

InputHandler* InputHandler::mInstance = 0;
