#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include "ScoreboardState.hpp"
#include <iostream>

/**
 * This method initializes the MainMenuState from an xml load file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MainMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mStateID, &mGameObjects,
                                &mTextureIDList))
        return false;

    // Initialize the callback functions
    mCallbacks.push_back(menuToSinglePlayer);
    mCallbacks.push_back(menuToMultiPlayer);
    mCallbacks.push_back(menuToScoreboard);
    mCallbacks.push_back(menuToQuit);

    setCallbacks(mCallbacks);
    std::cout << "Entering MainMenuState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of gameState
 * @return true
 */
bool MainMenuState::onExit()
{
    TheGame ::Instance()->setP1(""); // Reset the player names
    TheGame ::Instance()->setP2("");

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MainMenuState." << std::endl;
    return true;
}

std::string MainMenuState::getStateID() const
{
    return mStateID;
}

/**
 * Callback function that switches gameState to SinglePlayerMenuState
 */
void MainMenuState::menuToSinglePlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerMenuState());
}

/**
 * Callback function that switches gameState to MultiPlayerMenuState
 */
void MainMenuState::menuToMultiPlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerMenuState());
};

void MainMenuState::menuToScoreboard()
{
    TheGame::Instance()->getStateMachine()->changeState(new ScoreboardState);
}

/**
 * Callback function that ends the game
 */
void MainMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

// a unique ID for the MainMenuState used in the xml load file
const std::string MainMenuState::mStateID = "MAIN_MENU_STATE";
