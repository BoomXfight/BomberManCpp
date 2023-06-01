#include "GameStateMachine.hpp"

/**
 * This method changes the current GameState without removing it
 * @param pState
 */
void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

/**
 * This method removes the current GameState and changes to the new one
 * @param pState
 */
void GameStateMachine::changeState(GameState* pState)
{
    if(!m_gameStates.empty())
    {
        // If tyring to change to the same state
        if(m_gameStates.back()->getStateID() == pState->getStateID())
            return;

        if(m_gameStates.back()->onExit())
            m_gameStates.pop_back();
    }

    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

/**
 * This method removes the current state
 */
void GameStateMachine::popState()
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->onExit())
        {
            //delete m_gameStates.back(); -> caused seg fault
            m_gameStates.pop_back();
        }
    }
}

/**
 * This method updates the current GameState
 */
void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    }
}

/**
 * This method renders the current GameState
 */
void GameStateMachine::render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}
