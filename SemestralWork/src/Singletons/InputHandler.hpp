#pragma once
#include "SDL2/SDL.h"
#include <vector>
#include "../Vector2D.hpp"

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
    void reset();
    bool getMouseButtonState(int buttonNumber);
    bool isKeyDown(SDL_Scancode key);
    Vector2D* getMousePosition();
    std::string showInput();
    std::string getResetInput();

private:
    InputHandler();
    ~InputHandler();
    void onKeyDown();
    void onKeyUp();
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    void input(SDL_Event& event);

    static InputHandler* mInstance;
    std::vector<bool> mMouseButtonStates;
    Vector2D mMousePosition;
    const Uint8* mKeyStates;
    std::string mInput;
};

typedef InputHandler TheInputHandler;