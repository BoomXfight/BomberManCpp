#pragma once
#include "../GameObjects/GameObject.hpp"
#include "GameState.hpp"

/**
 * @class MenuState
 * This is a base class for all the menu states throughout the game.
 */
class MenuState : public GameState
{
public:
    MenuState();

    /**
     * This method updates the MenuState.
     */
    void update() override;

    /**
     * This method renders the MenuState to the screen.
     */
    void render() override;

protected:
    typedef void(*Callback)();
    void setCallbacks(const std::vector<Callback>& pCallbacks);

    std::vector<Callback> mCallbacks;
    std::vector<GameObject*> mGameObjects;
};
