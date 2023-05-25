#pragma once
#include "GameState.hpp"
#include <vector>

class GameStateMachine
{
public:
    void pushState(GameState* pState); // add without removing
    void changeState(GameState* pState); // remove and add another
    void popState(); // remove, don't add
    void update();
    void render();

private:
    std::vector<GameState*> m_gameStates;
};