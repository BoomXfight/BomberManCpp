#include "MainMenuState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "StateParser.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include <iostream>


/**
 * This method updates the gameObjects of the MainMenuState
 */
void MainMenuState::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the MainMenuState
 */
void MainMenuState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

/**
 * This method initializes the MainMenuState from an xml load file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MainMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mMenuID, &mGameObjects,&mTextureIDList))
        return false;

    // Initialize the callback functions
    mCallbacks.push_back(nullptr); // TO DO REMOVE AND REPAIR
    mCallbacks.push_back(menuToSinglePlayer);
    mCallbacks.push_back(menuToMultiPlayer);
    mCallbacks.push_back(menuToQuit);

    setCallbacks(mCallbacks);
    std::cout << "Entering MainMenuState" << std::endl;
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

    std::cout << "exiting MenuState" << std::endl;
    return true;
}

std::string MainMenuState::getStateID() const
{
    return mMenuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param[in] pCallbacks
 */
void MainMenuState::setCallbacks(const std::vector<Callback> &pCallbacks)
{
    for(int i = 0; i < mGameObjects.size(); i++)
    {
        // MenuButton requires callback function
        if(dynamic_cast<MenuButton*>(mGameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(pCallbacks[pButton->getCallbackID()]);
        }
    }
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

/**
 * Callback function that ends the game
 */
void MainMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

// a unique ID for the MainMenuState used in the xml load file
const std::string MainMenuState::mMenuID = "MAIN_MENU";
