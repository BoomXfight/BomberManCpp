#include "MultiPlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../StateParser.hpp"
#include <iostream>

// a unique ID for this state used in the xml file
const std::string MultiPlayerMenuState::s_menuID = "MULTI_PLAYER_MENU";

/**
 * This method updates the gameObjects of the MainMenuState
 */
void MultiPlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

/**
 * This method renders the gameObject of the MainMenuState
 */
void MultiPlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

/**
 * This method initializes the MultiPlayerMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MultiPlayerMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList))
        return false;

    m_callbacks.push_back(0);
    m_callbacks.push_back(menuToQuit);
    m_callbacks.push_back(mpMenuToMainMenu);
    m_callbacks.push_back(mpMenuToMpPlay);

    setCallbacks(m_callbacks);
    std::cout << "entering MultiPlayerMenu state\n";
    return true;
}

/**
 * This method cleans up at the end of gameState and sets the active players
 * @return true
 */
bool MultiPlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(m_gameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    if(TextSquare* b = dynamic_cast<TextSquare*>(m_gameObjects[1]))
    {
        TheGame::Instance()->setP2(b->getText());
        std::cout << "P2 set" << std::endl;
    }

    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

    std::cout << "exiting MultiPlayerMenuState\n";
    return true;
}

std::string MultiPlayerMenuState::getStateID() const
{
    return s_menuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param callbacks
 */
void MultiPlayerMenuState::setCallbacks(const std::vector<Callback> &callbacks)
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


void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

/**
 * Callback function to switch the current state to MainMenuState
 */
void MultiPlayerMenuState::mpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

/**
 * Callback function to switch the current state to MultiPlayerPlayState
 */
void MultiPlayerMenuState::mpMenuToMpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Player1 : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Player1 : guest" << std::endl;

    if(TheGame::Instance()->P2Ready())
        std::cout << "Player2 : " << TheGame::Instance()->getP2() << std::endl;
    else
        std::cout << "Player2 : guest" << std::endl;
}
