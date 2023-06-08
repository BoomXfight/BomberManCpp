#include "MultiPlayer2WinState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "StateParser.hpp"
#include <iostream>

/**
 * This method updates the gameObjects of the MultiPlayer2WinState
 */
void MultiPlayer2WinState::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the MultiPlayer2WinState
 */
void MultiPlayer2WinState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

/**
 * This method initializes the MultiPlayer2WinState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MultiPlayer2WinState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mMenuID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(nullptr);
    mCallbacks.push_back(playAgain);
    mCallbacks.push_back(returnToMainMenu);
    mCallbacks.push_back(exit);

    setCallbacks(mCallbacks);
    std::cout << "Entering MultiPlayer2WinState" << std::endl;
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
    std::cout << "Exiting MultiPlayer2WinState" << std::endl;
    return true;
}

std::string MultiPlayer2WinState::getStateID() const
{
    return mMenuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param pCallbacks
 */
void MultiPlayer2WinState::setCallbacks(const std::vector<Callback> &pCallbacks)
{
    for(int i = 0; i < mGameObjects.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(mGameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(pCallbacks[pButton->getCallbackID()]);
        }
    }
}

/**
 * Callback function that switches to MainMenuState
 */
void MultiPlayer2WinState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new (MultiPlayerPlayState));
}

/**
 * Callback function that resumes the MultiPlayerPlayState
 */
void MultiPlayer2WinState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

/**
 * Callback function that ends the game
 */
void MultiPlayer2WinState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string MultiPlayer2WinState::mMenuID = "MULTI_PLAYER2_WIN_STATE";
