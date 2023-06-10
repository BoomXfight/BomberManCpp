#pragma once
#include "GameState.hpp"
#include <vector>

class GameStateMachine
{
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void render();

    std::vector<GameState*> mGameStates;
};
