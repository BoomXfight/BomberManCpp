#include <iostream>
#include "InputHandler.hpp"
#include "Game.hpp"

InputHandler* InputHandler::Instance()
{
    if(s_pInstance == 0)
    {
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
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
}

InputHandler::InputHandler()
        : m_mousePosition(Vector2D(0,0)), m_keystates(nullptr)
{
    for(int i = 0; i < 3; i++) // mouse buttons = false
        m_mouseButtonStates.push_back(false);
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition()
{
    return &m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keystates != 0)
    {
        if(m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }

    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePosition.setX(event.motion.x);
    m_mousePosition.setY(event.motion.y);
}

void InputHandler::input(SDL_Event& event)
{
    m_input = event.text.text;
}


void InputHandler::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}

std::string InputHandler::showInput()
{
    return m_input;
}

std::string InputHandler::getInput()
{
    //std::cout << m_input;
    std::string tmp;
    tmp = m_input;
    m_input = "";
    //std::cout << tmp;
    return tmp;
}

InputHandler* InputHandler::s_pInstance = 0;