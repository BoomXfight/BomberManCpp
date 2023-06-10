#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "MultiPlayer1WinState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

/**
 * This method initializes the MultiPlayer1WinState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MultiPlayer1WinState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mStateID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(playAgain);
    mCallbacks.push_back(returnToMainMenu);
    mCallbacks.push_back(exit);
    setCallbacks(mCallbacks);

    std::cout << "Entering MultiPlayer1WinState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of MultiPlayer1WinState
 * @return true
 */
bool MultiPlayer1WinState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting MultiPlayer1WinState." << std::endl;
    return true;
}

std::string MultiPlayer1WinState::getStateID() const
{
    return mStateID;
}

void MultiPlayer1WinState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState());
}

void MultiPlayer1WinState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayer1WinState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string MultiPlayer1WinState::mStateID = "MULTI_PLAYER1_WIN_STATE";
