#include "GameStateMachine.hpp"

/**
 * This method changes the current GameState without removing it
 * @param pState
 */
void GameStateMachine::pushState(GameState* pState)
{
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

/**
 * This method removes the current GameState and changes to the new one
 * @param pState
 */
void GameStateMachine::changeState(GameState* pState)
{
    if(! mGameStates.empty())
    {
        // If tyring to change to the same state
        if(mGameStates.back()->getStateID() == pState->getStateID())
            return;

        if(mGameStates.back()->onExit())
            mGameStates.pop_back();
    }

    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

/**
 * This method removes the current state
 */
void GameStateMachine::popState()
{
    if (! mGameStates.empty())
    {
        if (mGameStates.back()->onExit())
            mGameStates.pop_back();
    }
}

/**
 * This method updates the current GameState
 */
void GameStateMachine::update()
{
    if(! mGameStates.empty())
       mGameStates.back()->update();
}

/**
 * This method renders the current GameState
 */
void GameStateMachine::render()
{
    if(! mGameStates.empty())
       mGameStates.back()->render();
}
