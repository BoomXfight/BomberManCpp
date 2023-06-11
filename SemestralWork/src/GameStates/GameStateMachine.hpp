#pragma once
#include "GameState.hpp"
#include <vector>

/**
 * @class GameStateMachine
 * @brief This class is responsible for changing the gameStates throughout the entire game
 */
class GameStateMachine
{
public:
    /**
    * This method changes the current GameState without removing the last one
    * This functionality ensures the ability to get back to the state before activated one
    * @param pState state that is activated
    */
    void pushState(GameState* pState);

    /**
     * This method changes the current GameState and removes the last one
     * This functionality makes it impossible ot get back to the last state
     * @param pState
     */
    void changeState(GameState* pState);

    /**
     * This method removes the current GameState
     */
    void popState();

    /**
     * This method updates the current GameState
     */
    void update();

    /**
     * This method renders the current GameState
     */
    void render();

    std::vector<GameState*> mGameStates;
};
