#include "PauseMenuState.hpp"
#include "MainMenuState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "StateParser.hpp"
#include <iostream>

// a unique ID for this state used in the xml file
const std::string PauseMenuState::s_pauseID = "PAUSE_STATE";

/**
 * This method updates the gameObjects of the PauseMenuState
 */
void PauseMenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the PauseMenuState
 */
void PauseMenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

/**
 * This method initializes the PauseMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool PauseMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", s_pauseID, &m_gameObjects,&m_textureIDList))
        return false;

    m_callbacks.push_back(0);
    m_callbacks.push_back(resumePlay);
    m_callbacks.push_back(pauseToMainMenu);
    m_callbacks.push_back(exit);

    setCallbacks(m_callbacks);
    std::cout << "entering PauseState\n";
    return true;
}

/**
 * This method cleans up at the end of gameState and sets the active players
 * @return true
 */
bool PauseMenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("resumeButton");
    TheTextureManager::Instance()->clearFromTextureMap("mainButton");
    TheTextureManager::Instance()->clearFromTextureMap("paused");
    TheTextureManager::Instance()->clearFromTextureMap("exitButton");

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "exiting PauseState\n";
    return true;
}

std::string PauseMenuState::getStateID() const
{
    return s_pauseID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param callbacks
 */
void PauseMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

/**
 * Callback function that switches to MainMenuState
 */
void PauseMenuState::pauseToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

/**
 * Callback function that resumes the PlayState
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
