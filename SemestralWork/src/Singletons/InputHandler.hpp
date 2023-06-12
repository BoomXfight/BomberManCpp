#pragma once
#include "../GameObjects/Vector2D.hpp"
#include "SDL2/SDL.h"
#include <vector>

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

/**
 * @class InputHandler
 * This singleton class is responsible for handling user input and updating the current states of mouse and keyboard.
 */
class InputHandler
{
public:
    static InputHandler* Instance();


    /**
     * This method registers and processes the input throughout the game.
     */
    void update();

    /**
     * This method cleans after the InputHandler.
     */
    void clean();

    /**
     * This method resets the mouse button states to false.
     */
    void reset();

    /**
     * This method returns whether a certain mouse click is pressed
     * @param[in] buttonNumber right, left, middle.
     * @return true -> pressed, false -> not pressed.
     */
    bool getMouseButtonState(int buttonNumber);

    /**
     * This method returns whether a certain key on the keyboard is pressed.
     * @param[in] key key number
     * @return
     */
    bool isKeyDown(SDL_Scancode key);

    Vector2D* getMousePosition();

    std::string showInput();

    /**
     * This method resets the input recorded from the user and resets it to empty
     * @return string -> user input
     */
    std::string getResetInput();

private:
    InputHandler();
    /**
     * Updates the current keyboard state.
     */
    void onKeyDown();

    /**
     * Updates the current keyboard state.
     */
    void onKeyUp();

    /**
     * Updates the position of the mouse.
     * @param[in] event mouse motion event.
     */
    void onMouseMove(SDL_Event& event);

    /**
     * Resets the mouse button to false.
     * @param[in] event mouse button event.
     */
    void onMouseButtonDown(SDL_Event& event);

    /**
     * Sets the mouse button to true.
     * @param[in] event mouse button event.
     */
    void onMouseButtonUp(SDL_Event& event);

    /**
     * This method records the user typed input.
     * @param event text input event.
     */
    void input(SDL_Event& event);

    static InputHandler* mInstance;
    std::vector<bool> mMouseButtonStates;
    Vector2D mMousePosition;
    const Uint8* mKeyStates;
    std::string mInput;
};

typedef InputHandler TheInputHandler;