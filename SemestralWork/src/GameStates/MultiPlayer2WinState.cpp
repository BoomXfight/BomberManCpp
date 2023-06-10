#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "MultiPlayer2WinState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

/**
 * This method initializes the MultiPlayer2WinState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MultiPlayer2WinState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mStateID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(playAgain);
    mCallbacks.push_back(returnToMainMenu);
    mCallbacks.push_back(exit);
    setCallbacks(mCallbacks);

    std::cout << "Entering MultiPlayer2WinState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of MultiPlayer2WinState
 * @return true
 */
bool MultiPlayer2WinState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting MultiPlayer2WinState." << std::endl;
    return true;
}

std::string MultiPlayer2WinState::getStateID() const
{
    return mStateID;
}

void MultiPlayer2WinState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new (MultiPlayerPlayState));
}

void MultiPlayer2WinState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayer2WinState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string MultiPlayer2WinState::mStateID = "MULTI_PLAYER2_WIN_STATE";
