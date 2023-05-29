#include "MainMenuState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../StateParser.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include <iostream>

const std::string MainMenuState::s_menuID = "MAIN_MENU";

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    // go through the game objects
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

void MainMenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    // parse the state
    StateParser stateParser;
    if(!stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList))
        std::cout << "Nerozumim" << std::endl;
    m_callbacks.push_back(0);
    m_callbacks.push_back(menuToSinglePlayer);
    m_callbacks.push_back(menuToMultiPlayer);
    m_callbacks.push_back(menuToQuit);

    setCallbacks(m_callbacks);
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    TheGame ::Instance()->setP1(""); // Reset the player names
    TheGame ::Instance()->setP2("");

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    std::cout << "exiting MenuState\n";
    return true;
}

void MainMenuState::menuToSinglePlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerMenuState());
}

void MainMenuState::menuToMultiPlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerMenuState());
};

void MainMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}
