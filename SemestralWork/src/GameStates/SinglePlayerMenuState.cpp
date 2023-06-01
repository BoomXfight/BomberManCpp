#include "SinglePlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../StateParser.hpp"
#include <iostream>

// a unique ID for this state used in the xml file
const std::string SinglePlayerMenuState::s_menuID = "SINGLE_PLAYER_MENU";

/**
 * This method updates the gameObjects of the MainMenuState
 */
void SinglePlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

/**
 * This method renders the gameObject of the MainMenuState
 */
void SinglePlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

/**
 * This method initializes the SinglePlayerMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool SinglePlayerMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList))
        return false;

    m_callbacks.push_back(0);
    m_callbacks.push_back(menuToQuit);
    m_callbacks.push_back(spMenuToMainMenu);
    m_callbacks.push_back(spMenuToSpPlay);

    setCallbacks(m_callbacks);
    std::cout << "entering SinglePlayerMenu state\n";
    return true;
}

/**
 * This method cleans up at the end of gameState and initializes an active player
 * @return true
 */
bool SinglePlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(m_gameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

    std::cout << "exiting SinglePlayerMenuState\n";
    return true;
}

std::string SinglePlayerMenuState::getStateID() const
{
    return s_menuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param callbacks
 */
void SinglePlayerMenuState::setCallbacks(const std::vector<Callback> &callbacks)
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
 * This callback function quits the game
 */
void SinglePlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

/**
 * This callback function returns to the MainMenuState
 */
void SinglePlayerMenuState::spMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

/**
 * This callback function switches the current game state to the SinglePlayerPlayState
 */
void SinglePlayerMenuState::spMenuToSpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Playing as : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Playing as : guest" << std::endl;
}
