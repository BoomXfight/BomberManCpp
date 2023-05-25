#pragma once
#include "SDL2/SDL.h"
#include <vector>
#include "Vector2D.hpp"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance();
    void update();
    void clean();
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition();
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler();
    void onKeyDown();
    void onKeyUp();
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    static InputHandler* s_pInstance;
    std::vector<bool> m_mouseButtonStates; // mouse input
    Vector2D m_mousePosition;
    const Uint8* m_keystates; // keyboard input
};

typedef InputHandler TheInputHandler;