#include "MainMenuState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../StateParser.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include <iostream>

// a unique ID for this state used in the xml file
const std::string MainMenuState::s_menuID = "MAIN_MENU";

/**
 * This method updates the gameObjects of the MainMenuState
 */
void MainMenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

/**
 * This method renders the gameObject of the MainMenuState
 */
void MainMenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

/**
 * This method initializes the MainMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MainMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList))
        return false;

    // Initialize the callback functions
    m_callbacks.push_back(0); // TO DO REMOVE AND REPAIR
    m_callbacks.push_back(menuToSinglePlayer);
    m_callbacks.push_back(menuToMultiPlayer);
    m_callbacks.push_back(menuToQuit);

    setCallbacks(m_callbacks);
    std::cout << "entering MainMenuState\n";
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

    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

    std::cout << "exiting MenuState\n";
    return true;
}

std::string MainMenuState::getStateID() const
{
    return s_menuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param callbacks
 */
void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // MenuButton requires callback function
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
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
