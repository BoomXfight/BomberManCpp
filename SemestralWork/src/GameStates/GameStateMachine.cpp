#include "GameStateMachine.hpp"

void GameStateMachine::pushState(GameState* pState)
{
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

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

void GameStateMachine::popState()
{
    if (! mGameStates.empty())
    {
        if (mGameStates.back()->onExit())
            mGameStates.pop_back();
    }
}

void GameStateMachine::update()
{
    if(! mGameStates.empty())
       mGameStates.back()->update();
}

void GameStateMachine::render()
{
    if(! mGameStates.empty())
       mGameStates.back()->render();
}
