#include "PauseMenuState.hpp"
#include "MainMenuState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "StateParser.hpp"
#include <iostream>

/**
 * This method updates the gameObjects of the PauseMenuState
 */
void PauseMenuState::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the PauseMenuState
 */
void PauseMenuState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

/**
 * This method initializes the PauseMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool PauseMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mPauseID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(nullptr);
    mCallbacks.push_back(resumePlay);
    mCallbacks.push_back(pauseToMainMenu);
    mCallbacks.push_back(exit);

    setCallbacks(mCallbacks);
    std::cout << "Entering PauseMenuState" << std::endl;
    return true;
}

/**
 * This method cleans up at the end of PauseMenuState
 * @return true
 */
bool PauseMenuState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting PauseMenuState" << std::endl;
    return true;
}

std::string PauseMenuState::getStateID() const
{
    return mPauseID;
}

/**
 * Callback function that switches to MainMenuState
 */
void PauseMenuState::pauseToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

/**
 * Callback function that resumes the MultiPlayerPlayState
 */
void PauseMenuState::resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

/**
 * Callback function that ends the game
 */
void PauseMenuState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string PauseMenuState::mPauseID = "PAUSE_MENU_STATE";
