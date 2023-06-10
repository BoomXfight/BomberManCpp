#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "SinglePlayerLostState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

/**
 * This method initializes the SinglePlayerLostState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool SinglePlayerLostState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mStateID, &mGameObjects,
                                &mTextureIDList))
        return false;

    mCallbacks.push_back(playAgain);
    mCallbacks.push_back(returnToMainMenu);
    mCallbacks.push_back(exit);

    setCallbacks(mCallbacks);
    std::cout << "Entering SinglePlayerLostState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of SinglePlayerLostState
 * @return true
 */
bool SinglePlayerLostState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "SinglePlayerLostState." << std::endl;
    return true;
}

std::string SinglePlayerLostState::getStateID() const
{
    return mStateID;
}

void SinglePlayerLostState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState());
}

void SinglePlayerLostState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void SinglePlayerLostState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string SinglePlayerLostState::mStateID = "SINGLE_PLAYER_LOST_STATE";
