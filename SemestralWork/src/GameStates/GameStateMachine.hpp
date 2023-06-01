#pragma once
#include "GameState.hpp"
#include <vector>
#include <memory>

class GameStateMachine
{
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void render();

    std::vector<GameState*> m_gameStates;
};